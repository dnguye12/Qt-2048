#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Plateau plat = plateauInitial();
    draw(plat);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(Plateau plat) {
    for(int i = 0; i < plat.size(); i++) {
        for(int j = 0; j < plat.size(); j++) {
            QString name = "btn";
            name.append(QString::number(j));
            name.append(QString::number(i));
            QToolButton *btn = ui->gridWidget->findChild<QToolButton *>(name);
            btn->setText(QString::number(plat[i][j]));
        }
    }

    QList<QToolButton*> btns = ui->gridWidget->findChildren<QToolButton*>();
    foreach(QToolButton *btn, btns) {
        if(btn->text() == "0") {
            btn->setStyleSheet("background-color: rgb(204, 192, 179); color: rgb(204, 192, 179)");
        }else if(btn->text() == "2") {
            btn->setStyleSheet("background-color: rgb(237, 224, 200); color: white;");
        }else if(btn->text() == "4") {
            btn->setStyleSheet("background-color: rgb(242, 177, 121); color: white;");
        }else if(btn->text() == "8") {
            btn->setStyleSheet("background-color: rgb(245, 149, 99); color: white;");
        }else if(btn->text() == "16") {
            btn->setStyleSheet("background-color: rgb(246, 124, 95); color: white;");
        }else if(btn->text() == "32") {
            btn->setStyleSheet("background-color: rgb(246, 94, 59); color: white;");
        }else if(btn->text() == "64") {
            btn->setStyleSheet("background-color: rgb(237, 207, 114); color: white;");
        }else if(btn->text() == "128") {
            btn->setStyleSheet("background-color: rgb(237, 204, 97); color: white;");
        }else if(btn->text() == "256") {
            btn->setStyleSheet("background-color: rgb(237, 200, 80); color: white;");
        }else if(btn->text() == "512") {
            btn->setStyleSheet("background-color: rgb(237, 197, 63); color: white;");
        }else if(btn->text() == "1024") {
            btn->setStyleSheet("background-color: rgb(237, 194, 46); color: white;");
        }else if(btn->text() == "2048") {
            btn->setStyleSheet("background-color: rgb(237, 224, 200); color: white;");
        }else {
            btn->setStyleSheet("background-color: black; color: white;");
        }
    }

}

void MainWindow::keyPressEvent(Plateau plat, QKeyEvent *e) {
    if(e->key() == Qt::Key_W) {
        plat = deplacementHaut(plat);
        emit deplace(plat);
    }
}
