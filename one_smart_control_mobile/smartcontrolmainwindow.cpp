#include "smartcontrolmainwindow.h"
#include "ui_smartcontrolmainwindow.h"

SmartControlMainWindow::SmartControlMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SmartControlMainWindow)
{
    ui->setupUi(this);

    setStyleSheet("background-color:white;");

    QScreen *screen = QApplication::screens().at(0);
    int width = screen->availableSize().width();

    qDebug()<< width;

    if (width >= 480)screenSize = Screensize::XS;
    if (width >= 768)screenSize = Screensize::S;
    if (width >= 1080)screenSize = Screensize::M;
    if (width >= 1440)screenSize = Screensize::L;
    //if (width >= 2048)screenSize = Screensize::XL;

    if (screenSize == Screensize::XS) qDebug()<<"Screensize::XS";
    if (screenSize == Screensize::S) qDebug()<<"Screensize::S";
    if (screenSize == Screensize::M) qDebug()<<"Screensize::M";
    if (screenSize == Screensize::L) qDebug()<<"Screensize::L";
    if (screenSize == Screensize::XL) qDebug()<<"Screensize::XL";

    basicLayout = new QVBoxLayout;

    sliderGroupbox = new QGroupBox;
    sliderLayout = new QVBoxLayout;
    sliderWidget = new OneSmartControl::SliderWidget(robot,smartControlData,screenSize);

    flowChartGroupbox = new QGroupBox;
    flowChartLayout = new QVBoxLayout;
    flowChartWidget = new OneSmartControl::FlowChartWidget(robot,smartControlData,screenSize);

    lightGroupbox = new QGroupBox;
    lightLayout = new QVBoxLayout;
    lightWidget = new OneSmartControl::LightWidget(robot,smartControlData,screenSize);

    gripperGroupbox = new QGroupBox;
    gripperLayout = new QVBoxLayout;
    gripperWidget = new OneSmartControl::GripperWidget(robot,smartControlData,screenSize);

    connectGroupbox = new QGroupBox;
    connectLayout = new QVBoxLayout;
    connectWidget = new OneSmartControl::ConnectWidget(robot,smartControlData,screenSize);

    timeGroupbox = new QGroupBox;
    timeLayout = new QVBoxLayout;
    timeWidget = new OneSmartControl::TimeWidget(smartControlData,screenSize);

    buttonWidget = new QWidget;
    buttonLayout = new QHBoxLayout;
    leftButton = new QPushButton;
    rightButton = new QPushButton;

    logoImage = new QImage;
    logoWidget = new QLabel;

    prepareImage = new QImage;
    prepareWidget = new QLabel;

    infoLabel = new QLabel;

    versionLabel = new QLabel;

    createLayout();
}

SmartControlMainWindow::~SmartControlMainWindow()
{
    delete ui;
}

