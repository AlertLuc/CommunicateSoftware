#pragma once
#include"INetMediator.h"
class TcpClientMediator :public INetMediator
{
    Q_OBJECT
public:
	TcpClientMediator();
	~TcpClientMediator();
	//开启网络
	bool OpenNet();
	//关闭网络
	void CloseNet();
	//发送数据
	bool SendData(long ISendIp, char* buf, int nLen);
	//处理数据
	void DealData(long ISendIp, char* buf, int nLen);
signals:
    //发送接收到数据给kernel类
    void SIG_ReadyData(long ISendIp, char* buf, int nLen);
};
