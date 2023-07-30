#pragma once
#include"INet.h"
#include "UdpMediator.h"
class UdpNet :public INet
{
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet() override;
	// 初始化网络
	bool InitNet() override;
	// 关闭网络
	void UnInitNet() override;
	//发送数据
	bool SendData(long ISendIp, char* buf, int nLen) override;
protected:
	//接收数据 
	void ReceiveData() override;
	//接收数据的线程函数
	static unsigned int  _stdcall recv_thread(void* ipvoid);
	SOCKET m_socket;
	//控制接收线程
	HANDLE m_h_thread_hendle_;
	bool m_isStop;
};
