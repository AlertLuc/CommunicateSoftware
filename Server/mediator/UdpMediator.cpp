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
	if (m_pNet) {
		delete m_pNet;
		m_pNet = nullptr;
	}
}

bool UdpMediator::OpenNet()
{
	if (!m_pNet->InitNet()) {
		return false;
	}
	return true;
}

void UdpMediator::CloseNet()
{
	m_pNet->UnInitNet();
}

bool UdpMediator::SendData(long ISendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(ISendIp, buf, nLen)){
		return false;
	}
	return true;
}

void UdpMediator::DealData(long ISendIp, char* buf, int nLen)
{
	std::cout << buf << std::endl;
}

