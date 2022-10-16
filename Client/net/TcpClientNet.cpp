#include"packDef.h"
#include"INetMediator.h"
#include<process.h>
#include "TcpClientNet.h"
TcpClientNet::TcpClientNet(INetMediator* pMediator):m_sock(INVALID_SOCKET), m_hThreadHendle(0), m_isStop(false)
{
	m_pMediator = pMediator;
}

TcpClientNet::~TcpClientNet()
{
	UnInitNet();
}

//Initialize the network load library, create sockets, bind IP addresses, apply for broadcast rights, and create a receiver thread
bool TcpClientNet::InitNet()
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
		return false;
	}
	else {
		cout << "socket success." << endl;
	}
    //Connecting to the Server
	sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;//The family of IPV4
    //htons convert integers to network byte order
    addrServer.sin_port = htons(_DEF_TCP_PORT);//Converts integer variables from host byte order to network byte order
    //Bind the IP address of the server
    addrServer.sin_addr.S_un.S_addr = inet_addr(_DEF_TCP_SERVER_IP);//Any NIC needs to be bound to the server
    //inet_addr: Converts an IP address from a string to a u_long
	err = connect(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "connect error:" << WSAGetLastError() << endl;	
		closesocket(m_sock);
		return false;
	}
	else {
		cout << "bind success." << endl;
	}
    //Create the receiving thread
	m_hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}

unsigned int  _stdcall TcpClientNet::RecvThread(void* Ipvoid)
{
	TcpClientNet* IpThis = (TcpClientNet*)Ipvoid;
	IpThis->RecvData();
	return 0;
}

//Close the network, close the socket, and load the library
void TcpClientNet::UnInitNet()
{
    m_isStop = true;//Attempt to exit the thread loop
    //Close the thread
	if (m_hThreadHendle) {
        //Wait to see if the thread exits
        if (WAIT_TIMEOUT == WaitForSingleObject(m_hThreadHendle, 100)) {
			TerminateThread(m_hThreadHendle, -1);
		}
        //Close the handle
		CloseHandle(m_hThreadHendle);
		m_hThreadHendle = NULL;
	}
    //Close the socket
	if (m_sock && INVALID_SOCKET != m_sock) {
		closesocket(m_sock);
	}
    //Uninstall the library
	WSACleanup();
}

//To send data
bool TcpClientNet::SendData(long ISendIp, char* buf, int nLen)
{
    //There is sticky packet problem based on byte stream
    //Calibration parameters
    //Determine the validity of the passed parameter
	if (!buf || nLen <= 0)
	{
		cout << "TcpClient::SendData parameter error" << endl;
		return false;
	}
    //To prevent sticky packets, send the packet size first
    //So m_sock is equal to ISendip
	if (send(m_sock, (char*)&nLen, sizeof(int), 0) <= 0)
	{
		cout << "TcpClient::SendData" << WSAGetLastError() << endl;
		return false;
	}
    //Redistribute the packet content
	if (send(m_sock, buf, nLen, 0) <= 0)
	{
	cout << "TcpClient::SendData" << WSAGetLastError() << endl;
	return false;
     }
	return true;
}

//Receive data
void TcpClientNet::RecvData()
{
	int nRecvNum = 0;
    int packSize = 0;//Storage package size
    int offset = 0;//Offset, which calculates the cumulative size of accepted packets
	while (!m_isStop)
	{
        //Receive the packet size, which is an int value, and then receive the packet
        nRecvNum = recv(m_sock, (char*)&packSize, sizeof(int), 0);
        //Copy packet sizes from the receive buffer
		if (nRecvNum <= 0) {
			cout << "TcpClient::RecvData" << WSAGetLastError() << endl;
			break;
		}
		char* packBuf = new char[packSize];
        //Loop receives packet contents
        //packSize records how much data has not been received in a package, and offset records how much data has been received in a package
        while (packSize) {
            nRecvNum = recv(m_sock, packBuf + offset, packSize, 0);
			if (nRecvNum > 0) {
				packSize -= nRecvNum;
				offset += nRecvNum;
			}
		}
        //After receiving a packet and sending it to the mediator class, you need to reclaim the buf heap space in this function
        this->m_pMediator->DealData(m_sock, packBuf, offset);
		offset = 0;
	}
}



