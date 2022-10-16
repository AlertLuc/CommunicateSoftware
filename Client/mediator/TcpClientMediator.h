#pragma once
#include"INetMediator.h"
class TcpClientMediator :public INetMediator
{
    Q_OBJECT
public:
      TcpClientMediator();
      ~TcpClientMediator();
      bool OpenNet();
      void CloseNet();
      bool SendData(long ISendIp, char* buf, int nLen);
      void DealData(long ISendIp, char* buf, int nLen);
signals:
      //The received data is passed to the kernel class
      void SIG_ReadyData(long ISendIp, char* buf, int nLen);
};
