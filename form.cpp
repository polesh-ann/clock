#include "form.h"
#include "ui_form.h"

form::form(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::form)
{
    /*ui->setupUi(this);
    QPixmap background(":/img/kartinti/фон1.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);*/

    ui->setupUi(this);
    m = 0;
    ms = 0;
    s = 0;
    timer = new QTimer (this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    timer->start(1);
    ui->pushButton->setText("СТАРТ");
     ui->pushButton_2->setText("СБРОС");
}

form::~form()
{
    delete ui;
}

void form::TimerSlot()
{
    ms++;
    if (ms >= 1000){
        ms = 0;
        s++;
    }
    if(s >= 60){
        s = 0;
        ms++;
    }
    ui->label->setText(QString::number(m) + " : " );
    ui->label_2->setText(QString::number(s));
    ui->label_3->setText(" : " + QString::number(ms));
}

void form::on_pushButton_clicked()
{
    flag = !flag;
    if (flag){
        ui->pushButton->setText("СТАРТ");
        timer ->stop();
    }
    else
    {
        ui->pushButton->setText("СТОП");
        timer ->start(1);
    }
}

void form::on_pushButton_2_clicked()
{
    ms = 0;
    s = 0;
    m = 0;
    ui->label->setText(QString::number(m) + " : " );
    ui->label_2->setText(QString::number(s));
    ui->label_3->setText(" : " + QString::number(ms));
}

