#include "mychatdialog.h"
#include "ui_mychatdialog.h"
#include<QMessageBox>
#include<QToolButton>
#include"game.h"



#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>

MyChatDialog::MyChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyChatDialog)
{
    ui->setupUi(this);
    setWindowTitle("QQ1.0");
    //设置图标
    setWindowIcon(QPixmap(":/images/7.png"));


    //初始化垂直布局的层
    m_layout=new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(3);
    //把层设置到控件
    ui->wdg_list->setLayout(m_layout);
    //给菜单new对象,this就是父窗口，子控件的回收由父窗口负责
    m_menu=new QMenu(this);
    //添加菜单项
    m_menu->addAction("添加好友");
    m_menu->addAction("系统设置");

    //绑定点击菜单的信号和槽函数
    connect(m_menu,SIGNAL(triggered(QAction*)),
              this,SLOT(slot_dealMenu(QAction*)));

    //设置图标
    setWindowIcon(QPixmap(":/images/7.png"));
}

MyChatDialog::~MyChatDialog()
{
    delete ui;
}

//关闭重写事件
void MyChatDialog::closeEvent(QCloseEvent *event)
{
    //忽略关闭事件，在kernel类中控制窗口关闭
    event->ignore();
    if(QMessageBox::Yes==QMessageBox::question(this,"提示","是否确认关闭？")) {
        Q_EMIT SIG_close();

    }
}

//添加好友信息
void MyChatDialog::addFriend(UserItem *item)
{
    m_layout->addWidget(item);
}

//设置用户信息
void MyChatDialog::setInfo(QString name, QString feeling, int iconId)
{
    ui->lb_name->setText(name);
    ui->le_feeling->setText(feeling);
    ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(iconId)));
}

void MyChatDialog::on_pb_menu_clicked()
{
    //显示菜单
    //获取鼠标点击的位置
    QPoint po=QCursor::pos();
    //获取菜单的高度
    QSize size = m_menu->sizeHint();
    m_menu->exec(QPoint(po.x(),po.y()-size.height()));
}

//处理菜单点击事件
void MyChatDialog::slot_dealMenu(QAction *action)
{
    if("添加好友"==action->text()){
       //给kernel发送添加好友信号
        Q_EMIT SIG_addFriend();
    }
    else if("系统设置"==action->text()){
       //系统设置的处理流程
    }
}

//打开浏览器
void MyChatDialog::on_pushButton_3_clicked()
{
     QDesktopServices::openUrl(QUrl("https://www.baidu.com", QUrl::TolerantMode));
}


void MyChatDialog::on_pb_tool4_clicked()
{
    game*t=new game;
    t->show();
}

void MyChatDialog::on_pb_tool5_clicked()
{
//    QCoreApplication::setApplicationName("Player Example");
//       QCoreApplication::setOrganizationName("QtProject");
//       QCoreApplication::setApplicationVersion(QT_VERSION_STR);
//       QCommandLineParser parser;
//       parser.setApplicationDescription("Qt MultiMedia Player Example");
//       parser.addHelpOption();
//       parser.addVersionOption();
//       parser.addPositionalArgument("url", "The URL to open.");
//      parser.process(app);
      //Player player;
//      if (!parser.positionalArguments().isEmpty() && player.isPlayerAvailable()) {
//           QList<QUrl> urls;
//          foreach (const QString &a, parser.positionalArguments())
//               urls.append(QUrl::fromUserInput(a, QDir::currentPath(), QUrl::AssumeLocalFile));
//           player.addToPlaylist(urls);
//       }
//   #if defined(Q_WS_SIMULATOR)
//       player.setAttribute(Qt::WA_LockLandscapeOrientation);
//       player.showMaximized();
//   #else
      // player.show();

}
