#include"UdpNet.h"
#include"UdpMediator.h"
#include"packDef.h"
#include"INetMediator.h"
#include<process.h>
#include "TcpServerNet.h"
#include "TcpClientNet.h"
UdpNet::UdpNet(INetMediator* pMediator) :m_socket(INVALID_SOCKET), m_hThreadHendle(nullptr), m_isStop(false)
{
	m_pMediator = pMediator;
}

UdpNet::~UdpNet()
{
	UdpNet::UnInitNet();
}

/*Initialize the network load library, create sockets, bind IP addresses,
 *apply for broadcast rights, and create a receiver thread*/
bool UdpNet::InitNet()
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
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2){
		printf("Could not find a usable version of Winsock.dll\n");
		return false;
	}
	else {
		printf("The Winsock 2.2 dll was found okay\n");
	}
	//Create the socket
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket) {
		cout << "socket error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "socket success." << endl;
	}
	//Binding an IP Address
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;

	addrServer.sin_port = htons(4321);//Converts integer variables from host byte order to network byte order
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;//Any NIC needs to be bound to the server
	err = bind(m_socket, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "bind error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "bind success." << endl;
	}
	//Applying for Broadcast Permission
	BOOL bval = true;
	setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bval, sizeof(bval));
	//Create the receiving thread
	m_hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}

unsigned int  _stdcall UdpNet::RecvThread(void* Ipvoid)
{
	UdpNet* pThis = (UdpNet*)Ipvoid;
	pThis->RecvData();
	return 0;
}

//Close the network, close the socket, and load the library
void UdpNet::UnInitNet()
{
	//Attempt to exit the thread loop
	m_isStop = true;
    //Close the thread
	if (m_hThreadHendle){
		//Wait to see if the thread exits
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hThreadHendle, 100)){
			TerminateThread(m_hThreadHendle, -1);
		}
		//Close the handle
		CloseHandle(m_hThreadHendle);
		m_hThreadHendle = NULL;
	}

	//Close the socket
	if (m_socket && m_socket != INVALID_SOCKET) {
		closesocket(m_socket);
	}

	//Uninstall the library
	WSACleanup();
}

//To send data
bool UdpNet::SendData(long ISendIp, char* buf, int nLen)
{
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(_DEF_UDP_PORT);
	addrServer.sin_addr.S_un.S_addr = ISendIp;
	if (sendto(m_socket, buf, nLen, 0, (sockaddr*)&addrServer, sizeof(addrServer)) <= 0){
		cout << "sendto error:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//Receive data
void UdpNet::RecvData()
{
	char recvBuf[_DEF_UDP_RECVBUF_LEN] = "";
	int nRecvNum = 0;
	sockaddr_in addrClient;
	int addrClientSize = sizeof(addrClient);
	while (!m_isStop){
		nRecvNum = recvfrom(m_socket, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&addrClient, &addrClientSize);
		if (nRecvNum > 0){
			//Data received
			char* packBuf = new char[nRecvNum];
			memcpy(packBuf, recvBuf, nRecvNum);
			if (m_pMediator) {
				//Pass the data to the mediator class
				m_pMediator->DealData(addrClient.sin_addr.S_un.S_addr, packBuf, nRecvNum);
				//Recycle packBuf, after processing the data
			}
		}
	}
}
