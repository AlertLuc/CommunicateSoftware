#include"UdpNet.h"
#include"UdpMediator.h"
#include"packDef.h"
#include"INetMediator.h"
#include<process.h>
#include "TcpServerNet.h"
#include "TcpClientNet.h"
UdpNet::UdpNet(INetMediator* pMediator) :m_socket(INVALID_SOCKET), m_hThreadHendle(0), m_isStop(false)
{
	m_pMediator = pMediator;
}
UdpNet::~UdpNet()//使用时，父类指针指向子类，使用虚析构
{
	UnInitNet();
}
//初始化网络 加载库、创建套接字、绑定IP地址、申请广播权限、创建一个接收线程
bool UdpNet::InitNet()
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
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
	addrServer.sin_port = htons(4321);//将整型变量从主机字节序转换成网络字节序
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
	//4.申请广播权限
	BOOL bval = true;
	setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bval, sizeof(bval));
	//TODO:5.创建接收线程
	//CreateThread是WIN API，退出使用的是ExitThread
	// 如果在线程中使用了strcpy这类C++运行时库函数，会创建内存块，但是在ExitThread退出线程时，不会回收创建的内存块，会造成内存泄漏
	// _beginthreadex，退出使用的是_endthreadex，会回收内存空间，再调用ExitThread退出线程
	m_hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}
unsigned int  _stdcall UdpNet::RecvThread(void* Ipvoid)
{
	UdpNet* pThis = (UdpNet*)Ipvoid;
	pThis->RecvData();
	return 0;
}
//关闭网络,关闭套接字，加载库 
void UdpNet::UnInitNet()
{
	m_isStop = true;//尝试退出线程循环
//TODO:关闭线程
	if (m_hThreadHendle)
	{
		//等待一会，查看线程是否退出
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hThreadHendle, 100))
		{//如果线程没有自己结束，就杀死线程
			TerminateThread(m_hThreadHendle, -1);
		}
		//关闭句柄
		CloseHandle(m_hThreadHendle);
		m_hThreadHendle = NULL;
	}
	//关闭套接字
	if (m_socket && m_socket != INVALID_SOCKET) 
	{
		closesocket(m_socket);
	}
	//卸载库
	WSACleanup();
}
//发送数据
bool UdpNet::SendData(long ISendIp, char* buf, int nLen)
{
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(_DEF_UDP_PORT);
	addrServer.sin_addr.S_un.S_addr = ISendIp;
	if (sendto(m_socket, buf, nLen, 0, (sockaddr*)&addrServer, sizeof(addrServer)) <= 0)
	{
		cout << "sendto error:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
//接收数据
void UdpNet::RecvData()
{
	char recvBuf[_DEF_UDP_RECVBUF_LEN] = "";
	int nRecvNum = 0;
	sockaddr_in addrClient;
	int addrClientSize = sizeof(addrClient);
	while (!m_isStop)
	{
		nRecvNum = recvfrom(m_socket, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&addrClient, &addrClientSize);
		if (nRecvNum > 0)
		{
			//接收到数据
			char* packBuf = new char[nRecvNum];
			memcpy(packBuf, recvBuf, nRecvNum);
			if (m_pMediator) 
			{
				//把数据传递给中介者类
				m_pMediator->DealData(addrClient.sin_addr.S_un.S_addr, packBuf, nRecvNum);
				//TODO:回收packBuf，在处理完数据以后
			}
		}
	}
}
