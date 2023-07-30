#pragma once
#include<iostream>
#include<QObject>
class INet;
class INetMediator:public QObject
{
    Q_OBJECT
public:
	INetMediator();
	virtual ~INetMediator();//使用时，父类指针指向子类，使用虚构函数
	 //开启网络
	virtual bool OpenNet() = 0;
	//关闭网络
	virtual void CloseNet() = 0;
	//发送数据
	virtual bool SendData(long ISendIp, char* buf, int nLen) = 0;
	//处理数据
	virtual void DealData(long ISendIp, char* buf, int nLen) = 0;
protected:
	INet* m_pNet;//网络接口指针，用于调用网络函数
};
