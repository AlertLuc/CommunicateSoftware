#pragma once
#include"INetMediator.h"
class UdpMediator :public INetMediator
{
public:
	UdpMediator();
	~UdpMediator();
	//��������
	bool OpenNet();
	//�ر�����
	void CloseNet();
	//��������
	bool SendData(long ISendIp, char* buf, int nLen);
	//��������
	void DealData(long ISendIp, char* buf, int nLen);
};



