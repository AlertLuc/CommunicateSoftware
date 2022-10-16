#pragma once
#include"INet.h"
#include "UdpMediator.h"
class UdpNet :public INet
{
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet();
	virtual bool InitNet();
	virtual void UnInitNet();
	bool SendData(long ISendIp, char* buf, int nLen);
protected:
	void RecvData();
	//A thread function that receives data
	static unsigned int  _stdcall RecvThread(void* Ipvoid);
	SOCKET m_socket;
	//Control the receiving thread
	HANDLE m_hThreadHendle;
	bool m_isStop;
};
