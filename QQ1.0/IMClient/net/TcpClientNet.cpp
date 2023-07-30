#include"TcpClientNet.h"
#include"packDef.h"
#include<process.h>
#include"TcpClientMediator.h"
#include"INet.h"
TcpClientNet::TcpClientNet(INetMediator* pMediator) :m_socket(INVALID_SOCKET), m_hThreadHendle(0), m_isStop(false)
{
	m_pMediator = pMediator;
}

TcpClientNet::~TcpClientNet()//使用时，父类指针指向子类，使用虚析构
{
	UnInitNet();
}

//初始化网络 加载库、创建套接字、连接服务器、创建一个接收线程
bool TcpClientNet::InitNet()
{//1.选项目----加载库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0){
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
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_socket) {
		cout << "socket error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "socket success." << endl;
	}
    //3.连接服务器
	//设置服务器的IP地址
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(_DEF_TCP_PORT);//将整型变量从主机字节序转换成网络字节序
	//addrServer.sin_addr.S_un.S_addr = ("192.168.110.9");//服务器需要绑定任意网卡
	addrServer.sin_addr.S_un.S_addr = inet_addr(_DEF_TCP_SERVER_IP);//inet_addr:将IP地址从字符串类型转换成u_long类型
	//连接服务器           //地址信息              //取大小
	err = connect(m_socket, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "connect error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "connect success." << endl;
	}
	//TODO:5.创建接收线程
	//CreateThread是WIN API，退出使用的是ExitThread
	// 如果在线程中使用了strcpy这类C++运行时库函数，会创建内存块，但是在ExitThread退出线程时，不会回收创建的内存块，会造成内存泄漏
	// _beginthreadex，退出使用的是_endthreadex，会回收内存空间，再调用ExitThread退出线程
	m_hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}

unsigned int  _stdcall TcpClientNet::RecvThread(void* Ipvoid)
{
	TcpClientNet* pThis = (TcpClientNet*)Ipvoid;
	pThis->RecvData();
	return 1;
}

//关闭网络,关闭线程，关闭套接字，卸载库
void TcpClientNet::UnInitNet()
{
	//TODO:关闭线程
	if (m_hThreadHendle){
		m_isStop = true;//尝试退出线程循环
		//等待一会，查看线程是否退出
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hThreadHendle, 100)){
			//如果线程没有自己结束，就杀死线程
			TerminateThread(m_hThreadHendle, -1);
		}
		//关闭句柄
		CloseHandle(m_hThreadHendle);
		m_hThreadHendle = NULL;
	}
	//关闭套接字
	if (m_socket && m_socket != INVALID_SOCKET){
		closesocket(m_socket);
	}
	//卸载库
	WSACleanup();
}

//发送数据
bool TcpClientNet::SendData(long ISendIp, char* buf, int nLen)
{
	// 1、校验参数
	if (!buf || nLen <= 0) {
		cout << "parameter error" << endl; return false;
	}
	// 2、先发包大小
	if (send(m_socket, (char*)&nLen, sizeof(int), 0) <= 0){
		cout << "send error:" << WSAGetLastError() << endl;
		return false;
	}
	// 3、再发包内容
	if (send(m_socket, buf, nLen, 0) <= 0){
		cout << "send error:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//接收数据
void TcpClientNet::RecvData()
{
	int nRecvNum = 0;
	int packSize = 0;
	int offset = 0;
	while (!m_isStop){
		//先接收包大小
		nRecvNum = recv(m_socket, (char*)&packSize, sizeof(int), 0);
		if (nRecvNum > 0) {
			// 再接收包内容
			char* packBuf = new char[packSize];
			while (packSize) {
				nRecvNum = recv(m_socket, packBuf + offset, packSize, 0);
				if (nRecvNum > 0) {
					offset += nRecvNum;
					packSize -= nRecvNum;
				}
			}
			if (m_pMediator) {
				//把数据传递给中介者类
				m_pMediator->DealData(m_socket, packBuf, offset);
			}// TODO:回收packBuf，在处理完数据以后}
			offset = 0;
		}
	}
}
