#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "endscreen.h"

#include <QKeyEvent>
#include <QDebug>
#include <QDir>
#include <QMediaPlayer>
#include <QAudioOutput>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("2048");


    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *aO = new QAudioOutput;
    music->setAudioOutput(aO);
    connect(music, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::playMusic);
    music->setSource(QUrl("qrc:/sounds/music.mp3"));
    aO->setVolume(0);
    //music->play();



    QString fPath = QDir::currentPath() + "/best.txt";
    QFile file(fPath);

    if (!file.open(QIODevice::ReadWrite))
        return;

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(QLatin1Char(','), Qt::SkipEmptyParts);
        if(list.size() == 0) {
            ui->score->setText("0");
            setScore(0);
            ui->best->setText("0");
        }else {
            ui->score->setText(list.at(0));
            setScore(list.at(0).toInt());
            ui->best->setText(list.at(1));
        }

    }

    file.close();



    this->setFocusPolicy(Qt::StrongFocus);
    plat = readLast();
    draw();

}

MainWindow::~MainWindow()
{
    delete ui;
}

Plateau MainWindow::readLast() {
    QList<QStringList> storage;
    QString fPath = QDir::currentPath() + "/last.txt";
    QFile file(fPath);

    if (!file.open(QIODevice::ReadWrite))
        return plateauInitial();

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(QLatin1Char(','), Qt::SkipEmptyParts);
        storage.append(list);
    }

    if(storage.size() == 0) {
        return plateauInitial();
    }

    Plateau plat = plateauVide();
    for(int i = 0; i < storage.size(); i++) {
        for(int j = 0; j < storage.at(i).size(); j++) {
            plat[i][j] = storage.at(i).at(j).toInt();
        }
    }
    return plat;
}

void MainWindow::playMusic() {
    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *aO = new QAudioOutput;
    music->setAudioOutput(aO);
    music->setSource(QUrl("qrc:/sounds/music.mp3"));
    aO->setVolume(0.1);
    music->play();
}

void MainWindow::draw() {
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



void MainWindow::keyPressEvent(QKeyEvent *e) {
    if(not estTermine(plat)) {
        Plateau last = plat;
        if(e->key() == Qt::Key_Up) {
            plat = deplacementHaut(plat);
        }
        if(e->key() == Qt::Key_Down) {
            plat = deplacementBas(plat);
        }
        if(e->key() == Qt::Key_Left) {
            plat = deplacementGauche(plat);
        }
        if(e->key() == Qt::Key_Right) {
            plat = deplacementDroite(plat);
        }

        if(not notMoved(last, plat)) {
            plat = addblock(plat);
        }


        ui->score->setText(QString::number(getScore()));

        int bst = ui->best->text().toInt();
        if(bst <= getScore()) {
            ui->best->setText(QString::number(getScore()));
        }
        draw();
    }else {
        EndScreen es;
        es.setModal(true);
        es.setAttribute(Qt::WA_TranslucentBackground);
        es.setWindowFlags(Qt::FramelessWindowHint);
        connect(&es, &EndScreen::reset, this, &MainWindow::resetGame);
        es.exec();

    }
}





void MainWindow::on_toolButton_clicked()
{
    resetScore();
    ui->score->setText("0");
    plat = plateauInitial();
    draw();
}

void MainWindow::saveLast() {
    QString fPath = QDir::currentPath() + "/last.txt";
    QFile file(fPath);
    if (!file.open(QIODevice::ReadWrite))
        return;
    file.resize(0);
    QTextStream out(&file);

    for(int i = 0; i < 4; i++) {
        QString line = "";
        for(int j = 0; j < 4; j++) {
            line += (QString::number(plat[i][j]) + ",");
        }
        out << line << "\n";
    }

    file.flush();
    file.close();
}

void MainWindow::closeEvent(QCloseEvent *e) {
    saveLast();
    QString fPath = QDir::currentPath() + "/best.txt";
    QFile file(fPath);
    if (!file.open(QIODevice::ReadWrite))
        return;

    QTextStream out(&file);

    file.resize(0);

    out << ui->score->text() << "," <<  ui->best->text();
    file.flush();
    file.close();
}

void MainWindow::resetGame() {
    resetScore();
    ui->score->setText("0");
    plat = plateauInitial();
    draw();
}

