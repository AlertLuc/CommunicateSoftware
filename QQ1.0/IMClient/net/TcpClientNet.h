#pragma once
#include"INet.h"
class TcpClientNet :public INet
{
public:
	TcpClientNet(INetMediator* pMediator);
	~TcpClientNet();
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
	HANDLE m_hThreadHendle;
	bool m_isStop;
};
