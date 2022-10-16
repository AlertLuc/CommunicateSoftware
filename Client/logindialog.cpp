#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    //Accept to close
    event->accept();
    //Send a signal to the kernel to close the window
    Q_EMIT SIG_CloseLogin();
}

//Login Clear button
void LoginDialog::on_pb_clear_clicked()
{
    ui->le_password->setText("");
    ui->le_tel->setText("");
}

//Login Submit button
void LoginDialog::on_pb_commit_clicked()
{
     //Gets data from the control
    QString tel = ui->le_tel->text();
    QString password=ui->le_password->text();
    //Check whether the input is valid
    QString telTemp=tel;
    if(tel.isEmpty()||password.isEmpty()||
            telTemp.remove(" ").isEmpty()){
        QMessageBox::about(this,"prompt","The phone number and password cannot be empty or blank");
        return;
    }
    if(tel.length() !=11 || password.length() > 15){
        QMessageBox::about(this,"prompt","The phone number can only be 11 digits, and the password can only be 15 digits");
        return;
    }
    QString passwordTmp=password;
    if(tel.isEmpty()||password.isEmpty()||
            passwordTmp.remove("").isEmpty()){
        QMessageBox::about(this,"prompt","The input content cannot be empty or all Spaces");
        return;
    }
     if(tel.length()!=11||password.length()>15) {
         QMessageBox::about(this,"prompt","The length of the input content is invalid");
         return;
     }
    //Use signal to send data to Kernel and transmit signal
     Q_EMIT SIG_LoginCommit(tel,password);
}

//Register Clear button
void LoginDialog::on_pb_clear_register_clicked()
{
      ui->le_name_register->setText("");
      ui->le_tel_register->setText("");
      ui->le_password_register->setText("");
}

//Registration Submit button
void LoginDialog::on_pb_commit_register_clicked()
{
    //1、Gets data from the control
    QString name=ui->le_name_register->text();
    QString tel=ui->le_tel_register->text();
    QString pas=ui->le_password_register->text();
    //2、Verify user input, reduce interaction, can not be empty, can not be all Spaces, length limit, tel can only be 11 digits, nicknames can not exceed 10 digits
    //Passwords can be no more than 15 characters, content verification, tel can only be a number, and nicknames can have no special characters -- regular expressions will be covered later
    QString nameTemp=name;
    QString telTemp=tel;
    if(name.isEmpty()||tel.isEmpty()||pas.isEmpty()||nameTemp.remove(" ").isEmpty()||
            telTemp.remove(" ").isEmpty()){
        QMessageBox::about(this,"prompt","Nicknames, phone numbers, and passwords cannot be empty or blank");
        return;
    }
    if(name.length() > 10 || tel.length() !=11 || pas.length() > 15){
        QMessageBox::about(this,"prompt","Phone numbers can be only 11 digits, nicknames no more than 10 digits, and passwords no more than 15 digits");
        return;
    }
    //3、Send data to kernel
    Q_EMIT SIG_RegisterCommit(name, tel, pas);
}
























