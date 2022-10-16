#include"TcpClientMediator.h"
#include "TcpClientNet.h"
#include<iostream>
#include<string>
TcpClientMediator::TcpClientMediator()
{
	 m_pNet = new TcpClientNet(this);
}

TcpClientMediator::~TcpClientMediator()
{
	if (m_pNet) {
		delete m_pNet;
		m_pNet = NULL;
	}
}

bool TcpClientMediator::OpenNet()
{
	if (!m_pNet->InitNet()) {
		return false;
	}
	return true;
}

void TcpClientMediator::CloseNet()
{
	m_pNet->UnInitNet();
}

bool TcpClientMediator::SendData(long ISendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(ISendIp, buf, nLen)) {
		return false;
	}
	return true;
}

void TcpClientMediator::DealData(long ISendIp, char* buf, int nLen)
{
    Q_EMIT SIG_ReadyData(ISendIp,buf,nLen);
}


