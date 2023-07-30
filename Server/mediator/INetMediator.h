#pragma once
#include<iostream>
class INet;
class INetMediator
{
public:
	INetMediator();
	virtual ~INetMediator();
	virtual bool OpenNet() = 0;
	virtual void CloseNet() = 0;
	virtual bool SendData(long ISendIp, char* buf, int nLen) = 0;
	virtual void DealData(long ISendIp, char* buf, int nLen) = 0;
protected:
	INet* m_pNet{};
};
