#include"UdpMediator.h"
#include "UdpNet.h"
#include<iostream>
#include<string>
UdpMediator::UdpMediator()
{
	m_pNet = new UdpNet(this);
}
UdpMediator::~UdpMediator()
{
	//回收资源
	if (m_pNet) 
	{
		delete m_pNet;
		m_pNet = NULL;
	}
}
//开启网络
bool UdpMediator::OpenNet()
{
	if (!m_pNet->InitNet()) 
	{
		return false;
	}
	return true;
}
//关闭网络
void UdpMediator::CloseNet()
{
	m_pNet->UnInitNet();
}
//发送数据
bool UdpMediator::SendData(long ISendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(ISendIp, buf, nLen))
	{
		return false;
	}
	return true;
}
//处理数据
void UdpMediator::DealData(long ISendIp, char* buf, int nLen)
{
	std::cout << buf << std::endl;
}

