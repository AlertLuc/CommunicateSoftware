#include"TcpServerMediator.h"
#include "TcpServerNet.h"
#include<iostream>
using namespace std;
#include<string>
TcpServerMediator::TcpServerMediator()
{
	m_pNet = new TcpServerNet(this);
}
TcpServerMediator::~TcpServerMediator()
{
	//回收资源
	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = NULL;
	}
}
//开启网络
bool TcpServerMediator::OpenNet()
{
	if (!m_pNet->InitNet())
	{
		return false;
	}
	return true;
}
//关闭网络
void TcpServerMediator::CloseNet()
{
	m_pNet->InitNet();
}
//发送数据
bool TcpServerMediator::SendData(long ISendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(ISendIp, buf, nLen))
	{
		return false;
	}
	return true;
}
//处理数据
#include<iostream>
void TcpServerMediator::DealData(long ISendIp, char* buf, int nLen)
{
	std::cout << buf << std::endl; 
	SendData(ISendIp, buf, nLen);
}
