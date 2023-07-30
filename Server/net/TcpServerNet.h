#pragma once
#include"INet.h"
#include "TcpServerMediator.h"
#include <List>
#include<map>
class TcpServerNet :public INet
{
public:
	TcpServerNet(INetMediator* pMediator);
	~TcpServerNet() override;
	// ��ʼ������
	 bool InitNet() override;
	 // �ر�����
	 void UnInitNet() override;
	 //��������
	bool SendData(long ISendIp, char* buf, int nLen) override;
protected:
	//�������� 
	void ReceiveData() override;
	//�������ݵ��̺߳���
	static unsigned int  _stdcall AcceptThread(void* ipvoid);
	static unsigned int  _stdcall RecvThread(void* ipvoid);
	SOCKET m_sock;
	//���ƽ����߳�  // NOLINT(clang-diagnostic-invalid-utf8)
	list <HANDLE> m_h_thread_hendle_list_;
	bool m_isStop;
	map<unsigned int, SOCKET>m_mapThreadIdSock;
};
