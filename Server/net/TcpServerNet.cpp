#include"packDef.h"
#include"INetMediator.h"
#include<process.h>
#include "TcpServerNet.h"
#include "TcpClientNet.h"
TcpServerNet::TcpServerNet(INetMediator* pMediator) :m_sock(INVALID_SOCKET), m_isStop(false)
{
	m_pMediator = pMediator;
}

TcpServerNet::~TcpServerNet()
{
	TcpServerNet::UnInitNet();
}

//初始化网络 加载库、创建套接字、绑定IP地址、申请广播权限、创建一个接收线程
bool TcpServerNet::InitNet()
{   
	//加载库
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
	//创建套接字
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sock) {
		cout << "socket error:" << WSAGetLastError() << endl;
		closesocket(m_sock);
		WSACleanup();
		return false;
	}
	else {
		cout << "socket success." << endl;
	}
	//绑定ip地址，使用TCP端口号，服务器绑定任意网卡
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	//将整型变量从主机字节序转换成网络字节序
	addrServer.sin_port = htons(_DEF_TCP_PORT);
	//服务器需要绑定任意网卡
	addrServer.sin_addr.S_un.S_addr = inet_addr(_DEF_TCP_SERVER_IP);
	err = bind(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "bind error:" << WSAGetLastError() << endl;
		closesocket(m_sock);
		WSACleanup();
		return false;
	}
	else {
		cout << "bind success." << endl;
	}
	//监听：使用主套接字进行监听，待处理连接队列的最大长度为0，判断返回值为SOCKRT_ERROR，则关闭网络返回
	err = listen(m_sock, 10);
	if (SOCKET_ERROR == err) {
		cout << "listen error" << WSAGetLastError() << endl;
		closesocket(m_sock);
		WSACleanup();
		return false;
	}
	else{
		printf("bind succeed.\n");
	}
	//TODO:5.创建接收线程，等待客户端连接
	//CreateThread是WIN API，退出使用的是ExitThread ,如果在线程中使用了strcpy这类C++运行时库函数，会创建内存块，但是在ExitThread退出线程时，不会回收创建的内存块，会造成内存泄漏
	// _beginthreadex，退出使用的是_endthreadex，会回收内存空间，再调用ExitThread退出线程,返回的线程句柄，如果句柄存在，把句柄存入list中管理
	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &AcceptThread, this, 0, NULL);
	if (handle)
	{
		m_h_thread_hendle_list_.push_back(handle);
	}
	return true;
}

//接受客户端连接的线程
unsigned int  _stdcall TcpServerNet::AcceptThread(void* ipvoid)
{
	//网络IO模型 接收连接之后，每个客户端需要一个线程
	TcpServerNet* IpThis = (TcpServerNet*)ipvoid;
	sockaddr_in clientAddr;
	int clientAddrSize=sizeof(clientAddr);
	 unsigned int threadId = 0;
	while (!IpThis->m_isStop)
	{
		//1、接受客户端连接
		SOCKET sock = accept(IpThis->m_sock, (sockaddr*)&clientAddr, &clientAddrSize);
		//打印日志
		cout << "ip:" << inet_ntoa(clientAddr.sin_addr)<<"connect" << endl;
		//2、给来连接客户端创建一个接收数据的线程
		//每一个客户端会对应一个线程 一个套接字 --> 线程和套接字也是对应的
		//可以在创建线程的时候，把线程id 和套接字 绑定在一起 形成映射 m_mapThreadIdSocket
		HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)IpThis, 0, &threadId);
		//保存线程句柄
		IpThis->m_mapThreadIdSock[threadId]=sock;
		//保存<threadID,socket>
		if (handle)
		{
			IpThis->m_h_thread_hendle_list_.push_back(handle);
		}
	}
	return 0;
}

unsigned int  _stdcall TcpServerNet::RecvThread(void* ipvoid)
{
	TcpServerNet* pThis = (TcpServerNet*)ipvoid;
	pThis->ReceiveData();
	return 0;
}

