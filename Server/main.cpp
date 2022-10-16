#include<windows.h>
#include<iostream>
#include"CMySql.h"
#include<string>
//#include"TcpClientMediator.h"
//#include"TcpServerMediator.h"
#include"Kernel.h"
using namespace std;
int main()
{
	CKernel kernel;
	if (kernel.startServer())
	{
		while (1) {
			Sleep(5000);
			cout << "server is running" << endl;
		}
	}
	else {
		cout << "Failed to open the server" << endl;
		system("pause");  // NOLINT(concurrency-mt-unsafe)
		return 1;
	}
}