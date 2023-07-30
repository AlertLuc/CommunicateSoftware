#include"TcpServerMediator.h"
#include "TcpServerNet.h"
#include<iostream>
#include<string>
#include"./../Kernel.h"
TcpServerMediator::TcpServerMediator()
{
	m_pNet = new TcpServerNet(this);
}

TcpServerMediator::~TcpServerMediator()
{
	//resource recovery
	if (m_pNet) {
		delete m_pNet;
		m_pNet = nullptr;
	}
}

bool TcpServerMediator::OpenNet()
{
	if (!m_pNet->InitNet()) {
		return false;
	}
	return true;
}

void TcpServerMediator::CloseNet()
{
	m_pNet->UnInitNet();
}

bool TcpServerMediator::SendData(long ISendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(ISendIp, buf, nLen)) {
		return false;
	}
	return true;
}

void TcpServerMediator::DealData(long ISendIp, char* buf, int nLen)
{	
	CKernel::p_kernel->dealData(ISendIp, buf, nLen);
}

