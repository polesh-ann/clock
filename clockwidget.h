#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ClockWidget : public QWidget {
    Q_OBJECT

public:
    ClockWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateClock();

private:
    Ui::MainWindow *ui;
    void drawAnalogClock(QPainter &painter);
    void drawDigitalClock(QPainter &painter);
    void drawStopwatch(QPainter &painter);
    QTimer *timer;
    QTimer *stopwatchTimer;
    bool displayStopwatch;
    bool isAnalog;
    bool showSeconds;
    form form;
};

#endif // CLOCKWIDGET_H
