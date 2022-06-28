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

    void draw();

signals:
    void deplace(Plateau plat);

public slots:
   // void deplaced(Plateau plat);

private:
    Ui::MainWindow *ui;

    void keyPressEvent(QKeyEvent *e);

    Plateau plat;
};
#endif // MAINWINDOW_H
