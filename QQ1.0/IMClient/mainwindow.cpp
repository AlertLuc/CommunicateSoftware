#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->savePictureButton,SIGNAL(clicked()),this,SLOT(savePictureSlot()));
    //设置标题
    setWindowTitle("截图");
    //设置图标
    setWindowIcon(QPixmap(":/images/editcut.png"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newScreenShotButton_clicked()
{
    if(ui->checkBox->isChecked())
    {
        this->hide();//this->show();
        this->timer=new QTimer;
        QObject::connect(this->timer,SIGNAL(timeout()),SLOT(shotScreenSlot()));
                this->timer->start(ui->spinBox->value()*1000);

    }
    else
    {
        qApp->beep();//声音
    }
}

void MainWindow::shotScreenSlot()
{
    //pixmap
    this->pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());//静态
    ui->screenLabel->setPixmap(this->pixmap.scaled(ui->screenLabel->size()));
    QClipboard *clipboard=QApplication::clipboard();
//    QString originalText=clipboard->text();
//    qDebug()<<"current clipboard text is"<<originalText;
    clipboard->setPixmap(this->pixmap);
    this->show();
    this->timer->stop();
}
void MainWindow::savePictureSlot()
 {
     QString fileName=QFileDialog::getSaveFileName(this,"Save","../","Images (*.jpg);;Images (*.bmp);;Images (*.png)");
     this->pixmap.save(fileName);

 }
