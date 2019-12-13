#include "gripperwidget.h"

OneSmartControl::GripperWidget::GripperWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent):
    QWidget(parent),
    screenSize(screenSize),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QGridLayout(this);
    buttonRowLayout = new QHBoxLayout;

    buttonRow = new QWidget;
    openButton = new QPushButton;
    closeButton = new QPushButton;
    toChartButton = new QPushButton;

    createLayout();
}

void OneSmartControl::GripperWidget::createLayout()
{
    setStyleSheet("background-color:white;");

    QFont font;
    int size = 0;
    if (screenSize == Screensize::XS)
    {
        font = QFont("Arial Rounded MT Bold", 15);

        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 5px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(45, 45));

        size = 30;

        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");

        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");

        basicLayout->setSpacing(5);
    }
    if (screenSize == Screensize::S)
    {
        font = QFont("Arial Rounded MT Bold", 17);

        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(75, 75));

        size = 55;

        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");

        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");

        basicLayout->setSpacing(10);
    }
    if (screenSize == Screensize::M)
    {
        font = QFont("Arial Rounded MT Bold", 20);

        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 15px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(120, 120));

        size = 90;

        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");

        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");

        basicLayout->setSpacing(20);
    }
    if (screenSize == Screensize::L)
    {
        font = QFont("Arial Rounded MT Bold", 22);

        toChartButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 20px; border: 3px solid rgb(255, 255, 255);}");
        toChartButton->setIconSize(QSize(150, 150));

        size = 120;

        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 40px; border: 20px solid rgb(200, 200, 200);}");

        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 40px; border: 20px solid rgb(200, 200, 200);}");

        basicLayout->setSpacing(25);
    }

    openButton->setFont(font);
    openButton->setMinimumSize(int(size*3.5),size);
    openButton->setMaximumHeight(size);

    closeButton->setFont(font);
    closeButton->setMinimumSize(int(size*3.5),size);
    closeButton->setMaximumHeight(size);

    toChartButton->setIcon(QIcon(":/images/icons/next.png"));
    connect(toChartButton, SIGNAL(released()),this,SLOT(toChartButtonHandle()));

    openButton->setText("open");
    connect(openButton, SIGNAL(released()),this,SLOT(openGripper()));

    closeButton->setText("close");
    connect(closeButton, SIGNAL(released()),this,SLOT(closeGripper()));

    buttonRowLayout->addStretch(1);
    buttonRowLayout->addWidget(openButton);
    buttonRowLayout->addStretch(1);
    buttonRowLayout->addWidget(closeButton);
    buttonRowLayout->addStretch(1);
    buttonRow->setLayout(buttonRowLayout);

    basicLayout->addWidget(toChartButton,0,1);
    basicLayout->addWidget(buttonRow,0,0,1,1);

    setLayout(basicLayout);
}

void OneSmartControl::GripperWidget::openGripper()
{
    if (screenSize == Screensize::XS)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::S)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::M)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::L)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 40px; border: 20px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 40px; border: 20px solid rgb(200, 200, 200);}");
    }
    robot.gripper.open();
    controlData.gripperStatus = false;
    emit dataChanged();
}

void OneSmartControl::GripperWidget::closeGripper()
{
    if (screenSize == Screensize::XS)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 10px; border: 5px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::S)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 20px; border: 10px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::M)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 30px; border: 15px solid rgb(200, 200, 200);}");
    }
    if (screenSize == Screensize::L)
    {
        openButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); border-radius: 40px; border: 20px solid rgb(200, 200, 200);}");
        closeButton->setStyleSheet("QPushButton{ background-color: rgb(200, 200, 200); color: rgb(30, 144, 255); border-radius: 40px; border: 20px solid rgb(200, 200, 200);}");
    }
    robot.gripper.close();
    controlData.gripperStatus = true;
    emit dataChanged();
}

void OneSmartControl::GripperWidget::toChartButtonHandle()
{
    controlData.dataid = ID::gripper;
    emit toChart();
}
