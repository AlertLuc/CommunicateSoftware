#include"UdpNet.h"
#include"UdpMediator.h"
#include"packDef.h"
#include"INetMediator.h"
#include<process.h>
#include "TcpServerNet.h"
#include "TcpClientNet.h"
UdpNet::UdpNet(INetMediator* pMediator) :m_socket(INVALID_SOCKET), m_h_thread_hendle_(nullptr), m_isStop(false)
{
	m_pMediator = pMediator;
}

UdpNet::~UdpNet()
{
	UdpNet::UnInitNet();
}

//��ʼ������ ���ؿ⡢�����׽��֡���IP��ַ������㲥Ȩ�ޡ�����һ�������߳�  // NOLINT(clang-diagnostic-invalid-utf8)
bool UdpNet::InitNet()
{
	//1.ѡ��Ŀ----���ؿ�
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

	//2.����---�����׽���
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket) {
		cout << "socket error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "socket success." << endl;
	}
	
	//3.��̯---��IP��ַ
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;

	addrServer.sin_port = htons(4321);//�����ͱ����������ֽ���ת���������ֽ���
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;//��������Ҫ����������
	err = bind(m_socket, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "bind error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "bind success." << endl;
	}

	//4.����㲥Ȩ��
	BOOL bval = true;
	setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bval, sizeof(bval));

	//TODO:5.���������߳�
	//CreateThread��WIN API���˳�ʹ�õ���ExitThread
	// ������߳���ʹ����strcpy����C++����ʱ�⺯�����ᴴ���ڴ�飬������ExitThread�˳��߳�ʱ��������մ������ڴ�飬������ڴ�й©
	// _beginthreadex���˳�ʹ�õ���_endthreadex��������ڴ�ռ䣬�ٵ���ExitThread�˳��߳�
	m_h_thread_hendle_ = (HANDLE)_beginthreadex(NULL, 0, &recv_thread, this, 0, NULL);
	return true;
}

unsigned int  _stdcall UdpNet::recv_thread(void* ipvoid)
{
	UdpNet* pThis = (UdpNet*)ipvoid;
	pThis->ReceiveData();
	return 0;
}

//�ر�����,�ر��׽��֣����ؿ� 
void UdpNet::UnInitNet()
{
	//�����˳��߳�ѭ��
	m_isStop = true;
    //Close the thread
	if (m_h_thread_hendle_){
		//�ȴ�һ�ᣬ�鿴�߳��Ƿ��˳�
		if (WAIT_TIMEOUT == WaitForSingleObject(m_h_thread_hendle_, 100)){//����߳�û���Լ���������ɱ���߳�
			TerminateThread(m_h_thread_hendle_, -1);
		}
		//�رվ��
		CloseHandle(m_h_thread_hendle_);
		m_h_thread_hendle_ = nullptr;
	}

	//�ر��׽���
	if (!m_socket || m_socket == INVALID_SOCKET) {
		closesocket(m_socket);
	}

	//ж�ؿ�
	WSACleanup();  // NOLINT(clang-diagnostic-invalid-utf8)
}

//��������
auto UdpNet::SendData(long ISendIp, char* buf, int nLen) -> bool
{
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(_DEF_UDP_PORT);
	addrServer.sin_addr.S_un.S_addr = ISendIp;
	if (sendto(m_socket, buf, nLen, 0, reinterpret_cast<sockaddr*>(&addrServer), sizeof(addrServer)) <= 0){
		cout << "sendto error:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//��������
void UdpNet::ReceiveData()
{
	char rec_buf[_DEF_UDP_RECVBUF_LEN] = "";
	int nRecvNum = 0;
	sockaddr_in addr_client;
	int addr_client_size = sizeof(addr_client);
	while (!m_isStop){
		nRecvNum = recvfrom(m_socket, rec_buf, sizeof(rec_buf), 0, reinterpret_cast<sockaddr*>(&addr_client), &addr_client_size);
		if (nRecvNum > 0){
			//���յ�����
			auto packBuf = new char[nRecvNum];
			memcpy(packBuf, rec_buf, nRecvNum);
			if (m_pMediator)
				//�����ݴ��ݸ��н�����
				m_pMediator->DealData(addr_client.sin_addr.S_un.S_addr, packBuf, nRecvNum);  // NOLINT(clang-diagnostic-invalid-utf8)
				//TODO:����packBuf���ڴ����������Ժ�
		}
	}
}
