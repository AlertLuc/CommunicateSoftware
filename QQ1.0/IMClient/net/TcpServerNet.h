#pragma once
#include"INet.h"
#include<map>
#include<list>
class TcpServerNet :public INet
{
public:
	TcpServerNet(INetMediator* pMediator);
	~TcpServerNet();
	// 初始化网络
	virtual bool InitNet();
	// 关闭网络
	virtual void UnInitNet();
	//发送数据
	bool SendData(long ISendIp, char* buf, int nLen);
protected:
	//接收数据 
	void RecvData();
	//接收连接的线程函数
	static unsigned int  _stdcall AcceptThread(void* Ipvoid);
	//接收数据的线程函数
	static unsigned int  _stdcall RecvThread(void* Ipvoid);
	SOCKET m_socket;//监听的socket
	//管理线程id和socket
	map<unsigned int, SOCKET>m_mapThreadIdToSocket;
	list<HANDLE>m_hThreadHendleList;
	HANDLE m_hThreadHendle;//控制接收线程
	bool m_isStop;
};
