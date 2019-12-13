#include "connectwidget.h"

OneSmartControl::ConnectWidget::ConnectWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent) :
    QWidget(parent),
    screenSize(screenSize),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QVBoxLayout(this);

    connectLayout = new QHBoxLayout;
    statusLayout = new QVBoxLayout;

    connectWidget = new QWidget;
    statusWidget = new QWidget;

    connectButton = new QPushButton;
    disconnectButton = new QPushButton;
    refreshButton = new QPushButton;

    devicesListView= new QListView;
    devicesStringList = new QStringList;
    devicesListModel = new QStringListModel;

    scanProgressBar = new QProgressBar;

    statusLabel = new QLabel;
    idLabel = new QLabel;
    portLabel = new QLabel;

    connectionFailedImage = new QImage;
    connectionfailedWidget = new QLabel;

    scanProgressTimer = new QTimer;

    createLayout();

    connect(&robot.connection,SIGNAL(connectingDevice()),this,SLOT(connectingDevice()));
    connect(&robot.connection, SIGNAL(deviceConnected(char)),this,SLOT(deviceConnected(char)));
    connect(&robot.connection,SIGNAL(deviceDisconnected()),this,SLOT(deviceDisconnected()));
    connect(&robot.connection,SIGNAL(scanStarted()),this,SLOT(scanStarted()));
    connect(&robot.connection,SIGNAL(scanFinished()),this,SLOT(scanFinished()));
    connect(&robot.connection,SIGNAL(handshakeFailed()),this,SLOT(handshakeFailed()));
    connect(&robot.connection, SIGNAL(updateScanValue(int)),this,SLOT(scanProgressBarHandle(int)));
    connect(scanProgressTimer, SIGNAL(timeout()), this, SLOT(scanProgressTimerHandle()));
}

