#pragma once
#include"INet.h"
#include "UdpMediator.h"
class UdpNet :public INet
{
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet();
	// 初始化网络
	virtual bool InitNet();
	// 关闭网络
	virtual void UnInitNet();
	//发送数据
	bool SendData(long ISendIp, char* buf, int nLen);
protected:
	//接收数据 
	void RecvData();
	//接收数据的线程函数
	static unsigned int  _stdcall RecvThread(void* Ipvoid);
	SOCKET m_socket;
	HANDLE m_hThreadHendle;//控制接收线程
	bool m_isStop;
};
//静态就不依赖类存在了