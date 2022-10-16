#ifndef QQDIALOG_H
#define QQDIALOG_H
#include<QMenu>
#include <QDialog>
#include"useritem.h"
#include<QVBoxLayout>
#include"chatdialog.h"
namespace Ui {
class QQDialog;
}

class QQDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QQDialog(QWidget *parent = 0);
    ~QQDialog();
    //Add buddy
    void addFriend(Useritem* item);
    //Setting User Information
    void setInfo(QString name,QString feeling,int iconId);
    //Override the close event
    void closeEvent(QCloseEvent * event);
signals:
    void SIG_AddFriend();
    void SIG_CloseQQ();
private slots:
    void on_pb_tool1_clicked();
    //The slot function that handles clicking menu items
    void slot_dealMenu(QAction* action);
private:
    Ui::QQDialog *ui;
    //Vertical layout layer, add friends
    QVBoxLayout* m_layout;
    //The menu bar
    QMenu* m_menu;
};
#endif