void OneSmartControl::ConnectWidget::createLayout()
{
    QFont font;

    if (screenSize == Screensize::XS)
    {
        font = QFont("Arial Rounded MT Bold", 18);

        devicesListView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 15px; border: 4px solid rgb(200, 200, 200); padding: 10px 10px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 4px; border: 1px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 12px; background-color: rgb(200, 200, 200); border: 2px transparent; border-radius: 6px;}"
                                       "QScrollBar::handle:horizontal{height: 12px; background: rgb(30, 144, 255); border: 2px rgb(30, 144, 255); border-radius: 6px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 12px; background-color: rgb(200, 200, 200); border: 2px transparent; border-radius: 6px;}"
                                       "QScrollBar::handle:vertical{width: 12px; background: rgb(30, 144, 255); border: 2px rgb(30, 144, 255); border-radius: 6px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        devicesListView->setMinimumHeight(int(400*0.33));
        devicesListView->setMinimumWidth(int(800*0.33));
        devicesListView->setMaximumWidth(int(800*0.33));

        scanProgressBar->setMinimumWidth(int(800*0.33));
        scanProgressBar->setMaximumWidth(int(800*0.33));
        scanProgressBar->setStyleSheet("QProgressBar {border-radius: 15px; border: 3px solid rgb(200, 200, 200);height: 24px;}"
                                       "QProgressBar::chunk {background-color: rgb(30, 144, 255);border-bottom-right-radius: 12px;border-bottom-left-radius: 12px;border-top-right-radius: 12px;border-top-left-radius: 12px; padding: 2px 2px;}");

        connectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        connectButton->setIconSize(QSize(65, 65));
        disconnectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        disconnectButton->setIconSize(QSize(65, 65));
        refreshButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        refreshButton->setIconSize(QSize(65, 65));

        statusLayout->setSpacing(10);
        basicLayout->setSpacing(10);
    }
    if (screenSize == Screensize::S)
    {
        font = QFont("Arial Rounded MT Bold", 19);

        devicesListView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 30px; border: 6px solid rgb(200, 200, 200); padding: 15px 15px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 6px; border: 3px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 24px; background-color: rgb(200, 200, 200); border: 4px transparent; border-radius: 12px;}"
                                       "QScrollBar::handle:horizontal{height: 24px; background: rgb(30, 144, 255); border: 4px rgb(30, 144, 255); border-radius: 12px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 24px; background-color: rgb(200, 200, 200); border: 4px transparent; border-radius: 12px;}"
                                       "QScrollBar::handle:vertical{width: 24px; background: rgb(30, 144, 255); border: 4px rgb(30, 144, 255); border-radius: 12px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        devicesListView->setMinimumHeight(int(400*0.66));
        devicesListView->setMinimumWidth(int(800*0.66));
        devicesListView->setMaximumWidth(int(800*0.66));

        scanProgressBar->setMinimumWidth(int(800*0.66));
        scanProgressBar->setMaximumWidth(int(800*0.66));
        scanProgressBar->setStyleSheet("QProgressBar {border-radius: 30px; border: 6px solid rgb(200, 200, 200);height: 48px;}"
                                       "QProgressBar::chunk {background-color: rgb(30, 144, 255);border-bottom-right-radius: 24px;border-bottom-left-radius: 24px;border-top-right-radius: 24px;border-top-left-radius: 24px; padding: 2px 2px;}");

        connectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        connectButton->setIconSize(QSize(100, 100));
        disconnectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        disconnectButton->setIconSize(QSize(100, 100));
        refreshButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        refreshButton->setIconSize(QSize(100, 100));

        statusLayout->setSpacing(15);
        basicLayout->setSpacing(15);
    }
    if (screenSize == Screensize::M)
    {
        font = QFont("Arial Rounded MT Bold", 20);

        devicesListView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 50px; border: 8px solid rgb(200, 200, 200); padding: 20px 20px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 8px; border: 4px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 30px; background-color: rgb(200, 200, 200); border: 5px transparent; border-radius: 15px;}"
                                       "QScrollBar::handle:horizontal{height: 30px; background: rgb(30, 144, 255); border: 5px rgb(30, 144, 255); border-radius: 15px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 30px; background-color: rgb(200, 200, 200); border: 5px transparent; border-radius: 15px;}"
                                       "QScrollBar::handle:vertical{width: 30px; background: rgb(30, 144, 255); border: 5px rgb(30, 144, 255); border-radius: 15px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        devicesListView->setMinimumHeight(400);
        devicesListView->setMinimumWidth(800);
        devicesListView->setMaximumWidth(800);

        scanProgressBar->setMinimumWidth(800);
        scanProgressBar->setMaximumWidth(800);
        scanProgressBar->setStyleSheet("QProgressBar {border-radius: 50px; border: 8px solid rgb(200, 200, 200);height: 84px;}"
                                       "QProgressBar::chunk {background-color: rgb(30, 144, 255);border-bottom-right-radius: 42px;border-bottom-left-radius: 42px;border-top-right-radius: 42px;border-top-left-radius: 42px; padding: 2px 2px;}");

        connectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        connectButton->setIconSize(QSize(150, 150));
        disconnectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        disconnectButton->setIconSize(QSize(150, 150));
        refreshButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        refreshButton->setIconSize(QSize(150, 150));

        statusLayout->setSpacing(20);
        basicLayout->setSpacing(20);
    }
    if (screenSize == Screensize::L)
    {
        font = QFont("Arial Rounded MT Bold", 22);

        devicesListView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 75px; border: 15px solid rgb(200, 200, 200); padding: 25px 25px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 15px; border: 5px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 40px; background-color: rgb(200, 200, 200); border: 6px transparent; border-radius: 20px;}"
                                       "QScrollBar::handle:horizontal{height: 40px; background: rgb(30, 144, 255); border: 6px rgb(30, 144, 255); border-radius: 20px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 40px; background-color: rgb(200, 200, 200); border: 6px transparent; border-radius: 20px;}"
                                       "QScrollBar::handle:vertical{width: 40px; background: rgb(30, 144, 255); border: 6px rgb(30, 144, 255); border-radius: 20px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        devicesListView->setMinimumHeight(int(400*1.33));
        devicesListView->setMinimumWidth(int(800*1.33));
        devicesListView->setMaximumWidth(int(800*1.33));

        scanProgressBar->setMinimumWidth(int(800*1.33));
        scanProgressBar->setMaximumWidth(int(800*1.33));
        scanProgressBar->setStyleSheet("QProgressBar {border-radius: 65px; border: 10px solid rgb(200, 200, 200);height: 110px;}"
                                       "QProgressBar::chunk {background-color: rgb(30, 144, 255);border-bottom-right-radius: 55px;border-bottom-left-radius: 55px;border-top-right-radius: 55px;border-top-left-radius: 55px; padding: 3px 3px;}");

        connectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        connectButton->setIconSize(QSize(200, 200));
        disconnectButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        disconnectButton->setIconSize(QSize(200, 200));
        refreshButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        refreshButton->setIconSize(QSize(200, 200));

        statusLayout->setSpacing(25);
        basicLayout->setSpacing(25);
    }


    devicesListView->setFont(font);
    scanProgressBar->setFont(font);

    scanProgressBar->setTextVisible(false);
    scanProgressBar->setValue(0);
    scanProgressBar->setMinimum(0);
    scanProgressBar->setMaximum(150);

    connectButton->setIcon(QIcon(":/images/icons/connect.png"));

    connect(connectButton, SIGNAL(released()),this,SLOT(connectButtonHandle()));

    disconnectButton->setIcon(QIcon(":/images/icons/disconnect.png"));

    connect(disconnectButton, SIGNAL(released()),this,SLOT(disconnectButtonHandle()));

    refreshButton->setIcon(QIcon(":/images/icons/refresh.png"));

    connect(refreshButton, SIGNAL(released()),this,SLOT(refreshButtonHandle()));

    statusLabel->setFont(font);

    statusLabel->setText("Status: disconnected");
    idLabel->setFont(font);
    idLabel->setText("Robot-ID: -");
    portLabel->setFont(font);
    portLabel->setText("BLE-Modul: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(true);
    disconnectButton->setEnabled(false);

    connectLayout->addWidget(refreshButton);
    connectLayout->addWidget(connectButton);
    connectLayout->addWidget(disconnectButton);
    connectWidget->setLayout(connectLayout);

    statusLayout->addWidget(statusLabel,0,Qt::AlignCenter);
    statusLayout->addWidget(portLabel,0,Qt::AlignCenter);
    statusLayout->addWidget(idLabel,0,Qt::AlignCenter);

    statusWidget->setLayout(statusLayout);

    basicLayout->addWidget(connectWidget);
    basicLayout->addWidget(devicesListView,0,Qt::AlignCenter);
    basicLayout->addWidget(scanProgressBar,0,Qt::AlignCenter);
    basicLayout->addWidget(statusWidget);

    setLayout(basicLayout);
}