void SmartControlMainWindow::createLayout()
{
    setStyleSheet("background-color:white;");

    connect(sliderWidget,SIGNAL(toChart()),flowChartWidget,SLOT(addData()));
    connect(lightWidget,SIGNAL(toChart()),flowChartWidget,SLOT(addData()));
    connect(gripperWidget,SIGNAL(toChart()),flowChartWidget,SLOT(addData()));
    connect(timeWidget,SIGNAL(toChart()),flowChartWidget,SLOT(addData()));

    connect(sliderWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));
    connect(lightWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));
    connect(gripperWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));
    connect(timeWidget,SIGNAL(toChart()),this,SLOT(showToChartMessage()));

    connect(lightWidget,SIGNAL(dataChanged()),this,SLOT(lightWidgetBorder()));
    connect(sliderWidget,SIGNAL(dataChanged()),this,SLOT(sliderWidgetBorder()));

    connect(flowChartWidget,SIGNAL(playlistOn()),this,SLOT(playlistOn()));
    connect(flowChartWidget,SIGNAL(playlistOff()),this,SLOT(playlistOff()));

    logoImage->load(":/images/logos/onesmartcontrol.png");
    logoWidget->setAlignment(Qt::AlignCenter);

    prepareImage->load(":/images/screens/preparerobot.png");
    prepareWidget->setAlignment(Qt::AlignCenter);

    QFont font;
    int size = 0;

    if (screenSize == Screensize::XS)
    {
        font = QFont("Arial Rounded MT Bold", 18);
        size = 15;
        sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
        lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
        gripperGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
        flowChartGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
        timeGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
        connectGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
        rightButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
        leftButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
        prepareWidget->setPixmap(QPixmap::fromImage(prepareImage->scaled(int(1000*0.4),int(1000*0.4),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        logoWidget->setPixmap(QPixmap::fromImage(logoImage->scaled(int(800*0.4),int(800*0.4),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    if (screenSize == Screensize::S)
    {
        font = QFont("Arial Rounded MT Bold", 18);
        size = 25;
        sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 200);}");
        lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 200);}");
        gripperGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 200);}");
        flowChartGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 200);}");
        timeGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 200);}");
        connectGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border:6px solid rgb(200, 200, 200);}");
        rightButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");
        leftButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");
        prepareWidget->setPixmap(QPixmap::fromImage(prepareImage->scaled(int(1000*0.7),int(1000*0.7),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        logoWidget->setPixmap(QPixmap::fromImage(logoImage->scaled(int(800*0.7),int(800*0.7),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    if (screenSize == Screensize::M)
    {
        font = QFont("Arial Rounded MT Bold", 20);
        size = 40;
        sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
        lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
        gripperGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
        flowChartGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
        timeGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
        connectGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
        rightButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");
        leftButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");
        prepareWidget->setPixmap(QPixmap::fromImage(prepareImage->scaled(1000,1000,Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        logoWidget->setPixmap(QPixmap::fromImage(logoImage->scaled(int(800),int(800),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }
    if (screenSize == Screensize::L)
    {
        font = QFont("Arial Rounded MT Bold", 22);
        size = 55;
        sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
        lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
        gripperGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
        flowChartGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
        timeGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
        connectGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
        rightButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 50px; border: 20px solid rgb(200, 200, 200);}");
        leftButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 50px; border: 20px solid rgb(200, 200, 200);}");
        prepareWidget->setPixmap(QPixmap::fromImage(prepareImage->scaled(int(1000*1.4),int(1000*1.4),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        logoWidget->setPixmap(QPixmap::fromImage(logoImage->scaled(int(800*1.4),int(800*1.4),Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    }

    sliderGroupbox->setLayout(sliderLayout);

    sliderLayout->addWidget(sliderWidget);

    lightGroupbox->setLayout(lightLayout);

    lightLayout->addWidget(lightWidget);

    gripperGroupbox->setLayout(gripperLayout);

    gripperLayout->addWidget(gripperWidget);

    flowChartGroupbox->setLayout(flowChartLayout);

    flowChartLayout->addWidget(flowChartWidget);

    timeGroupbox->setLayout(timeLayout);

    timeLayout->addWidget(timeWidget);

    connectGroupbox->setLayout(connectLayout);

    connectLayout->addWidget(connectWidget);

    rightButton->setIcon(QIcon(":/images/icons/rightside.png"));
    rightButton->setMinimumSize(size*8,3*size);

    leftButton->setIcon(QIcon(":/images/icons/leftside.png"));
    leftButton->setMinimumSize(size*8,3*size);

    buttonWidget->setLayout(buttonLayout);
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);

    buttonLayout->setContentsMargins(0,25,0,25);

    versionLabel->setText("V " + OneSmartControl::version.toString());
    versionLabel->setAlignment(Qt::AlignHCenter);
    versionLabel->setFont(font);

    infoLabel->setFont(font);
    infoLabel->setText("");

    connect(rightButton, SIGNAL(released()),this,SLOT(rightButtonHandle()));
    connect(leftButton, SIGNAL(released()),this,SLOT(leftButtonHandle()));

    changeLayout(page);

    ui->centralWidget->setLayout(basicLayout);
}

void SmartControlMainWindow::changeLayout(uint page)
{
    delete basicLayout;
    basicLayout = new QVBoxLayout;

    basicLayout->setContentsMargins(50,25,50,25);

    switch (page)
    {
    case Page::start:
        prepareWidget->hide();
        basicLayout->addStretch(5);
        basicLayout->addWidget(logoWidget,Qt::AlignCenter);
        basicLayout->addWidget(versionLabel,Qt::AlignHCenter);
        basicLayout->addStretch(5);
        basicLayout->addWidget(buttonWidget,0,Qt::AlignBottom);
        leftButton->setEnabled(false);
        logoWidget->show();
        versionLabel->show();
        break;

    case Page::prepare:
        logoWidget->hide();
        connectGroupbox->hide();
        versionLabel->hide();
        basicLayout->addStretch(1);
        basicLayout->addWidget(prepareWidget,Qt::AlignCenter);
        basicLayout->addStretch(1);
        basicLayout->addWidget(buttonWidget,0,Qt::AlignBottom);
        leftButton->setEnabled(true);
        rightButton->setEnabled(true);
        prepareWidget->show();
        break;

    case Page::connect:
        prepareWidget->hide();
        sliderGroupbox->hide();
        infoLabel->hide();
        basicLayout->addStretch(1);
        basicLayout->addWidget(connectGroupbox);
        basicLayout->addStretch(1);
        basicLayout->addWidget(buttonWidget,0,Qt::AlignBottom);
        leftButton->setEnabled(true);
        rightButton->setEnabled(true);
        connectGroupbox->show();
        break;

    case Page::slider:
        gripperGroupbox->hide();
        connectGroupbox->hide();
        lightGroupbox->hide();
        timeGroupbox->hide();
        basicLayout->addWidget(infoLabel);
        basicLayout->addWidget(sliderGroupbox);
        basicLayout->addStretch(10);
        basicLayout->addWidget(buttonWidget,0,Qt::AlignBottom);
        leftButton->setEnabled(true);
        rightButton->setEnabled(true);
        sliderGroupbox->show();
        infoLabel->show();
        break;

    case Page::functions:
        sliderGroupbox->hide();
        flowChartGroupbox->hide();
        basicLayout->addWidget(infoLabel);
        basicLayout->addStretch(1);
        basicLayout->addWidget(lightGroupbox);
        basicLayout->addStretch(5);
        basicLayout->addWidget(timeGroupbox);
        basicLayout->addStretch(5);
        basicLayout->addWidget(gripperGroupbox);
        basicLayout->addStretch(5);
        basicLayout->addWidget(buttonWidget,0,Qt::AlignBottom);
        leftButton->setEnabled(true);
        rightButton->setEnabled(true);
        lightGroupbox->show();
        timeGroupbox->show();
        gripperGroupbox->show();
        infoLabel->show();
        break;

    case Page::flowchart:
        logoWidget->hide();
        lightGroupbox->hide();
        timeGroupbox->hide();
        infoLabel->hide();
        gripperGroupbox->hide();
        basicLayout->addWidget(flowChartGroupbox);
        basicLayout->addWidget(buttonWidget,0,Qt::AlignBottom);
        rightButton->setEnabled(false);
        flowChartGroupbox->show();
        break;
    }
    ui->centralWidget->setLayout(basicLayout);
}

void SmartControlMainWindow::leftButtonHandle()
{
    if(page>0)page--;
    changeLayout(page);
}

void SmartControlMainWindow::rightButtonHandle()
{
    page++;
    changeLayout(page);
}

void SmartControlMainWindow::showToChartMessage()
{
    if(smartControlData.dataid == ID::move && smartControlData.workingSpaceStatus)
    {
        infoLabel->setAlignment(Qt::AlignHCenter);
        infoLabel->setStyleSheet("QLabel{ color: rgb(200, 50, 50);}");
        infoLabel->setText("Position out of workingspace!");
    }
    else
    {
        infoLabel->setAlignment(Qt::AlignHCenter);
        infoLabel->setStyleSheet("QLabel{ color: rgb(30, 144, 255);}");
        infoLabel->setText("Command added to flowchart >>");
        QTimer::singleShot(500, this, &SmartControlMainWindow::hideToChartMessage);
    }
}

void SmartControlMainWindow::hideToChartMessage()
{
    infoLabel->setText("");
}

void SmartControlMainWindow::sliderWidgetBorder()
{
    if(smartControlData.workingSpaceStatus)
    {
        if (screenSize == Screensize::XS)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 40, 40);}");
        }
        if (screenSize == Screensize::S)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 40, 40);}");
        }
        if (screenSize == Screensize::M)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 40, 40);}");
        }
        if (screenSize == Screensize::L)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 40, 40);}");
        }
        infoLabel->setAlignment(Qt::AlignHCenter);
        infoLabel->setStyleSheet("QLabel{ color: rgb(200, 50, 50);}");
        infoLabel->setText("Position out of workingspace!");        
    }
    else
    {
        infoLabel->setText("");

        if (screenSize == Screensize::XS)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
        }
        if (screenSize == Screensize::S)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 200);}");
        }
        if (screenSize == Screensize::M)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
        }
        if (screenSize == Screensize::L)
        {
            sliderGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
        }
    }
}

