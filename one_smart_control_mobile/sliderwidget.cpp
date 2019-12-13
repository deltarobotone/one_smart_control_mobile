#include "sliderwidget.h"

OneSmartControl::SliderWidget::SliderWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent):
    QWidget(parent),
    screenSize(screenSize),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);
    
    xLabel = new QLabel;
    yLabel = new QLabel;
    zLabel = new QLabel;
    vLabel = new QLabel;
    
    xValue = new QLabel;
    yValue = new QLabel;
    zValue = new QLabel;
    vValue = new QLabel;
    
    xSlider = new QSlider(Qt::Horizontal);
    ySlider = new QSlider(Qt::Horizontal);
    zSlider = new QSlider(Qt::Horizontal);
    vSlider = new QSlider(Qt::Horizontal);
    
    toChartButton = new QPushButton;

    createLayout();

    workingSpace.setLevel(1, 70.0, 79.0, 25.0);
    workingSpace.setLevel(2, 80.0, 99.0, 45.0);
    workingSpace.setLevel(3, 100.0, 119.0, 37.5);
    workingSpace.setLevel(4, 120.0, 130.0, 15.0);
}

void OneSmartControl::SliderWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    QFont font;

    if (screenSize == Screensize::XS)
    {
        font = QFont("Arial Rounded MT Bold", 18);
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 5px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(40, 40));
        xSlider->setStyleSheet("QSlider { min-height: 50px; max-height: 50px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 10px; }"
                               "QSlider::handle:Horizontal { width:30px; height: 30px; background: rgb(30, 144, 255); border-radius: 14.99px; margin: -10px 0px -10px 0px; }");
        ySlider->setStyleSheet("QSlider { min-height: 50px; max-height: 50px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 10px; }"
                               "QSlider::handle:Horizontal { width:30px; height: 30px; background: rgb(30, 144, 255); border-radius: 14.99px; margin: -10px 0px -10px 0px; }");
        zSlider->setStyleSheet("QSlider { min-height: 50px; max-height: 50px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 10px; }"
                               "QSlider::handle:Horizontal { width:30px; height: 30px; background: rgb(30, 144, 255); border-radius: 14.99px; margin: -10px 0px -10px 0px; }");
        vSlider->setStyleSheet("QSlider { min-height: 50px; max-height: 50px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 10px; }"
                               "QSlider::handle:Horizontal { width:30px; height: 30px; background: rgb(30, 144, 255); border-radius: 14.99px; margin: -10px 0px -10px 0px; }");
    }
    if (screenSize == Screensize::S)
    {
        font = QFont("Arial Rounded MT Bold", 18);
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(75, 75));
        xSlider->setStyleSheet("QSlider { min-height: 85px; max-height: 85px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 14px; }"
                               "QSlider::handle:Horizontal { width:40px; height: 40px; background: rgb(30, 144, 255); border-radius: 19.99px; margin: -14px 0px -14px 0px; }");
        ySlider->setStyleSheet("QSlider { min-height: 85px; max-height: 85px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 14px; }"
                               "QSlider::handle:Horizontal { width:40px; height: 40px; background: rgb(30, 144, 255); border-radius: 19.99px; margin: -14px 0px -14px 0px; }");
        zSlider->setStyleSheet("QSlider { min-height: 85px; max-height: 85px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 14px; }"
                               "QSlider::handle:Horizontal { width:40px; height: 40px; background: rgb(30, 144, 255); border-radius: 19.99px; margin: -14px 0px -14px 0px; }");
        vSlider->setStyleSheet("QSlider { min-height: 85px; max-height: 85px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 14px; }"
                               "QSlider::handle:Horizontal { width:40px; height: 40px; background: rgb(30, 144, 255); border-radius: 19.99px; margin: -14px 0px -14px 0px; }");
        basicLayout->setSpacing(5);
    }
    if (screenSize == Screensize::M)
    {
        font = QFont("Arial Rounded MT Bold", 20);
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 15px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(120, 120));
        xSlider->setStyleSheet("QSlider { min-height: 125px; max-height: 125px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 20px; }"
                               "QSlider::handle:Horizontal { width:60px; height: 60px; background: rgb(30, 144, 255); border-radius: 29.99px; margin: -20px 0px -20px 0px; }");
        ySlider->setStyleSheet("QSlider { min-height: 125px; max-height: 125px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 20px; }"
                               "QSlider::handle:Horizontal { width:60px; height: 60px; background: rgb(30, 144, 255); border-radius: 29.99px; margin: -20px 0px -20px 0px; }");
        zSlider->setStyleSheet("QSlider { min-height: 125px; max-height: 125px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 20px; }"
                               "QSlider::handle:Horizontal { width:60px; height: 60px; background: rgb(30, 144, 255); border-radius: 29.99px; margin: -20px 0px -20px 0px; }");
        vSlider->setStyleSheet("QSlider { min-height: 125px; max-height: 125px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 20px; }"
                               "QSlider::handle:Horizontal { width:60px; height: 60px; background: rgb(30, 144, 255); border-radius: 29.99px; margin: -20px 0px -20px 0px; }");
        basicLayout->setSpacing(15);
    }
    if (screenSize == Screensize::L)
    {
        font = QFont("Arial Rounded MT Bold", 22);
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 20px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(120, 120));
        xSlider->setStyleSheet("QSlider { min-height: 160px; max-height: 160px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 30px; }"
                               "QSlider::handle:Horizontal { width:80px; height: 80px; background: rgb(30, 144, 255); border-radius: 39.99px; margin: -25px 0px -25px 0px; }");
        ySlider->setStyleSheet("QSlider { min-height: 160px; max-height: 160px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 30px; }"
                               "QSlider::handle:Horizontal { width:80px; height: 80px; background: rgb(30, 144, 255); border-radius: 39.99px; margin: -25px 0px -25px 0px; }");
        zSlider->setStyleSheet("QSlider { min-height: 160px; max-height: 160px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 30px; }"
                               "QSlider::handle:Horizontal { width:80px; height: 80px; background: rgb(30, 144, 255); border-radius: 39.99px; margin: -25px 0px -25px 0px; }");
        vSlider->setStyleSheet("QSlider { min-height: 160px; max-height: 160px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 30px; }"
                               "QSlider::handle:Horizontal { width:80px; height: 80px; background: rgb(30, 144, 255); border-radius: 39.99px; margin: -25px 0px -25px 0px; }");
        basicLayout->setSpacing(20);
    }

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));
    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));

    xLabel->setText("- X +");
    xLabel->setAlignment(Qt::AlignCenter);
    xLabel->setFont(font);
    xValue->setAlignment(Qt::AlignCenter);
    xValue->setFont(font);
    xSlider->setMaximum(45);
    xSlider->setMinimum(-45);
    xSlider->setValue(0);
    connect(xSlider, SIGNAL(valueChanged(int)),this, SLOT(xSliderValueChanged(int)));
    connect(xSlider, SIGNAL(sliderReleased()),this, SLOT(xSliderReleased()));


    yLabel->setText("- Y +");
    yLabel->setAlignment(Qt::AlignCenter);
    yLabel->setFont(font);
    yValue->setAlignment(Qt::AlignCenter);
    yValue->setFont(font);
    ySlider->setMaximum(45);
    ySlider->setMinimum(-45);
    ySlider->setValue(0);
    connect(ySlider, SIGNAL(valueChanged(int)),this, SLOT(ySliderValueChanged(int)));
    connect(ySlider, SIGNAL(sliderReleased()),this, SLOT(ySliderReleased()));
    
    
    zLabel->setText("- Z +");
    zLabel->setAlignment(Qt::AlignCenter);
    zLabel->setFont(font);
    zValue->setAlignment(Qt::AlignCenter);
    zValue->setFont(font);
    zSlider->setMaximum(130);
    zSlider->setMinimum(70);
    zSlider->setValue(100);
    connect(zSlider, SIGNAL(valueChanged(int)),this, SLOT(zSliderValueChanged(int)));
    connect(zSlider, SIGNAL(sliderReleased()),this, SLOT(zSliderReleased()));
    

    vLabel->setText("- Speed +");
    vLabel->setAlignment(Qt::AlignCenter);
    vLabel->setFont(font);
    vValue->setAlignment(Qt::AlignCenter);
    vValue->setFont(font);
    vSlider->setMaximum(100);
    vSlider->setMinimum(10);
    vSlider->setValue(80);
    connect(vSlider, SIGNAL(valueChanged(int)),this, SLOT(vSliderValueChanged(int)));
    connect(vSlider, SIGNAL(sliderReleased()),this, SLOT(vSliderReleased()));


    basicLayout->addWidget(xLabel,0,0,1,2);
    basicLayout->addWidget(toChartButton,0,1,1,1,Qt::AlignRight);
    basicLayout->addWidget(xValue,1,0,1,2);
    basicLayout->addWidget(xSlider,2,0,1,2);

    basicLayout->addWidget(yLabel,3,0,1,2);
    basicLayout->addWidget(yValue,4,0,1,2);
    basicLayout->addWidget(ySlider,5,0,1,2);
    
    basicLayout->addWidget(zLabel,6,0,1,2);
    basicLayout->addWidget(zValue,7,0,1,2);
    basicLayout->addWidget(zSlider,8,0,1,2);

    basicLayout->addWidget(vLabel,9,0,1,2);
    basicLayout->addWidget(vValue,10,0,1,2);
    basicLayout->addWidget(vSlider,11,0,1,2);

    setLayout(basicLayout);

    controlData.xPosition  = int(xSlider->value());
    QString text = QString::number(xSlider->value()) + QString(" mm");
    xValue->setText(text);

    controlData.yPosition  = int(ySlider->value());
    text = QString::number(ySlider->value()) + QString(" mm");
    yValue->setText(text);

    controlData.zPosition  = int(zSlider->value());
    text = QString::number(zSlider->value()) + QString(" mm");
    zValue->setText(text);

    controlData.velocity  = int(vSlider->value());
    text = QString::number(vSlider->value()) + QString(" %");
    vValue->setText(text);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::xSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" mm");
    xValue->setText(text);
    controlData.xPosition = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::ySliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" mm");
    yValue->setText(text);
    controlData.yPosition = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::zSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" mm");
    zValue->setText(text);
    controlData.zPosition = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::vSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" %");
    vValue->setText(text);
    controlData.velocity = value;
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit dataChanged();
}

void OneSmartControl::SliderWidget::xSliderReleased()
{
    controlData.xPosition = xSlider->value();
    robot.move.ptp(controlData.xPosition,controlData.yPosition,controlData.zPosition,controlData.velocity);
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::ySliderReleased()
{
    controlData.yPosition = ySlider->value();
    robot.move.ptp(controlData.xPosition,controlData.yPosition,controlData.zPosition,controlData.velocity);
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::zSliderReleased()
{
    controlData.zPosition = zSlider->value();
    robot.move.ptp(controlData.xPosition,controlData.yPosition,controlData.zPosition,controlData.velocity);
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::vSliderReleased()
{
    controlData.velocity = vSlider->value();
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
}

void OneSmartControl::SliderWidget::toChartButtonHandle()
{
    controlData.dataid = ID::move;
    controlData.xPosition = xSlider->value();
    controlData.yPosition = ySlider->value();
    controlData.zPosition = zSlider->value();
    controlData.velocity = vSlider->value();
    controlData.workingSpaceStatus = workingSpace.check(controlData.xPosition,controlData.yPosition,controlData.zPosition);
    emit toChart();
}


