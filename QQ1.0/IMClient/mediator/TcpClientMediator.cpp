#include"TcpClientMediator.h"
#include "TcpClientNet.h"
//#include<iostream>
#include<string>
TcpClientMediator::TcpClientMediator()
{
	m_pNet = new TcpClientNet(this);
}

TcpClientMediator::~TcpClientMediator()
{
	//回收资源
	if (m_pNet) {
		delete m_pNet;
		m_pNet = NULL;
	}
}

//开启网络
bool TcpClientMediator::OpenNet()
{
	if (!m_pNet->InitNet()) {
		return false;
	}
	return true;
}

//关闭网络
void TcpClientMediator::CloseNet()
{
	m_pNet->UnInitNet();
}

//发送数据
bool TcpClientMediator::SendData(long ISendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(ISendIp, buf, nLen)){
		return false;
	}
	return true;
}

//处理数据
void TcpClientMediator::DealData(long ISendIp, char* buf, int nLen)
{
//	std::cout << buf << std::endl;
     Q_EMIT SIG_ReadyData(ISendIp, buf, nLen);
}
