#include "lightwidget.h"

OneSmartControl::LightWidget::LightWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent):
    QWidget(parent),
    screenSize(screenSize),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);

    buttonRowLayout1 = new QHBoxLayout;
    buttonRowLayout2 = new QHBoxLayout;

    buttonRow1 = new QWidget;
    buttonRow2 = new QWidget;

    redButton = new QPushButton;
    greenButton = new QPushButton;
    blueButton = new QPushButton;
    cyanButton = new QPushButton;
    yellowButton = new QPushButton;
    magentaButton = new QPushButton;
    whiteButton = new QPushButton;
    offButton = new QPushButton;

    iLabel = new QLabel;
    iValue = new QLabel;
    iSlider = new QSlider(Qt::Horizontal);

    toChartButton = new QPushButton;

    createLayout();
}

void OneSmartControl::LightWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    int size = 0;
    QFont font;
    if (screenSize == Screensize::XS)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 5px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(45, 45));

        redButton->setStyleSheet("QPushButton{ background-color: rgb(200, 40, 40); border-radius: 15px; border: 1px solid rgb(200, 40, 40);}");
        greenButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 20); border-radius: 15px; border: 1px solid rgb(20, 200, 20);}");
        blueButton->setStyleSheet("QPushButton{ background-color: rgb(20, 20, 200); border-radius: 15px; border: 1px solid rgb(20, 20, 200);}");
        whiteButton->setStyleSheet("QPushButton{ background-color: rgb(250, 250, 250); border-radius: 15px; border: 1px solid rgb(200, 200, 200);}");
        cyanButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 200); border-radius: 15px; border: 1px solid rgb(20, 200, 200);}");
        yellowButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 20); border-radius: 15px; border: 1px solid rgb(200, 200, 20);}");
        magentaButton->setStyleSheet("QPushButton{ background-color: rgb(200, 20, 200); border-radius: 15px; border: 1px solid rgb(200, 20, 200);}");
        offButton->setStyleSheet("QPushButton{ background-color: rgb(200,200,200); border-radius: 15px; border: 1px solid rgb(200, 200, 200);}");

        iSlider->setStyleSheet("QSlider { min-height: 50px; max-height: 50px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 10px; }"
                               "QSlider::handle:Horizontal { width:30px; height: 30px; background: rgb(30, 144, 255); border-radius: 14.99px; margin: -10px 0px -10px 0px; }");

        font = QFont("Arial Rounded MT Bold", 18);

        size = 50;
    }
    if (screenSize == Screensize::S)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(75, 75));

        redButton->setStyleSheet("QPushButton{ background-color: rgb(200, 40, 40); border-radius: 28px; border: 2px solid rgb(200, 40, 40);}");
        greenButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 20); border-radius: 28px; border: 2px solid rgb(20, 200, 20);}");
        blueButton->setStyleSheet("QPushButton{ background-color: rgb(20, 20, 200); border-radius: 28px; border: 2px solid rgb(20, 20, 200);}");
        whiteButton->setStyleSheet("QPushButton{ background-color: rgb(250, 250, 250); border-radius: 28px; border: 2px solid rgb(200, 200, 200);}");
        cyanButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 200); border-radius: 28px; border: 2px solid rgb(20, 200, 200);}");
        yellowButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 20); border-radius: 28px; border: 2px solid rgb(200, 200, 20);}");
        magentaButton->setStyleSheet("QPushButton{ background-color: rgb(200, 20, 200); border-radius: 28px; border: 2px solid rgb(200, 20, 200);}");
        offButton->setStyleSheet("QPushButton{ background-color: rgb(200,200,200); border-radius: 28px; border: 2px solid rgb(200, 200, 200);}");

        iSlider->setStyleSheet("QSlider { min-height: 85px; max-height: 85px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 14px; }"
                               "QSlider::handle:Horizontal { width:40px; height: 40px; background: rgb(30, 144, 255); border-radius: 19.99px; margin: -14px 0px -14px 0px; }");

        font = QFont("Arial Rounded MT Bold", 18);

        basicLayout->setSpacing(0);

        size = 75;
    }
    if (screenSize == Screensize::M)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 15px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(120, 120));

        redButton->setStyleSheet("QPushButton{ background-color: rgb(200, 40, 40); border-radius: 40px; border: 3px solid rgb(200, 40, 40);}");
        greenButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 20); border-radius: 40px; border: 3px solid rgb(20, 200, 20);}");
        blueButton->setStyleSheet("QPushButton{ background-color: rgb(20, 20, 200); border-radius: 40px; border: 3px solid rgb(20, 20, 200);}");
        whiteButton->setStyleSheet("QPushButton{ background-color: rgb(250, 250, 250); border-radius: 40px; border: 3px solid rgb(200, 200, 200);}");
        cyanButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 200); border-radius: 40px; border: 3px solid rgb(20, 200, 200);}");
        yellowButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 20); border-radius: 40px; border: 3px solid rgb(200, 200, 20);}");
        magentaButton->setStyleSheet("QPushButton{ background-color: rgb(200, 20, 200); border-radius: 40px; border: 3px solid rgb(200, 20, 200);}");
        offButton->setStyleSheet("QPushButton{ background-color: rgb(200,200,200); border-radius: 40px; border: 3px solid rgb(200, 200, 200);}");

        iSlider->setStyleSheet("QSlider { min-height: 125px; max-height: 125px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 20px; }"
                               "QSlider::handle:Horizontal { width:60px; height: 60px; background: rgb(30, 144, 255); border-radius: 29.99px; margin: -20px 0px -20px 0px; }");

        font = QFont("Arial Rounded MT Bold", 20);

        size = 120;
    }
    if (screenSize == Screensize::L)
    {
        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 20px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(150, 150));

        redButton->setStyleSheet("QPushButton{ background-color: rgb(200, 40, 40); border-radius: 50px; border: 4px solid rgb(200, 40, 40);}");
        greenButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 20); border-radius: 50px; border: 4px solid rgb(20, 200, 20);}");
        blueButton->setStyleSheet("QPushButton{ background-color: rgb(20, 20, 200); border-radius: 50px; border: 4px solid rgb(20, 20, 200);}");
        whiteButton->setStyleSheet("QPushButton{ background-color: rgb(250, 250, 250); border-radius: 50px; border: 4px solid rgb(200, 200, 200);}");
        cyanButton->setStyleSheet("QPushButton{ background-color: rgb(20, 200, 200); border-radius: 50px; border: 4px solid rgb(20, 200, 200);}");
        yellowButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 20); border-radius: 50px; border: 4px solid rgb(200, 200, 20);}");
        magentaButton->setStyleSheet("QPushButton{ background-color: rgb(200, 20, 200); border-radius: 50px; border: 4px solid rgb(200, 20, 200);}");
        offButton->setStyleSheet("QPushButton{ background-color: rgb(200,200,200); border-radius: 50px; border: 4px solid rgb(200, 200, 200);}");

        iSlider->setStyleSheet("QSlider { min-height: 160px; max-height: 160px; background: transparent;}"
                               "QSlider::sub-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::add-page:Horizontal { background: rgb(180, 180, 180);}"
                               "QSlider::groove:Horizontal { background: transparent; height: 30px; }"
                               "QSlider::handle:Horizontal { width:80px; height: 80px; background: rgb(30, 144, 255); border-radius: 39.99px; margin: -25px 0px -25px 0px; }");

        font = QFont("Arial Rounded MT Bold", 22);

        size = 150;
    }

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));

    redButton->setMinimumSize(size,size);
    redButton->setMaximumSize(size,size);
    greenButton->setMinimumSize(size,size);
    greenButton->setMaximumSize(size,size);
    blueButton->setMinimumSize(size,size);
    blueButton->setMaximumSize(size,size);
    whiteButton->setMinimumSize(size,size);
    whiteButton->setMaximumSize(size,size);
    cyanButton->setMinimumSize(size,size);
    cyanButton->setMaximumSize(size,size);
    yellowButton->setMinimumSize(size,size);
    yellowButton->setMaximumSize(size,size);
    magentaButton->setMinimumSize(size,size);
    magentaButton->setMaximumSize(size,size);
    offButton->setMinimumSize(size,size);
    offButton->setMaximumSize(size,size);

    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));
    connect(redButton, SIGNAL(released()),this,SLOT(setColourRed()));
    connect(greenButton, SIGNAL(released()),this,SLOT(setColourGreen()));
    connect(blueButton, SIGNAL(released()),this,SLOT(setColourBlue()));
    connect(whiteButton, SIGNAL(released()),this,SLOT(setColourWhite()));
    connect(cyanButton, SIGNAL(released()),this,SLOT(setColourCyan()));
    connect(yellowButton, SIGNAL(released()),this,SLOT(setColourYellow()));
    connect(magentaButton, SIGNAL(released()),this,SLOT(setColourMagenta()));
    connect(offButton, SIGNAL(released()),this,SLOT(setLightOff()));

    buttonRowLayout1->addWidget(redButton);
    buttonRowLayout1->addWidget(greenButton);
    buttonRowLayout1->addWidget(blueButton);
    buttonRowLayout1->addWidget(cyanButton);
    buttonRowLayout2->addWidget(yellowButton);
    buttonRowLayout2->addWidget(magentaButton);
    buttonRowLayout2->addWidget(whiteButton);
    buttonRowLayout2->addWidget(offButton);

    iLabel->setText("- Intensity +");
    iLabel->setAlignment(Qt::AlignCenter);
    iLabel->setFont(font);
    iValue->setFont(font);
    iValue->setAlignment(Qt::AlignCenter);
    iSlider->setMaximum(100);
    iSlider->setMinimum(10);
    iSlider->setValue(55);
    connect(iSlider, SIGNAL(valueChanged(int)),this, SLOT(iSliderValueChanged(int)));
    connect(iSlider, SIGNAL(sliderReleased()),this, SLOT(iSliderReleased()));

    basicLayout->addWidget(iLabel,0,0,1,2);
    basicLayout->addWidget(toChartButton,0,1,1,1,Qt::AlignRight);
    basicLayout->addWidget(iValue,1,0,1,2);
    basicLayout->addWidget(iSlider,2,0,1,2);

    buttonRow1->setLayout(buttonRowLayout1);
    buttonRow2->setLayout(buttonRowLayout2);
    basicLayout->addWidget(buttonRow1,3,0,1,2);
    basicLayout->addWidget(buttonRow2,4,0,1,2);

    setLayout(basicLayout);

    controlData.intensity  = int(iSlider->value());
    QString text = QString::number(iSlider->value()) + QString(" %");
    iValue->setText(text);

    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourRed()
{
    robot.light.setColour(Colour::red,controlData.intensity);
    controlData.colour = Colour::red;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourGreen()
{
    robot.light.setColour(Colour::green,controlData.intensity);
    controlData.colour = Colour::green;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourBlue()
{
    robot.light.setColour(Colour::blue,controlData.intensity);
    controlData.colour = Colour::blue;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourCyan()
{
    robot.light.setColour(Colour::cyan,controlData.intensity);
    controlData.colour = Colour::cyan;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourYellow()
{
    robot.light.setColour(Colour::yellow,controlData.intensity);
    controlData.colour = Colour::yellow;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourMagenta()
{
    robot.light.setColour(Colour::magenta,controlData.intensity);
    controlData.colour = Colour::magenta;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setColourWhite()
{
    robot.light.setColour(Colour::white,controlData.intensity);
    controlData.colour = Colour::white;
    emit dataChanged();
}

void OneSmartControl::LightWidget::setLightOff()
{
    robot.light.off();
    controlData.colour = Protocol::lightoff;
    emit dataChanged();
}

void OneSmartControl::LightWidget::iSliderValueChanged(int value)
{
    QString text = QString::number(value) + QString(" %");
    iValue->setText(text);
    controlData.intensity  = value;
    emit dataChanged();
}

void OneSmartControl::LightWidget::iSliderReleased()
{
    robot.light.setColour(controlData.colour,controlData.intensity);
}

void OneSmartControl::LightWidget::toChartButtonHandle()
{
    controlData.dataid = ID::light;
    emit toChart();
}
