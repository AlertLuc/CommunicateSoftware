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

//��ʼ������ ���ؿ⡢�����׽��֡���IP��ַ������㲥Ȩ�ޡ�����һ�������߳�
bool TcpServerNet::InitNet()
{   
	//���ؿ�
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
	//�����׽���
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
	//��ip��ַ��ʹ��TCP�˿ںţ�����������������
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	//�����ͱ����������ֽ���ת���������ֽ���
	addrServer.sin_port = htons(_DEF_TCP_PORT);
	//��������Ҫ����������
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
	//������ʹ�����׽��ֽ��м��������������Ӷ��е���󳤶�Ϊ0���жϷ���ֵΪSOCKRT_ERROR����ر����緵��
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
	//TODO:5.���������̣߳��ȴ��ͻ�������
	//CreateThread��WIN API���˳�ʹ�õ���ExitThread ,������߳���ʹ����strcpy����C++����ʱ�⺯�����ᴴ���ڴ�飬������ExitThread�˳��߳�ʱ��������մ������ڴ�飬������ڴ�й©
	// _beginthreadex���˳�ʹ�õ���_endthreadex��������ڴ�ռ䣬�ٵ���ExitThread�˳��߳�,���ص��߳̾�������������ڣ��Ѿ������list�й���
	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &AcceptThread, this, 0, NULL);
	if (handle)
	{
		m_h_thread_hendle_list_.push_back(handle);
	}
	return true;
}

//���ܿͻ������ӵ��߳�
unsigned int  _stdcall TcpServerNet::AcceptThread(void* ipvoid)
{
	//����IOģ�� ��������֮��ÿ���ͻ�����Ҫһ���߳�
	TcpServerNet* IpThis = (TcpServerNet*)ipvoid;
	sockaddr_in clientAddr;
	int clientAddrSize=sizeof(clientAddr);
	 unsigned int threadId = 0;
	while (!IpThis->m_isStop)
	{
		//1�����ܿͻ�������
		SOCKET sock = accept(IpThis->m_sock, (sockaddr*)&clientAddr, &clientAddrSize);
		//��ӡ��־
		cout << "ip:" << inet_ntoa(clientAddr.sin_addr)<<"connect" << endl;
		//2���������ӿͻ��˴���һ���������ݵ��߳�
		//ÿһ���ͻ��˻��Ӧһ���߳� һ���׽��� --> �̺߳��׽���Ҳ�Ƕ�Ӧ��
		//�����ڴ����̵߳�ʱ�򣬰��߳�id ���׽��� ����һ�� �γ�ӳ�� m_mapThreadIdSocket
		HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)IpThis, 0, &threadId);
		//�����߳̾��
		IpThis->m_mapThreadIdSock[threadId]=sock;
		//����<threadID,socket>
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

//�ر�����,�ر��׽��֣����ؿ� 
void TcpServerNet::UnInitNet()
{
	//�˳��߳�
	m_isStop = true;//�����˳��߳�ѭ��
	//TODO:�ر��߳�
	for (auto ite=m_h_thread_hendle_list_.begin();ite != m_h_thread_hendle_list_.end();) {
		HANDLE handle = *ite;
		//�ȴ�һ�ᣬ�鿴�߳��Ƿ��˳�
		if (WAIT_TIMEOUT == WaitForSingleObject(handle, 100)) {//����߳�û���Լ���������ɱ���߳�
			TerminateThread(handle, -1);
		}
		//�رվ��
		CloseHandle(handle);
		handle = NULL;
	}
	//�ر��׽���
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
	//ж�ؿ�
	WSACleanup();
}

//��������
bool TcpServerNet::SendData(long ISendIp, char* buf, int nLen)
{
	//�����ֽ�����ճ������
	//1��У�����
	if (!buf || nLen <= 0){
		cout << "TcpServer::SendData parameter error" << endl;
		return false;

	}
	//2���ȷ�����С
	if (send(ISendIp, (char*)&nLen, sizeof(int), 0) <= 0){
		cout << "TcpServer::SendData" << WSAGetLastError() << endl;
		return false;
	}
	//3���ٷ�������
	if (send(ISendIp, buf, nLen, 0) <= 0){
		cout << "TcpServer::SendData" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//��������
void TcpServerNet::ReceiveData()
{
	int nRecvNum = 0;
	int packSize = 0;
	int offset = 0;
	//����100ms����Ϊ�߳��Ǵ��������У����ǰ�socket����map��Ҫһ��ʱ��
	Sleep(100);
	//1��ͨ���߳�id��map��ȡ����ͻ���ͨ�ŵ��׽��֣���ȡ�߳�ID
	unsigned int threadId = GetCurrentThreadId();
	//�����߳�Idȡ��socket
	SOCKET sock = INVALID_SOCKET;
	if (m_mapThreadIdSock.find(threadId) != m_mapThreadIdSock.end()){
		sock = m_mapThreadIdSock[threadId];
	}
	//2���ж�socket�Ƿ���Ч����Чֱ���˳��߳�
	if (!sock || INVALID_SOCKET == sock) {
		cout << "TcpServer::ReceiveData invalid sock" << endl;
		return;
	}
	//3����������
	while (!m_isStop){
		// 1����ȡ��ͻ���ͨ�ŵ�socket
		Sleep(100);
		SOCKET sock = m_mapThreadIdSock[GetCurrentThreadId()];
		// 2���ж�socket�ĺϷ���
		if (!sock || sock == INVALID_SOCKET){
			return;
		}
		while (!m_isStop){
			//�ȽӰ���С������С��һ��intֵ
			nRecvNum = recv(sock, (char*)&packSize, sizeof(int), 0);
			if (nRecvNum <= 0) {
				break;
			}
			//offset����
			offset = 0;
			char* packBuf = new char[packSize];
			//ѭ�����հ�����
			//packSize��¼����һ�����л��ж�������û�н��յ���offset��¼����һ�������ۼ��Ѿ����յ���������
			while (packSize) {
				nRecvNum = recv(sock, packBuf + offset, packSize, 0);
				packSize -= nRecvNum;
				offset += nRecvNum;
			}
			//������һ�����ݰ��������н�����
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