#ifndef GAME_H
#define GAME_H

#include <QDialog>

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();

private slots:


    void on_pb_xq_clicked();

private:
    Ui::game *ui;
};

#endif // GAME_H
