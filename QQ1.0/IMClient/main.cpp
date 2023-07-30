#include <QApplication>
#include"ckernel.h"

//#include "player.h"

//#include <QCommandLineParser>
//#include <QCommandLineOption>
//#include <QDir>
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    CKernel kernel;
    return app.exec();

//    FeiQDialog w;
//    w.show();
//    INetMediator*m_pMediator=new UdpMediator;

//    //打开网络
//   if(!m_pMediator->OpenNet())
//   {
//       cout<<"打开网络失败"<<endl;
//       system("pause");
//       return 0;
//   }
//    //发个广播
//    m_pMediator->SendData(inet_addr("255.255.255.255"),"hello world",strlen("")+1);
//    //关闭网络
//    m_pMediator->CloseNet();
//    Sleep(50);
//    system("pause");
//    return 0;
}
