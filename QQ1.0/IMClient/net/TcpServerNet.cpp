#include"TcpServerNet.h"
#include"TcpServerMediator.h"
#include "packDef.h"
#include <process.h>
#include "TcpServerMediator.h"
#include "UdpNet.h"
#include "TcpClientNet.h"
TcpServerNet::TcpServerNet(INetMediator* pMediator) :m_socket(INVALID_SOCKET), m_hThreadHendle(0), m_isStop(false)
{
	m_pMediator = pMediator;
}
TcpServerNet::~TcpServerNet()//使用时，父类指针指向子类，使用虚析构
{
	UnInitNet();
}
//初始化网络 加载库、创建套接字、绑定IP地址、监听、创建一个接受连接线程
bool TcpServerNet::InitNet()
{//1.选项目----加载库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) 
	{
		printf("WSAStartup failed with error:%d\n", err);
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) 
	{
		printf("Could not find a usable version of Winsock.dll\n");
		return false;
	}
	else 
	{
		printf("The Winsock 2.2 dll was found okay\n");
	}
	//2.雇人---创建套接字
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_socket) 
	{
		cout << "socket error:" << WSAGetLastError() << endl;
		return false;
	}
	else 
	{
		cout << "socket success." << endl;
	}
	//3.摆摊---绑定IP地址
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(_DEF_TCP_PORT);//将整型变量从主机字节序转换成网络字节序
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;//服务器需要绑定任意网卡
	//addrServer.sin_addr.S_un.S_addr = inet_addr("192.168.43.162");//inet_addr:将IP地址从字符串类型转换成u_long类型
	err = bind(m_socket, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) 
	{
		cout << "bind error:" << WSAGetLastError() << endl;
		return false;
	}
	else 
	{
		cout << "bind success." << endl;
	}
	//4.监听
	err = listen(m_socket, 10);
	if (SOCKET_ERROR == err) 
	{
		cout << "listen error:" << WSAGetLastError() << endl;
		return false;
	}
	else 
	{
		cout << "listen success." << endl;
	}
	//TODO:5.创建接受连接线程
	//CreateThread是WIN API，退出使用的是ExitThread
	// 如果在线程中使用了strcpy这类C++运行时库函数，会创建内存块，但是在ExitThread退出线程时，不会回收创建的内存块，会造成内存泄漏
	// _beginthreadex，退出使用的是_endthreadex，会回收内存空间，再调用ExitThread退出线程
	m_hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &AcceptThread, this, 0, NULL);
	return true;
}
//接受连接的线程函数
unsigned int _stdcall TcpServerNet::AcceptThread(void* Ipvoid)
{
	TcpServerNet* pThis = (TcpServerNet*)Ipvoid;
	sockaddr_in addrClient;
	int addrClientSize = sizeof(addrClient);
	while (!pThis->m_isStop) 
	{
		SOCKET sock = accept(pThis->m_socket, (sockaddr*)&addrClient, &addrClientSize);
		cout << "IP:" << inet_ntoa(addrClient.sin_addr) << "connect success." << endl;
		//给连接成功的客户端创建一个接收数据线程 
		unsigned int nThreadId = 0;
		HANDLE hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, pThis, 0, &nThreadId);
		// 保存句柄
		pThis->m_hThreadHendleList.push_back(hThreadHendle);
		//保存socket和对应的线程id
		pThis->m_mapThreadIdToSocket[nThreadId] = sock;
	}
	return 0;
}
unsigned int  _stdcall TcpServerNet::RecvThread(void* Ipvoid)
{
	TcpServerNet* pThis = (TcpServerNet*)Ipvoid;
	pThis->RecvData();
	return 0;
}
//关闭网络,退出线程、关闭套接字，加载库 
void TcpServerNet::UnInitNet()
{
	//TODO:关闭线程
	//设置标志位，让线程自己结束循环
	//让线程自己结束循环
	for (auto ite = m_hThreadHendleList.begin(); ite != m_hThreadHendleList.end();)
	{
		if (*ite)
		{
			m_isStop = true;
			//等待一会，查看线程是否退出
			if (WAIT_TIMEOUT == WaitForSingleObject(*ite, 100))
			{//如果线程没有自己结束，就杀死线程
				TerminateThread(*ite, -1);
			}
			//关闭句柄
			CloseHandle(*ite);
			*ite = NULL;
		}
		ite = m_hThreadHendleList.erase(ite);
	}
	//关闭套接字
	if (m_socket && m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
	}
	// 关闭n个数据交换使用的套接字
	for (auto ite = m_mapThreadIdToSocket.begin(); ite != m_mapThreadIdToSocket.end();)
	{
		if (ite->second && ite->second != INVALID_SOCKET) 
		{
			closesocket(ite->second);
		}
		ite = m_mapThreadIdToSocket.erase(ite);
		//卸载库
		WSACleanup();
	}
}
//发送数据
bool TcpServerNet::SendData(long ISendIp, char* buf, int nLen)
{
	// 1、校验参数
	if (!buf || nLen <= 0) 
	{
		cout << "parameter error" << endl; return false;
	}
	// 2、先发包大小
	if (send(ISendIp, (char*)&nLen, sizeof(int), 0) <= 0) 
	{
		cout << "send error:" << WSAGetLastError() << endl;
		return false;
	}
	// 3、再发包内容
	if (send(ISendIp, buf, nLen, 0) <= 0) 
	{
		cout << "send error:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
//接收数据
void TcpServerNet::RecvData()
{
	// 1、获取与客户端通信的socket
//因为接收数据线程是创建即运行，但是把线程id和对应的套接字存入map中还需要一点时间，所以需要休眠一会 
	Sleep(100);
	SOCKET sock = m_mapThreadIdToSocket[GetCurrentThreadId()];
	// 2、判断socket的合法性
	if (!sock || sock == INVALID_SOCKET)
	{
		return;
	}
	int nRecvNum = 0;
	int packSize = 0;
	int offset = 0;
	while (!m_isStop) 
	{
		//先接收包大小
		nRecvNum = recv(sock, (char*)&packSize, sizeof(int), 0);
		if (nRecvNum > 0)
		{
			// 再接收包内容
			char* packBuf = new char[packSize];
			while (packSize) 
			{
				nRecvNum = recv(sock, packBuf + offset, packSize, 0);
				if (nRecvNum > 0) 
				{
					offset += nRecvNum;
					packSize -= nRecvNum;
				}
			}
			if (m_pMediator) 
			{
				//把数据传递给中介者类
				m_pMediator->DealData(sock, packBuf, offset);
			}// TODO:回收packBuf，在处理完数据以后}
			offset = 0;
		}
	}
}

