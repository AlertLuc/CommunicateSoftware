#pragma once
#include <iostream>
#include <winsock2.h>
using namespace std;  // NOLINT(clang-diagnostic-header-hygiene)
// Need to link with Ws2 32lib
#pragma comment(lib,"ws2_32.lib")
//Declare the class directly
class INetMediator;
class INet
{
public:
	INet() {}
	virtual~INet() {}
	virtual bool InitNet() = 0;
	virtual void UnInitNet() = 0;
	virtual bool SendData(long ISendlp, char* buf, int nLen) = 0;
protected:
	virtual void RecvData() = 0;
    //The mediator class pointer that is used to pass data to the mediator class
	INetMediator* m_pMediator; 
};

