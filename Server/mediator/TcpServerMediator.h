#pragma once
#include"INetMediator.h"
class TcpServerMediator :public INetMediator
{
public:
	  TcpServerMediator();
	  ~TcpServerMediator() override;
	  bool OpenNet() override;
	  void CloseNet() override;
	  bool SendData(long ISendIp, char* buf, int nLen) override;
	  void DealData(long ISendIp, char* buf, int nLen) override;
};