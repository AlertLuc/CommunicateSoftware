#pragma once
#include<QObject>
#include<iostream>
class INet;
class INetMediator:public QObject
{
    Q_OBJECT
public:
	INetMediator();
    virtual ~INetMediator();
	virtual bool OpenNet() = 0;
	virtual void CloseNet() = 0;
	virtual bool SendData(long ISendIp, char* buf, int nLen) = 0;
	virtual void DealData(long ISendIp, char* buf, int nLen) = 0;
protected:
    //Network interface pointer used to call network functions
    INet* m_pNet;
};
