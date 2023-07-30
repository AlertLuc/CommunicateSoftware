#ifndef USERITEM_H
#define USERITEM_H
#include <QWidget>
namespace Ui
{
class UserItem;
}
class UserItem : public QWidget
{
    Q_OBJECT
signals:
    //用户点击好友头像的信号
    void SIG_userItemClicked(int id);
public:
    explicit UserItem(QWidget *parent = 0);
    ~UserItem();
    //设置好友信息
    void setInfo(QString name,QString feeling,int state,int icon,int id);
    //把头像置灰
    void setOffline();
    int m_state;
private slots:
    void on_pb_icon_clicked();
public:
     QString m_name;
private:
    Ui::UserItem *ui;
    QString m_feeling;
    int m_icon;
    int m_id;
};
#endif // USERITEM_H
