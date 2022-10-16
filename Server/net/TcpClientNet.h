#pragma once
#include"INet.h"
class TcpClientNet :public INet
{
public:
    TcpClientNet(INetMediator* pMediator);
    ~TcpClientNet();
    bool InitNet();
    void UnInitNet();
    bool SendData(long ISendIp, char* buf, int nLen);
protected:
    void RecvData();
    //A thread function that receives data
    static unsigned int  _stdcall RecvThread(void* Ipvoid);
    SOCKET m_sock;
    //Control the receiving thread
    HANDLE m_hThreadHendle;
    bool m_isStop;
};
