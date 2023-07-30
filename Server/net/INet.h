#pragma once
#include <iostream>
#include <winsock2.h>
using namespace std;  // NOLINT(clang-diagnostic-header-hygiene)
// Need to link with Ws2 32lib
#pragma comment(lib,"ws2_32.lib")
//ֱ�����������  // NOLINT(clang-diagnostic-invalid-utf8)
class INetMediator;
class INet
{
public:
	INet() {}//ʹ��ʱ������ָ��ָ�����������Ҫʹ����������ֹ�ڴ�
	// ��ʼ������
	virtual~INet() {}
	// ��ʼ������
	virtual bool InitNet() = 0;
	// �ر�����
	virtual void UnInitNet() = 0;
	//��������
	virtual bool SendData(long ISendlp, char* buf, int nLen) = 0;
protected:
	//������
	virtual void ReceiveData() = 0;
	//�н�����ָ�룬���ڽ����ݴ��ݸ��н�����;
	INetMediator* m_pMediator; 
};

