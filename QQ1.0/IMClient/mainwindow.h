#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include<QPixmap>
#include<QDesktopWidget>
#include<QMessageBox>
#include<QFileDialog>
#include <QStandardPaths>
#include<QDesktopServices>
#include<QString>
#include<QDebug>
#include<QClipboard>
//storageLocaltion

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newScreenShotButton_clicked();
    void shotScreenSlot();//新建截图
    void savePictureSlot();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QPixmap pixmap;

};

#endif // MAINWINDOW_H
