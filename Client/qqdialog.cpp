#include "qqdialog.h"
#include "ui_qqdialog.h"
#include<QMessageBox>
#include<QCloseEvent>
QQDialog::QQDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QQDialog)
{
      ui->setupUi(this);
      //Modify the title
      setWindowTitle("Communication software");
      //Initialize the QVBoxLayout pointer, new an object
      m_layout= new QVBoxLayout;
      //Control to the left, right, and top of the border
      m_layout->setContentsMargins(0,0,0,0);
      //The distance of each control from each other
      m_layout->setSpacing(3);
      //Sets the layer to the control
      ui->widget->setLayout(m_layout);
      //Initialize the menu bar
      m_menu=new QMenu(this);
      //Add menu options
      m_menu->addAction("Add buddy");
      m_menu->addAction("System Settings");
      //Click Binding click menu options Signal and slot function
      connect(m_menu,SIGNAL(triggered(QAction*)),this,SLOT(slot_dealMenu(QAction*)));
}

QQDialog::~QQDialog()
{
    delete ui;
}

//Add buddy
void QQDialog::addFriend(Useritem *item)
{
    //Add a friend control to the layer
    m_layout->addWidget(item);
}

//Setting User Information
void QQDialog::setInfo(QString name, QString feeling, int iconId)
{
    ui->lb_name->setText(name);
    ui->le_feeling->setText(feeling);
    ui->pb_icon->setIcon(QIcon(QString(":/tx/%1.png").arg(iconId)));
}

void QQDialog::on_pb_tool1_clicked()
{
    //Click the coordinates of the mouse, up pop-up menu bar, get the coordinates of the mouse click
    QPoint p=QCursor::pos();
    //Gets the absolute size of the menu bar
    QSize size=m_menu->sizeHint();
    m_menu->exec(QPoint(p.x(),p.y()-size.height()));
}

 //The slot function that handles clicking menu items
void QQDialog::slot_dealMenu(QAction *action)
{
    //Determine which menu is being clicked on
    if("Add buddy"==action->text()){
        //Process the request to add a friend and send a signal to the kernel
        Q_EMIT SIG_AddFriend();
    }else if("System Settings"==action->text()){}
}

void QQDialog::closeEvent(QCloseEvent * event)
{
    event->ignore();
    if(QMessageBox::Yes == QMessageBox::question(this,"prompt","Do you confirm to exit?")){Q_EMIT SIG_CloseQQ();}
}
