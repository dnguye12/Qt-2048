#include "endscreen.h"
#include "ui_endscreen.h"

 #include "mainwindow.h"

EndScreen::EndScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndScreen)
{
    ui->setupUi(this);

}

EndScreen::~EndScreen()
{
    delete ui;
}

void EndScreen::on_toolButton_clicked()
{
    qDebug() << "reset";
    emit reset();
    close();
}

