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
	static unsigned int  _stdcall AcceptThread(void* ipvoid);
	static unsigned int  _stdcall RecvThread(void* ipvoid);
	SOCKET m_sock;
	//控制接收线程  // NOLINT(clang-diagnostic-invalid-utf8)
	list <HANDLE> m_h_thread_hendle_list_;
	bool m_isStop;
	map<unsigned int, SOCKET>m_mapThreadIdSock;
};
