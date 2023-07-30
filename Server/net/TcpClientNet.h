#pragma once
#include"INet.h"
class TcpClientNet :public INet
{
public:
    TcpClientNet(INetMediator* pMediator);
    ~TcpClientNet();
    // ��ʼ������
    bool InitNet();
    // �ر�����
    void UnInitNet();
    //��������
    bool SendData(long ISendIp, char* buf, int nLen);
protected:
    //��������
    void ReceiveData();
    //�������ݵ��̺߳���
    static unsigned int  _stdcall RecvThread(void* Ipvoid);
    SOCKET m_sock;
    //�������ݵ��̺߳���
    HANDLE m_hThreadHendle;//���ƽ����߳�
    bool m_isStop;
};
