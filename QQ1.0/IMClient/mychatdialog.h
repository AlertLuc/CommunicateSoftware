#ifndef MYCHATDIALOG_H
#define MYCHATDIALOG_H
#include <QDialog>
#include<QVBoxLayout>
#include<QCloseEvent>
#include<QUrl>
#include  <QDesktopServices>
#include"useritem.h"
#include<QMenu>
#include <QWidget>

namespace Ui
{
class MyChatDialog;
}
class MyChatDialog : public QDialog
{
    Q_OBJECT
signals:
    //给kernel发送添加好友的信号
    void SIG_addFriend();
    //关闭好友列表界面的信号
    void SIG_close();
public:
    explicit MyChatDialog(QWidget *parent = 0);
    ~MyChatDialog();
    //关闭重写事件
    void closeEvent(QCloseEvent*event);
    //添加好友信息
    void addFriend(UserItem*item);
    //设置用户信息
    void setInfo(QString name,QString feeling,int iconId);
private slots:
    void on_pb_menu_clicked();
    //处理菜单点击事件
    void slot_dealMenu(QAction* action);


    void on_pushButton_3_clicked();

    void on_pb_tool4_clicked();

    void on_pb_tool5_clicked();

private:
    Ui::MyChatDialog *ui;
    // QVBoxLayout垂直布局的层
    QVBoxLayout* m_layout;
    //菜单
    QMenu* m_menu;
};
#endif // MYCHATDIALOG_H
