#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QDialog>

namespace Ui {
class EndScreen;
}

class EndScreen : public QDialog
{
    Q_OBJECT

public:
    explicit EndScreen(QWidget *parent = nullptr);
    ~EndScreen();

signals:
    void reset();

private slots:
    void on_toolButton_clicked();

private:
    Ui::EndScreen *ui;
};

#endif // ENDSCREEN_H
