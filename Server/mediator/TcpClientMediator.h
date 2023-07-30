#pragma once
#include"INetMediator.h"
class TcpClientMediator :public INetMediator
{
public:
	  TcpClientMediator();
	  ~TcpClientMediator() override;
	  bool OpenNet() override;
	  void CloseNet() override;
	  bool SendData(long ISendIp, char* buf, int nLen) override;
	  void DealData(long ISendIp, char* buf, int nLen) override;
};