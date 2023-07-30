#include"packDef.h"
#include"INetMediator.h"
#include<process.h>
#include "TcpServerNet.h"
#include "TcpClientNet.h"
TcpClientNet::TcpClientNet(INetMediator* pMediator):m_sock(INVALID_SOCKET), m_hThreadHendle(0), m_isStop(false)
{
	m_pMediator = pMediator;
}

TcpClientNet::~TcpClientNet()
{
	TcpClientNet::UnInitNet();
}

//初始化网络 加载库、创建套接字、绑定IP地址、申请广播权限、创建一个接收线程
//TCP需要修改的地方：1、创建Socket使用TCP协议；2、设置广播权限去掉，不需要了；3、连接服务器，绑定服务器
//IP地址和端口号，调用connect函数连接服务器
bool TcpClientNet::InitNet()
{
	//1.选项目----加载库，手抓饼
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSAStartup failed with error:%d\n", err);
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("Could not find a usable version of Winsock.dll\n");
		return false;
	}
	else {
		printf("The Winsock 2.2 dll was found okay\n");
	}
	//2.雇人---创建套接字
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sock) {
		cout << "socket error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "socket success." << endl;
	}
	//3.连接服务器
	sockaddr_in addrServer;
	// IPV4协议族
	addrServer.sin_family = AF_INET;
	//htons将整数转换成网络字节序
	addrServer.sin_port = htons(_DEF_TCP_PORT);//将整型变量从主机字节序转换成网络字节序
	//绑定服务器IP地址
	addrServer.sin_addr.S_un.S_addr = inet_addr(_DEF_TCP_SERVER_IP);//服务器需要绑定任意网卡
	//inet_addr:将IP地址从字符串类型转换成u_long类型
	err = connect(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "connect error:" << WSAGetLastError() << endl;	
		closesocket(m_sock);
		return false;
	}
	else {
		cout << "bind success." << endl;
	}
	//接收数据--创建线程 C/C++RunTime库 strcpy创建内存块
	//CreateThread创建的线程不会回收内存块，造成内存泄漏
	//ExitThread退出线程 _brginthreadex底层也是调用的CreateThread,退出时调用ExitThread,并且回收创建内存块

	//TODO:5.创建接收线程
	//CreateThread是WIN API，退出使用的是ExitThread
	// 如果在线程中使用了strcpy这类C++运行时库函数，会创建内存块，但是在ExitThread退出线程时，不会回收创建的内存块，会造成内存泄漏
	// _beginthreadex，退出使用的是_endthreadex，会回收内存空间，再调用ExitThread退出线程
	m_hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}

auto _stdcall TcpClientNet::RecvThread(void* Ipvoid) -> unsigned int
{
	TcpClientNet* IpThis = (TcpClientNet*)Ipvoid;
	IpThis->ReceiveData();
	return 0;
}

//关闭网络,关闭套接字，加载库 
void TcpClientNet::UnInitNet()
{
	//尝试退出线程循环
	m_isStop = true;
    //Close the thread
	if (m_hThreadHendle) {
		//等待一会，查看线程是否退出
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hThreadHendle, 100)) {
			//如果线程没有自己结束，就杀死线程
			TerminateThread(m_hThreadHendle, -1);
		}
		//关闭句柄
		CloseHandle(m_hThreadHendle);
		m_hThreadHendle = NULL;
	}
	//关闭套接字
	if (m_sock && INVALID_SOCKET != m_sock) {
		closesocket(m_sock);
	}
	//卸载库
	WSACleanup();
}

//发送数据：1、先判断输入参数的合法性，如果buf为空或者nLen小于等于0，就不用传输了；
//2、为了防止沾包问题，先发送包大小，再发送包内容。
//TCP传输使用send函数，发送数据使用的socket就是上面创建的m_sock

//发送数据
bool TcpClientNet::SendData(long ISendIp, char* buf, int nLen)
{
	//基于字节流有粘包问题
	//1、校验参数
	//判断传入参数合法性
	if (!buf || nLen <= 0)
	{
		cout << "TcpClient::SendData parameter error" << endl;
		return false;
	}
	//2、防止粘包，先发包大小
	//这里m_sock就等于ISendip
	if (send(m_sock, (char*)&nLen, sizeof(int), 0) <= 0)
	{
		cout << "TcpClient::SendData" << WSAGetLastError() << endl;
		return false;
	}
	//3、再发包内容
	if (send(m_sock, buf, nLen, 0) <= 0)
	{
	cout << "TcpClient::SendData" << WSAGetLastError() << endl;
	return false;
    }
	return true;
}

//1、定义一个变量存储包的大小，一个变量接着接收返回值，一个变量计算偏移量
// 2、在循环中接收数据，先接收包大小，再接收包的内容
// 2.1、使用recv函数接收数据，判断返回值小于等于0就直接结束接收，说明与服务端的连接已经出错了
// 2.2、申请一块接收到的包大小这么大的空间，循环接收包数据，因为数据可能不能一次接收完全
// 2.3、每次接收完数据，根据返回值计算偏移量（返回的是实际接收的字节数），如果实际接收的数据量大于0，则
// 包大小-实际接收的数据的大小，偏移量+实际接收大小，然后继续循环
// 3、此次数据接收完成以后，调用中介者的处理数据函数，把数据传递给中介者类，缓冲区中的数据取出后，
// 需要在函数回收申请的堆空间
//接收数据
void TcpClientNet::ReceiveData()
{
	int nRecvNum = 0;
	//存储包大小
	int packSize = 0;
	//偏移量，计算累计接受的包的大小
	int offset = 0;
	while (!m_isStop)
	{
		//先接包大小，包大小是一个int值，再接收数据包
		nRecvNum = recv(m_sock, (char*)&packSize, sizeof(int), 0);
		//从接收缓冲区拷贝包大小
		if (nRecvNum <= 0) {
			cout << "TcpClient::ReceiveData" << WSAGetLastError() << endl;
			break;
		}
		char* packBuf = new char[packSize];
		//循环接收包内容
		//packSize记录的是一个包中还有多少数据没有接收到，offset记录的是一个包中累计已经接收到多少数据
		while (packSize) {
			nRecvNum = recv(m_sock, packBuf + offset, packSize, 0);
			if (nRecvNum > 0) {//数据可能不能一次接收完全，需要循环接收
				packSize -= nRecvNum;
				offset += nRecvNum;
			}
		}
		//接收完一个数据包，发给中介者类
		//需要在这个函数回收buf堆区空间
		this->m_pMediator->DealData(m_sock, packBuf, offset);
		//回收new出来的packBuf
		//offset清零
		offset = 0;
	}
}



