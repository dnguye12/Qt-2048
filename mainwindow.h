#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void draw(Plateau plat);

private:
    Ui::MainWindow *ui;

    void keyPressEvent(Plateau plat, QKeyEvent *e);
};
#endif // MAINWINDOW_H