//关闭网络,关闭套接字，加载库 
void TcpServerNet::UnInitNet()
{
	//退出线程
	m_isStop = true;//尝试退出线程循环
	//TODO:关闭线程
	for (auto ite=m_h_thread_hendle_list_.begin();ite != m_h_thread_hendle_list_.end();) {
		HANDLE handle = *ite;
		//等待一会，查看线程是否退出
		if (WAIT_TIMEOUT == WaitForSingleObject(handle, 100)) {//如果线程没有自己结束，就杀死线程
			TerminateThread(handle, -1);
		}
		//关闭句柄
		CloseHandle(handle);
		handle = NULL;
	}
	//关闭套接字
	if (m_sock && INVALID_SOCKET != m_sock) {
		closesocket(m_sock);
	}
	SOCKET sock = INVALID_SOCKET;
	for (auto ite = m_mapThreadIdSock.begin(); ite != m_mapThreadIdSock.end();)
	{
		sock = ite->second;
		if (sock && INVALID_SOCKET != sock)
		{
			closesocket(sock);
		}
		ite = m_mapThreadIdSock.erase(ite);
	}
	//卸载库
	WSACleanup();
}

//发送数据
bool TcpServerNet::SendData(long ISendIp, char* buf, int nLen)
{
	//基于字节流有粘包问题
	//1、校验参数
	if (!buf || nLen <= 0){
		cout << "TcpServer::SendData parameter error" << endl;
		return false;

	}
	//2、先发包大小
	if (send(ISendIp, (char*)&nLen, sizeof(int), 0) <= 0){
		cout << "TcpServer::SendData" << WSAGetLastError() << endl;
		return false;
	}
	//3、再发包内容
	if (send(ISendIp, buf, nLen, 0) <= 0){
		cout << "TcpServer::SendData" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//接收数据
void TcpServerNet::ReceiveData()
{
	int nRecvNum = 0;
	int packSize = 0;
	int offset = 0;
	//休眠100ms，因为线程是创建及运行，但是把socket存入map需要一点时间
	Sleep(100);
	//1、通过线程id从map中取得与客户端通信的套接字，获取线程ID
	unsigned int threadId = GetCurrentThreadId();
	//根据线程Id取出socket
	SOCKET sock = INVALID_SOCKET;
	if (m_mapThreadIdSock.find(threadId) != m_mapThreadIdSock.end()){
		sock = m_mapThreadIdSock[threadId];
	}
	//2、判断socket是否有效，无效直接退出线程
	if (!sock || INVALID_SOCKET == sock) {
		cout << "TcpServer::ReceiveData invalid sock" << endl;
		return;
	}
	//3、接收数据
	while (!m_isStop){
		// 1、获取与客户端通信的socket
		Sleep(100);
		SOCKET sock = m_mapThreadIdSock[GetCurrentThreadId()];
		// 2、判断socket的合法性
		if (!sock || sock == INVALID_SOCKET){
			return;
		}
		while (!m_isStop){
			//先接包大小，包大小是一个int值
			nRecvNum = recv(sock, (char*)&packSize, sizeof(int), 0);
			if (nRecvNum <= 0) {
				break;
			}
			//offset清零
			offset = 0;
			char* packBuf = new char[packSize];
			//循环接收包内容
			//packSize记录的是一个包中还有多少数据没有接收到，offset记录的是一个包中累计已经接收到多少数据
			while (packSize) {
				nRecvNum = recv(sock, packBuf + offset, packSize, 0);
				packSize -= nRecvNum;
				offset += nRecvNum;
			}
			//接收完一个数据包，发给中介者类
			if (m_pMediator) {
				this->m_pMediator->DealData(sock, packBuf, offset);
				cout << "TcpServerNet::ReceiveData recv" << endl;
			}
			else if (0 == nRecvNum || 10054 == WSAGetLastError()) {
				cout << "TcpServerNet::ReceiveData close connection" << endl;
				break;
			}
			else {
				cout << "TcpServerNet::ReceiveData error" << endl;
			}
			offset = 0;
		}
	}
}