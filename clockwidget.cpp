#include "clockwidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QTime>
#include "QFont"

ClockWidget::ClockWidget(QWidget *parent) :
    QWidget(parent),isAnalog(true),showSeconds(true),displayStopwatch(false){


    // Таймер для обновления времени
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClockWidget::updateClock);
    timer->start(1000);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QGroupBox *typeGroup = new QGroupBox(tr("Тип часов"));
    QVBoxLayout *typeLayout = new QVBoxLayout;
    QRadioButton *analogButton = new QRadioButton(tr("Круглые"));
    QRadioButton *digitalButton = new QRadioButton(tr("Цифровые"));
    QRadioButton *stopwatchButton = new QRadioButton(tr("Секундомер"));
    connect(analogButton, &QRadioButton::toggled, this, [=](bool checked) {
        if (checked) {
            isAnalog = true;
            displayStopwatch = false;
            update();
        }
    });
    connect(digitalButton, &QRadioButton::toggled, this, [=](bool checked) {
        if (checked) {
            isAnalog = false;
            displayStopwatch = false;
            update();
        }
    });
    connect(stopwatchButton, &QRadioButton::toggled, this, [=](bool checked) {
        if (checked) {
            isAnalog = false;
            displayStopwatch = true;
        }

    });
    typeLayout->addWidget(analogButton);
    typeLayout->addWidget(digitalButton);
    typeLayout->addWidget(stopwatchButton);
    typeGroup->setLayout(typeLayout);

    QCheckBox *secondsCheckbox = new QCheckBox(tr("Показывать секунды"));
    secondsCheckbox->setChecked(true);
    connect(secondsCheckbox, &QCheckBox::toggled, this, [=](bool checked) {
        showSeconds = checked;
        update();
    });
    mainLayout->addWidget(typeGroup);
    mainLayout->addWidget(secondsCheckbox);
    setLayout(mainLayout);

    setWindowTitle(tr("Часы"));
    resize(600, 600);

}

void ClockWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (displayStopwatch) {
        drawStopwatch(painter); // Display the stopwatch if it is selected
    } else if (isAnalog) {
        drawAnalogClock(painter);  // Display the analog clock
    } else {
        drawDigitalClock(painter);  // Display the digital clock
    }
}

void ClockWidget::updateClock() {
    update();
}

void ClockWidget::drawAnalogClock(QPainter &painter) {
    int side = qMin(width(), height());
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-50, -50, 100, 100);

    QTime time = QTime::currentTime();

    painter.setPen(Qt::NoPen);

    painter.setBrush(Qt::black);
    for (int i = 0; i < 12; ++i) {
        painter.drawRect(0, -35, 1, 4);
        painter.rotate(30.0);
    }
    painter.setPen(Qt::black);

    QPen pen;
    pen.setWidth(2);

    // Часовая стрелка
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(0, 0, 0, -15);
    painter.restore();

    // Минутная стрелка
    painter.save();
    painter.rotate(6.0 * ((time.minute() + time.second() / 60.0)));
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(0, 0, 0, -25);
    painter.restore();

    if (showSeconds) {
        // Секундная стрелка
        painter.save();
        painter.rotate(6.0 * time.second());
        pen.setColor(Qt::green);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(0, 0, 0, -30);
        painter.restore();
    }
}

void ClockWidget::drawDigitalClock(QPainter &painter) {
    QTime time = QTime::currentTime();
    QString timeText = time.toString(showSeconds ? "hh:mm:ss" : "hh:mm");

    painter.setPen(Qt::green);
    painter.setFont(QFont("Comic Sans MS", 50));
    painter.drawText(rect(), Qt::AlignCenter, timeText);
}

void ClockWidget::drawStopwatch(QPainter &painter) {
    form.show();
}


