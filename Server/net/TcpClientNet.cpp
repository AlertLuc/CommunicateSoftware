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

//��ʼ������ ���ؿ⡢�����׽��֡���IP��ַ������㲥Ȩ�ޡ�����һ�������߳�
//TCP��Ҫ�޸ĵĵط���1������Socketʹ��TCPЭ�飻2�����ù㲥Ȩ��ȥ��������Ҫ�ˣ�3�����ӷ��������󶨷�����
//IP��ַ�Ͷ˿ںţ�����connect�������ӷ�����
bool TcpClientNet::InitNet()
{
	//1.ѡ��Ŀ----���ؿ⣬��ץ��
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
	//2.����---�����׽���
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sock) {
		cout << "socket error:" << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "socket success." << endl;
	}
	//3.���ӷ�����
	sockaddr_in addrServer;
	// IPV4Э����
	addrServer.sin_family = AF_INET;
	//htons������ת���������ֽ���
	addrServer.sin_port = htons(_DEF_TCP_PORT);//�����ͱ����������ֽ���ת���������ֽ���
	//�󶨷�����IP��ַ
	addrServer.sin_addr.S_un.S_addr = inet_addr(_DEF_TCP_SERVER_IP);//��������Ҫ����������
	//inet_addr:��IP��ַ���ַ�������ת����u_long����
	err = connect(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
	if (SOCKET_ERROR == err) {
		cout << "connect error:" << WSAGetLastError() << endl;	
		closesocket(m_sock);
		return false;
	}
	else {
		cout << "bind success." << endl;
	}
	//��������--�����߳� C/C++RunTime�� strcpy�����ڴ��
	//CreateThread�������̲߳�������ڴ�飬����ڴ�й©
	//ExitThread�˳��߳� _brginthreadex�ײ�Ҳ�ǵ��õ�CreateThread,�˳�ʱ����ExitThread,���һ��մ����ڴ��

	//TODO:5.���������߳�
	//CreateThread��WIN API���˳�ʹ�õ���ExitThread
	// ������߳���ʹ����strcpy����C++����ʱ�⺯�����ᴴ���ڴ�飬������ExitThread�˳��߳�ʱ��������մ������ڴ�飬������ڴ�й©
	// _beginthreadex���˳�ʹ�õ���_endthreadex��������ڴ�ռ䣬�ٵ���ExitThread�˳��߳�
	m_hThreadHendle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}

auto _stdcall TcpClientNet::RecvThread(void* Ipvoid) -> unsigned int
{
	TcpClientNet* IpThis = (TcpClientNet*)Ipvoid;
	IpThis->ReceiveData();
	return 0;
}

//�ر�����,�ر��׽��֣����ؿ� 
void TcpClientNet::UnInitNet()
{
	//�����˳��߳�ѭ��
	m_isStop = true;
    //Close the thread
	if (m_hThreadHendle) {
		//�ȴ�һ�ᣬ�鿴�߳��Ƿ��˳�
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hThreadHendle, 100)) {
			//����߳�û���Լ���������ɱ���߳�
			TerminateThread(m_hThreadHendle, -1);
		}
		//�رվ��
		CloseHandle(m_hThreadHendle);
		m_hThreadHendle = NULL;
	}
	//�ر��׽���
	if (m_sock && INVALID_SOCKET != m_sock) {
		closesocket(m_sock);
	}
	//ж�ؿ�
	WSACleanup();
}

//�������ݣ�1�����ж���������ĺϷ��ԣ����bufΪ�ջ���nLenС�ڵ���0���Ͳ��ô����ˣ�
//2��Ϊ�˷�ֹմ�����⣬�ȷ��Ͱ���С���ٷ��Ͱ����ݡ�
//TCP����ʹ��send��������������ʹ�õ�socket�������洴����m_sock

//��������
bool TcpClientNet::SendData(long ISendIp, char* buf, int nLen)
{
	//�����ֽ�����ճ������
	//1��У�����
	//�жϴ�������Ϸ���
	if (!buf || nLen <= 0)
	{
		cout << "TcpClient::SendData parameter error" << endl;
		return false;
	}
	//2����ֹճ�����ȷ�����С
	//����m_sock�͵���ISendip
	if (send(m_sock, (char*)&nLen, sizeof(int), 0) <= 0)
	{
		cout << "TcpClient::SendData" << WSAGetLastError() << endl;
		return false;
	}
	//3���ٷ�������
	if (send(m_sock, buf, nLen, 0) <= 0)
	{
	cout << "TcpClient::SendData" << WSAGetLastError() << endl;
	return false;
    }
	return true;
}

//1������һ�������洢���Ĵ�С��һ���������Ž��շ���ֵ��һ����������ƫ����
// 2����ѭ���н������ݣ��Ƚ��հ���С���ٽ��հ�������
// 2.1��ʹ��recv�����������ݣ��жϷ���ֵС�ڵ���0��ֱ�ӽ������գ�˵�������˵������Ѿ�������
// 2.2������һ����յ��İ���С��ô��Ŀռ䣬ѭ�����հ����ݣ���Ϊ���ݿ��ܲ���һ�ν�����ȫ
// 2.3��ÿ�ν��������ݣ����ݷ���ֵ����ƫ���������ص���ʵ�ʽ��յ��ֽ����������ʵ�ʽ��յ�����������0����
// ����С-ʵ�ʽ��յ����ݵĴ�С��ƫ����+ʵ�ʽ��մ�С��Ȼ�����ѭ��
// 3���˴����ݽ�������Ժ󣬵����н��ߵĴ������ݺ����������ݴ��ݸ��н����࣬�������е�����ȡ����
// ��Ҫ�ں�����������Ķѿռ�
//��������
void TcpClientNet::ReceiveData()
{
	int nRecvNum = 0;
	//�洢����С
	int packSize = 0;
	//ƫ�����������ۼƽ��ܵİ��Ĵ�С
	int offset = 0;
	while (!m_isStop)
	{
		//�ȽӰ���С������С��һ��intֵ���ٽ������ݰ�
		nRecvNum = recv(m_sock, (char*)&packSize, sizeof(int), 0);
		//�ӽ��ջ�������������С
		if (nRecvNum <= 0) {
			cout << "TcpClient::ReceiveData" << WSAGetLastError() << endl;
			break;
		}
		char* packBuf = new char[packSize];
		//ѭ�����հ�����
		//packSize��¼����һ�����л��ж�������û�н��յ���offset��¼����һ�������ۼ��Ѿ����յ���������
		while (packSize) {
			nRecvNum = recv(m_sock, packBuf + offset, packSize, 0);
			if (nRecvNum > 0) {//���ݿ��ܲ���һ�ν�����ȫ����Ҫѭ������
				packSize -= nRecvNum;
				offset += nRecvNum;
			}
		}
		//������һ�����ݰ��������н�����
		//��Ҫ�������������buf�����ռ�
		this->m_pMediator->DealData(m_sock, packBuf, offset);
		//����new������packBuf
		//offset����
		offset = 0;
	}
}



