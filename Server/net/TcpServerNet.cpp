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
	UnInitNet();
}

/*Initialize the network load library, create sockets, bind IP addresses,
 *apply for broadcast rights, and create a receiver thread*/
bool TcpServerNet::InitNet()
{   
	//Load the library
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
	//Create the socket
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
	/*
	 * Bind the ip address, use the TCP port number, and bind any NIC to the server
	 */
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	//Converts integer variables from host byte order to network byte order
	addrServer.sin_port = htons(_DEF_TCP_PORT);
	//Any NIC needs to be bound to the server
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
	/*
	 * Listening: The primary socket is used for listening. The maximum length of the queue to be processed is 0.
	 * If the return value is SOCKET_ERROR, the network is closed
	 */
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
	//Create the receiving thread and wait for the client to connect
	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &AcceptThread, this, 0, NULL);
	if (handle)
	{
		m_hThreadHendleList.push_back(handle);
	}
	return true;
}

//The thread that accepts the client connection
unsigned int  _stdcall TcpServerNet::AcceptThread(void* Ipvoid)
{
	/*
	 *Once the network IO model receives a connection, each client needs a thread
	 *
	 */
	TcpServerNet* IpThis = (TcpServerNet*)Ipvoid;
	sockaddr_in clientAddr;
	int clientAddrSize=sizeof(clientAddr);
	 unsigned int threadId = 0;
	while (!IpThis->m_isStop)
	{
		//Accept client connections
		SOCKET sock = accept(IpThis->m_sock, (sockaddr*)&clientAddr, &clientAddrSize);
		cout << "ip:" << inet_ntoa(clientAddr.sin_addr)<<"connect" << endl;
		HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)IpThis, 0, &threadId);
		//Save the thread handle
		IpThis->m_mapThreadIdSock[threadId]=sock;
		if (handle)
		{
			IpThis->m_hThreadHendleList.push_back(handle);
		}
	}
	return 0;
}

unsigned int  _stdcall TcpServerNet::RecvThread(void* Ipvoid)
{
	TcpServerNet* pThis = (TcpServerNet*)Ipvoid;
	pThis->RecvData();
	return 0;
}

// Close the network, close the socket, and load the library
void TcpServerNet::UnInitNet()
{
	//Out of the thread
	m_isStop = true;
	//Close the thread
	for (auto ite=m_hThreadHendleList.begin();ite != m_hThreadHendleList.end();) {
		HANDLE handle = *ite;
		//Wait to see if the thread exits
		if (WAIT_TIMEOUT == WaitForSingleObject(handle, 100)) {
        //If the thread does not end on its own, the thread is killed
			TerminateThread(handle, -1);
		}
		//Close the handle
		CloseHandle(handle);
		handle = NULL;
	}
	//Close the socket
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
	//Uninstall the library
	WSACleanup();
}

//To send data
bool TcpServerNet::SendData(long ISendIp, char* buf, int nLen)
{
	//1¡¢Calibration parameters
	if (!buf || nLen <= 0){
		cout << "TcpServer::SendData parameter error" << endl;
		return false;

	}
	//2¡¢The size of the packet sent first
	if (send(ISendIp, (char*)&nLen, sizeof(int), 0) <= 0){
		cout << "TcpServer::SendData" << WSAGetLastError() << endl;
		return false;
	}
	//3¡¢Redistribute the packet content
	if (send(ISendIp, buf, nLen, 0) <= 0){
		cout << "TcpServer::SendData" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//Receive data
void TcpServerNet::RecvData()
{
	int nRecvNum = 0;
	int packSize = 0;
	int offset = 0;
	/*
	 * Sleep for 100ms because the thread is created and running,
	 * but it takes a while to put the socket into the map
	 */
	Sleep(100);
	//Get the socket that communicates with the client from the map using the thread id to get the thread ID
	unsigned int threadId = GetCurrentThreadId();
	//Fetch the socket according to the thread Id
	SOCKET sock = INVALID_SOCKET;
	if (m_mapThreadIdSock.find(threadId) != m_mapThreadIdSock.end()){
		sock = m_mapThreadIdSock[threadId];
	}
	//Check whether the socket is valid. If the socket is invalid, exit the thread directly
	if (!sock || INVALID_SOCKET == sock) {
		cout << "TcpServer::RecvData invalid sock" << endl;
		return;
	}
	//Receive data
	while (!m_isStop){
		//Gets the socket that communicates with the client
		Sleep(100);
		SOCKET sock = m_mapThreadIdSock[GetCurrentThreadId()];
		//Check the validity of the socket
		if (!sock || sock == INVALID_SOCKET){
			return;
		}
		while (!m_isStop){
			//Take the packet size first, which is an int value
			nRecvNum = recv(sock, (char*)&packSize, sizeof(int), 0);
			if (nRecvNum <= 0) {
				break;
			}
			//Offset zero
			offset = 0;
			char* packBuf = new char[packSize];
			/*
			 * Receives the contents of a package in a loop. packSize records how much data is not received in a package,
			 * and offset records how much data has been received in a package
			 */
			while (packSize) {
				nRecvNum = recv(sock, packBuf + offset, packSize, 0);
				packSize -= nRecvNum;
				offset += nRecvNum;
			}
			//After receiving a packet, send it to the mediator class
			if (m_pMediator) {
				this->m_pMediator->DealData(sock, packBuf, offset);
				cout << "TcpServerNet::RecvData recv" << endl;
			}
			else if (0 == nRecvNum || 10054 == WSAGetLastError()) {
				cout << "TcpServerNet::RecvData close connection" << endl;
				break;
			}
			else {
				cout << "TcpServerNet::RecvData error" << endl;
			}
			offset = 0;
		}
	}
}