void OneSmartControl::ConnectWidget::selectionChangedHandle( const QModelIndex& selected, const QModelIndex& deselected )
{
    connectButton->setEnabled(true);
    refreshButton->setEnabled(true);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(true);
}

void OneSmartControl::ConnectWidget::scanProgressBarHandle(int value)
{
    scanProgressBar->setValue(value+20);
    this->repaint();
};

void OneSmartControl::ConnectWidget::scanProgressTimerHandle()
{
    scanProgressValue++;
    emit scanProgressBarHandle(scanProgressValue);
};

void OneSmartControl::ConnectWidget::connectButtonHandle()
{
    idLabel->setText("Robot-ID: -");
    portLabel->setText("BLE-Modul: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);

    int index = devicesListView->currentIndex().row();
    robot.connection.connectDevice(index);
}

void OneSmartControl::ConnectWidget::handshakeFailed()
{
    statusLabel->setText("Status: handshake failed");
    idLabel->setText("Robot-ID: -");
    portLabel->setText("BLE-Modul: -");
}

void OneSmartControl::ConnectWidget::disconnectButtonHandle()
{
    statusLabel->setText("Status: disconnect...");
    idLabel->setText("Robot-ID: -");
    portLabel->setText("BLE-Modul: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);

    robot.connection.disconnectDevice();
}

void OneSmartControl::ConnectWidget::refreshButtonHandle()
{
    QBluetoothLocalDevice localDevice;

    if (localDevice.isValid())
    {
        localDevice.powerOn();
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    }
    else
    {
        statusLabel->setText("Status: bluetooth disabled");
        idLabel->setText("Robot-ID: -");
        portLabel->setText("BLE-Modul: -");

        connectButton->setEnabled(false);
        refreshButton->setEnabled(true);
        disconnectButton->setEnabled(false);
        devicesListView->setEnabled(false);
    }

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);

    devicesStringList->clear();
    devicesListModel->setStringList( QStringList{} );
    devicesListView->setModel(devicesListModel);
    robot.connection.startDeviceDiscovery();
}

void OneSmartControl::ConnectWidget::connectingDevice()
{
    statusLabel->setText("Status: connecting...");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);
}

