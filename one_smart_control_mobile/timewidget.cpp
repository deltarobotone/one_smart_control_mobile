#include "timewidget.h"

OneSmartControl::TimeWidget::TimeWidget(OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent):
    QWidget(parent),
    screenSize(screenSize),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);

    tLabel = new QLabel;
    tSlider = new QSlider(Qt::Horizontal);

    toChartButton = new QPushButton;

    createLayout();
}

void OneSmartControl::TimeWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    int size = 0;
    QFont font;
    if (screenSize == Screensize::XS)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 5px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(45, 45));

        tSlider->setStyleSheet("QSlider { min-height: 50px; max-height: 50px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 10px; }"
                               "QSlider::handle:Horizontal { width:30px; height: 30px; background: rgb(30, 144, 255); border-radius: 14.99px; margin: -10px 0px -10px 0px; }");

        font = QFont("Arial Rounded MT Bold", 18);

    }
    if (screenSize == Screensize::S)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(80, 80));

        tSlider->setStyleSheet("QSlider { min-height: 85px; max-height: 85px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 14px; }"
                               "QSlider::handle:Horizontal { width:40px; height: 40px; background: rgb(30, 144, 255); border-radius: 19.99px; margin: -14px 0px -14px 0px; }");

        font = QFont("Arial Rounded MT Bold", 18);

        basicLayout->setSpacing(2);

    }
    if (screenSize == Screensize::M)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 15px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(120, 120));

        tSlider->setStyleSheet("QSlider { min-height: 125px; max-height: 125px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 20px; }"
                               "QSlider::handle:Horizontal { width:60px; height: 60px; background: rgb(30, 144, 255); border-radius: 29.99px; margin: -20px 0px -20px 0px; }");

        font = QFont("Arial Rounded MT Bold", 20);
    }
    if (screenSize == Screensize::L)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 20px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(150, 150));

        tSlider->setStyleSheet("QSlider { min-height: 160px; max-height: 160px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 30px; }"
                               "QSlider::handle:Horizontal { width:80px; height: 80px; background: rgb(30, 144, 255); border-radius: 39.99px; margin: -25px 0px -25px 0px; }");

        font = QFont("Arial Rounded MT Bold", 22);
    }

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));

    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));

    tLabel->setAlignment(Qt::AlignCenter);
    tLabel->setFont(font);
    tSlider->setMaximum(2500);
    tSlider->setMinimum(500);
    tSlider->setValue(1500);
    connect(tSlider, SIGNAL(valueChanged(int)),this, SLOT(tSliderValueChanged(int)));

    basicLayout->addWidget(tLabel,0,0,1,2);
    basicLayout->addWidget(toChartButton,0,1,1,1,Qt::AlignRight);
    basicLayout->addWidget(tSlider,2,0,1,2);

    setLayout(basicLayout);
    tSliderValueChanged(tSlider->value());
    emit dataChanged();
}

void OneSmartControl::TimeWidget::tSliderValueChanged(int value)
{
    QString text = "Wait for " +  QString::number(value) + QString(" ms");
    tLabel->setText(text);
    controlData.waitFortime  = uint(value);
    emit dataChanged();
}

void OneSmartControl::TimeWidget::toChartButtonHandle()
{
    controlData.dataid = ID::waitFor;
    emit toChart();
}
