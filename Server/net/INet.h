#pragma once
#include <iostream>
#include <winsock2.h>
using namespace std;  // NOLINT(clang-diagnostic-header-hygiene)
// Need to link with Ws2 32lib
#pragma comment(lib,"ws2_32.lib")
//直接声明这个类  // NOLINT(clang-diagnostic-invalid-utf8)
class INetMediator;
class INet
{
public:
	INet() {}//使用时，父类指针指向子类对象，需要使用虚析构防止内存
	// 初始化网络
	virtual~INet() {}
	// 初始化网络
	virtual bool InitNet() = 0;
	// 关闭网络
	virtual void UnInitNet() = 0;
	//发送数据
	virtual bool SendData(long ISendlp, char* buf, int nLen) = 0;
protected:
	//收数据
	virtual void ReceiveData() = 0;
	//中介者类指针，用于将数据传递给中介者类;
	INetMediator* m_pMediator; 
};

