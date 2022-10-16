#pragma once
#include"INet.h"
#include "TcpServerMediator.h"
#include <List>
#include<map>
class TcpServerNet :public INet
{
public:
	TcpServerNet(INetMediator* pMediator);
	~TcpServerNet();
	 bool InitNet();
	 void UnInitNet();
	bool SendData(long ISendIp, char* buf, int nLen);
protected:
	void RecvData();
	//A thread function that receives data
	static unsigned int  _stdcall AcceptThread(void* Ipvoid);
	static unsigned int  _stdcall RecvThread(void* Ipvoid);
	SOCKET m_sock;
	//Control the receiving thread
	list <HANDLE> m_hThreadHendleList;
	bool m_isStop;
	map<unsigned int, SOCKET>m_mapThreadIdSock;
};