void SmartControlMainWindow::lightWidgetBorder()
{
    if (screenSize == Screensize::XS)
    {
        if(smartControlData.colour == Colour::red) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 40, 40);}");
        else if(smartControlData.colour == Colour::green) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(20, 200, 20);}");
        else if(smartControlData.colour == Colour::blue) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(20, 20, 200);}");
        else if(smartControlData.colour == Colour::cyan) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(20, 200, 200);}");
        else if(smartControlData.colour == Colour::magenta) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 20, 200);}");
        else if(smartControlData.colour == Colour::yellow) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 20);}");
        else if(smartControlData.colour == Colour::white) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(240, 240, 240);}");
        else lightGroupbox->setStyleSheet("QGroupBox {border-radius: 20px; border: 4px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::S)
    {
        if(smartControlData.colour == Colour::red) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 40, 40);}");
        else if(smartControlData.colour == Colour::green) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(20, 200, 20);}");
        else if(smartControlData.colour == Colour::blue) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(20, 20, 200);}");
        else if(smartControlData.colour == Colour::cyan) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(20, 200, 200);}");
        else if(smartControlData.colour == Colour::magenta) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 20, 200);}");
        else if(smartControlData.colour == Colour::yellow) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 20);}");
        else if(smartControlData.colour == Colour::white) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(240, 240, 240);}");
        else lightGroupbox->setStyleSheet("QGroupBox {border-radius: 30px; border: 6px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::M)
    {
        if(smartControlData.colour == Colour::red) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 40, 40);}");
        else if(smartControlData.colour == Colour::green) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(20, 200, 20);}");
        else if(smartControlData.colour == Colour::blue) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(20, 20, 200);}");
        else if(smartControlData.colour == Colour::cyan) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(20, 200, 200);}");
        else if(smartControlData.colour == Colour::magenta) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 20, 200);}");
        else if(smartControlData.colour == Colour::yellow) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 20);}");
        else if(smartControlData.colour == Colour::white) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(240, 240, 240);}");
        else lightGroupbox->setStyleSheet("QGroupBox {border-radius: 50px; border: 8px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::L)
    {
        if(smartControlData.colour == Colour::red) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 40, 40);}");
        else if(smartControlData.colour == Colour::green) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(20, 200, 20);}");
        else if(smartControlData.colour == Colour::blue) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(20, 20, 200);}");
        else if(smartControlData.colour == Colour::cyan) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(20, 200, 200);}");
        else if(smartControlData.colour == Colour::magenta) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 20, 200);}");
        else if(smartControlData.colour == Colour::yellow) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 20);}");
        else if(smartControlData.colour == Colour::white) lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(240, 240, 240);}");
        else lightGroupbox->setStyleSheet("QGroupBox {border-radius: 75px; border: 12px solid rgb(200, 200, 200);}");
    }
}

void SmartControlMainWindow::playlistOn()
{
    leftButton->setEnabled(false);
}

void SmartControlMainWindow::playlistOff()
{
    leftButton->setEnabled(true);
}