void OneSmartControl::ConnectWidget::deviceConnected(char id)
{
    statusLabel->setText("Status: connected");

    QString qid = QString::fromStdString(&id);

    int index = devicesListView->currentIndex().row();
    QString modul = devicesStringList->at(index);

    idLabel->setText("Robot-ID: " + qid);
    portLabel->setText("BLE-Modul: " + modul);

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(true);
    devicesListView->setEnabled(false);
}

void OneSmartControl::ConnectWidget::deviceDisconnected()
{
    statusLabel->setText("Status: disconnected");
    idLabel->setText("Robot-ID: -");
    portLabel->setText("BLE-Modul: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(true);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);

    devicesStringList->clear();
    devicesListModel->setStringList( QStringList{} );
    devicesListView->setModel(devicesListModel);
}

void OneSmartControl::ConnectWidget::scanStarted()
{
    scanProgressValue=0;
    scanProgressBar->setValue(scanProgressValue);
    scanProgressTimer->start(100);
    devicesStringList->clear();
    devicesListModel->setStringList( QStringList{} );
    devicesListView->setModel(devicesListModel);

    statusLabel->setText("Status: scanning...");
    idLabel->setText("Robot-ID: -");
    portLabel->setText("BLE-Modul: -");

    connectButton->setEnabled(false);
    refreshButton->setEnabled(false);
    disconnectButton->setEnabled(false);
    devicesListView->setEnabled(false);
}

void OneSmartControl::ConnectWidget::scanFinished()
{
    scanProgressValue=150;
    scanProgressBar->setValue(scanProgressValue);
    scanProgressTimer->stop();

    QList<QString> deviceList = robot.connection.getDeviceList();

    devicesStringList->clear();
    devicesListModel->setStringList( QStringList{} );
    devicesListView->setModel(devicesListModel);

    if(!deviceList.empty())
    {
        statusLabel->setText("Status: scan finished");
        idLabel->setText("Robot-ID: -");
        portLabel->setText("BLE-Modul: -");

        connectButton->setEnabled(false);
        refreshButton->setEnabled(true);
        disconnectButton->setEnabled(false);
        devicesListView->setEnabled(true);

        for (int i = 0; i < deviceList.size(); i++)
        {
            devicesStringList->append(deviceList.at(i));
            devicesListModel->setStringList(*devicesStringList);
            devicesListView->setModel(devicesListModel);
        }
    }
    else
    {
        statusLabel->setText("Status: no device found");
        idLabel->setText("Robot-ID: -");
        portLabel->setText("BLE-Modul: -");

        connectButton->setEnabled(false);
        refreshButton->setEnabled(true);
        disconnectButton->setEnabled(false);
        devicesListView->setEnabled(false);
    }

    QItemSelectionModel *selectionModel = devicesListView->selectionModel();
    connect(selectionModel,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(selectionChangedHandle(QModelIndex,QModelIndex)));
};
