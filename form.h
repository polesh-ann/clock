#ifndef FORM_H
#define FORM_H

#include <QMainWindow>
#include "QTimer"

namespace Ui {
class form;
}

class form : public QMainWindow
{
    Q_OBJECT

public:
    explicit form(QWidget *parent = nullptr);
    ~form();

private:
    Ui::form *ui;
    QTimer *timer;
    int ms, s, m;
    bool flag = true;

private slots:
    void TimerSlot();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // FORM_H
