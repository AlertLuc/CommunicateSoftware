#pragma once
#include"INet.h"
#include "UdpMediator.h"
class UdpNet :public INet
{
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet() override;
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
	static unsigned int  _stdcall recv_thread(void* ipvoid);
	SOCKET m_socket;
	//���ƽ����߳�
	HANDLE m_h_thread_hendle_;
	bool m_isStop;
};
