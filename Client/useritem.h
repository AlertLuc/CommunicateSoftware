#ifndef USERITEM_H
#define USERITEM_H
#include <QWidget>
#include"chatdialog.h"
namespace Ui {
class Useritem;
}

class Useritem : public QWidget
{
    Q_OBJECT
public:
    explicit Useritem(QWidget *parent = 0);
    ~Useritem();
    //Set friend information
    void setInfo(int id,int iconId,int state,QString name,QString feeling);
    //Setting a User Offline
    void setoffline();
signals:
    //Notifies the kernel that the chat window is displayed
     void SIG_userItemClicked(int id);
private slots:
    void on_pushButton_clicked();
public:
    QString m_name;
private:
    //friend id
    int m_id;
    int m_iconId;
    int m_state;
    Ui::Useritem *ui;
    QString m_feeling;
};
#endif // USERITEM_H
