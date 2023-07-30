#pragma once
#include <iostream>
#include <winsock2.h>
using namespace std;
#include<QObject>
// Need to link with Ws2 32lib
#pragma comment(lib,"ws2_32.lib")
class INetMediator;//直接声明这个类
class INet
{
public:
    INet();
    virtual~INet() ;//使用时，父类指针指向子类对象，需要使用虚析构防止内存
	// 初始化网络
	virtual bool InitNet() = 0;
	// 关闭网络
	virtual void UnInitNet() = 0;
	//发送数据
	virtual bool SendData(long ISendlp, char* buf, int nLen) = 0;
protected:
	//收数据
	virtual void RecvData() = 0;
	INetMediator* m_pMediator; //中介者类指针，用于将数据传递给中介者类;
};

