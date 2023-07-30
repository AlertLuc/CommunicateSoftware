#pragma once
#include"INet.h"
class TcpClientNet :public INet
{
public:
    TcpClientNet(INetMediator* pMediator);
    ~TcpClientNet();
    // 初始化网络
    bool InitNet();
    // 关闭网络
    void UnInitNet();
    //发送数据
    bool SendData(long ISendIp, char* buf, int nLen);
protected:
    //接收数据
    void ReceiveData();
    //接收数据的线程函数
    static unsigned int  _stdcall RecvThread(void* Ipvoid);
    SOCKET m_sock;
    //接收数据的线程函数
    HANDLE m_hThreadHendle;//控制接收线程
    bool m_isStop;
};
