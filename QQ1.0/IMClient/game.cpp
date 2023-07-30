#include "game.h"
#include "ui_game.h"

game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    setWindowTitle("game");
    //设置图标
    setWindowIcon(QPixmap(":/images/game.png"));
}

game::~game()
{
    delete ui;
}



void game::on_pb_xq_clicked()
{

}
