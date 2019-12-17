#include "flowchartwidget.h"

OneSmartControl::FlowChartWidget::FlowChartWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent):
    QWidget(parent),
    screenSize(screenSize),
    robot(easyProtocol),
    controlData(smartControlData)
{
    basicLayout = new QVBoxLayout(this);
    buttonRowLayout = new QHBoxLayout;
    buttonRow = new QWidget;

    controlChartView= new QListView;
    controlDataList = new QStringList;
    controlDataListModel = new QStringListModel;

    loadButton = new QPushButton;
    saveButton = new QPushButton;
    deleteButton = new QPushButton;
    playButton = new QPushButton;
    upButton = new QPushButton;
    downButton = new QPushButton;

    fileDialog = new QFileDialog(this);

    createLayout();
}

void OneSmartControl::FlowChartWidget::createLayout()
{

    QFont font;

    if (screenSize == Screensize::XS)
    {
        font = QFont("Arial Rounded MT Bold", 13);

        controlChartView->setFont(font);
        controlChartView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 15px; border: 4px solid rgb(200, 200, 200); padding: 10px 10px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 4px; border: 1px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 12px; background-color: rgb(200, 200, 200); border: 2px transparent; border-radius: 6px;}"
                                       "QScrollBar::handle:horizontal{height: 12px; background: rgb(30, 144, 255); border: 2px rgb(30, 144, 255); border-radius: 6px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 12px; background-color: rgb(200, 200, 200); border: 2px transparent; border-radius: 6px;}"
                                       "QScrollBar::handle:vertical{width: 12px; background: rgb(30, 144, 255); border: 2px rgb(30, 144, 255); border-radius: 6px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        saveButton->setIcon(QIcon(":/images/icons/save.png"));
        loadButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        loadButton->setIconSize(QSize(50, 50));
        saveButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        saveButton->setIconSize(QSize(50, 50));
        deleteButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        deleteButton->setIconSize(QSize(50, 50));
        playButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        playButton->setIconSize(QSize(50, 50));
        upButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        upButton->setIconSize(QSize(50, 50));
        downButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 6px; border: 1px solid rgb(255, 255, 255);}");
        downButton->setIconSize(QSize(50, 50));

        basicLayout->setSpacing(12);
    }
    if (screenSize == Screensize::S)
    {
        font = QFont("Arial Rounded MT Bold", 13);

        controlChartView->setFont(font);
        controlChartView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 30px; border: 6px solid rgb(200, 200, 200); padding: 15px 15px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 6px; border: 3px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 24px; background-color: rgb(200, 200, 200); border: 4px transparent; border-radius: 12px;}"
                                       "QScrollBar::handle:horizontal{height: 24px; background: rgb(30, 144, 255); border: 4px rgb(30, 144, 255); border-radius: 12px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 24px; background-color: rgb(200, 200, 200); border: 4px transparent; border-radius: 12px;}"
                                       "QScrollBar::handle:vertical{width: 24px; background: rgb(30, 144, 255); border: 4px rgb(30, 144, 255); border-radius: 12px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        saveButton->setIcon(QIcon(":/images/icons/save.png"));
        loadButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        loadButton->setIconSize(QSize(75, 75));
        saveButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        saveButton->setIconSize(QSize(75, 75));
        deleteButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        deleteButton->setIconSize(QSize(75, 75));
        playButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        playButton->setIconSize(QSize(75, 75));
        upButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        upButton->setIconSize(QSize(75, 75));
        downButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 8px; border: 1px solid rgb(255, 255, 255);}");
        downButton->setIconSize(QSize(75, 75));

        basicLayout->setSpacing(20);
    }
    if (screenSize == Screensize::M)
    {
        font = QFont("Arial Rounded MT Bold", 14);

        controlChartView->setFont(font);
        controlChartView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 50px; border: 8px solid rgb(200, 200, 200); padding: 20px 20px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 8px; border: 4px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 30px; background-color: rgb(200, 200, 200); border: 5px transparent; border-radius: 15px;}"
                                       "QScrollBar::handle:horizontal{height: 30px; background: rgb(30, 144, 255); border: 5px rgb(30, 144, 255); border-radius: 15px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 30px; background-color: rgb(200, 200, 200); border: 5px transparent; border-radius: 15px;}"
                                       "QScrollBar::handle:vertical{width: 30px; background: rgb(30, 144, 255); border: 5px rgb(30, 144, 255); border-radius: 15px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        saveButton->setIcon(QIcon(":/images/icons/save.png"));
        loadButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        loadButton->setIconSize(QSize(100, 100));
        saveButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        saveButton->setIconSize(QSize(100, 100));
        deleteButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        deleteButton->setIconSize(QSize(100, 100));
        playButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        playButton->setIconSize(QSize(100, 100));
        upButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        upButton->setIconSize(QSize(100, 100));
        downButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 10px; border: 1px solid rgb(255, 255, 255);}");
        downButton->setIconSize(QSize(100, 100));

        basicLayout->setSpacing(28);
    }
    if (screenSize == Screensize::L)
    {
        font = QFont("Arial Rounded MT Bold", 15);

        controlChartView->setFont(font);
        controlChartView->setStyleSheet("QListView {background-color: rgb(255, 255, 255); border-radius: 75px; border: 15px solid rgb(200, 200, 200); padding: 25px 25px;}"
                                       "QListView::item:selected{background-color: rgb(30, 144, 255);border-radius: 15px; border: 5px solid rgb(200, 200, 200);}"
                                       "QScrollBar:horizontal{height: 40px; background-color: rgb(200, 200, 200); border: 6px transparent; border-radius: 20px;}"
                                       "QScrollBar::handle:horizontal{height: 40px; background: rgb(30, 144, 255); border: 6px rgb(30, 144, 255); border-radius: 20px;}"
                                       "QScrollBar::add-line:horizontal{border: none;background: none;}"
                                       "QScrollBar::sub-line:horizontal{border: none;background: none;}"
                                       "QScrollBar:vertical{width: 40px; background-color: rgb(200, 200, 200); border: 6px transparent; border-radius: 20px;}"
                                       "QScrollBar::handle:vertical{width: 40px; background: rgb(30, 144, 255); border: 6px rgb(30, 144, 255); border-radius: 20px;}"
                                       "QScrollBar::add-line:vertical{border: none;background: none;}"
                                       "QScrollBar::sub-line:vertical{border: none;background: none;}");

        saveButton->setIcon(QIcon(":/images/icons/save.png"));
        loadButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        loadButton->setIconSize(QSize(130, 130));
        saveButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        saveButton->setIconSize(QSize(130, 130));
        deleteButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        deleteButton->setIconSize(QSize(130, 130));
        playButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        playButton->setIconSize(QSize(130, 130));
        upButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        upButton->setIconSize(QSize(130, 130));
        downButton->setStyleSheet("QPushButton{ background-color: rgb(255, 255, 255); border-radius: 14px; border: 2px solid rgb(255, 255, 255);}");
        downButton->setIconSize(QSize(130, 130));

        basicLayout->setSpacing(36);
    }

    controlChartView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    controlChartView->setSelectionMode(QAbstractItemView::SingleSelection);

    deleteButton->setIcon(QIcon(":/images/icons/delete.png"));
    playButton->setIcon(QIcon(":/images/icons/play.png"));
    downButton->setIcon(QIcon(":/images/icons/down.png"));
    upButton->setIcon(QIcon(":/images/icons/up.png"));
    loadButton->setIcon(QIcon(":/images/icons/load.png"));

    connect(loadButton, SIGNAL(released()),this,SLOT(loadButtonHandle()));
    connect(saveButton, SIGNAL(released()),this,SLOT(saveButtonHandle()));
    connect(deleteButton, SIGNAL(released()),this,SLOT(deleteButtonHandle()));
    connect(playButton, SIGNAL(released()),this,SLOT(playButtonHandle()));
    connect(upButton, SIGNAL(released()),this,SLOT(upButtonHandle()));
    connect(downButton, SIGNAL(released()),this,SLOT(downButtonHandle()));
    connect(fileDialog,SIGNAL(fileSelected(const QString)),this,SLOT(fileSelected(const QString)));

    connect(&robot.connection,SIGNAL(freeChannel()),this,SLOT(freeChannel()));
    connect(&robot.connection,SIGNAL(nextCommand()),this,SLOT(nextCommand()));

    buttonRowLayout->addWidget(upButton);
    buttonRowLayout->addWidget(downButton);
    buttonRowLayout->addWidget(deleteButton);
    buttonRowLayout->addWidget(playButton);
    buttonRowLayout->addWidget(loadButton);
    buttonRowLayout->addWidget(saveButton);

    buttonRow->setLayout(buttonRowLayout);

    basicLayout->addWidget(controlChartView);
    basicLayout->addWidget(buttonRow);

    setLayout(basicLayout);
}

void OneSmartControl::FlowChartWidget::addData()
{
    if(controlData.dataid == ID::move && controlData.workingSpaceStatus)
    {
        //Workingspace-Limit
    }
    else
    {
        controlDataStore.append(controlData);
        controlDataList->append(controlData.toString());
        controlDataListModel->setStringList(*controlDataList);
        controlChartView->setModel(controlDataListModel);
    }
}

void OneSmartControl::FlowChartWidget::upButtonHandle()
{
    int i = controlChartView->currentIndex().row();
    if(i>0)
    {
        SmartControlData data1 = controlDataStore.at(i);
        QString item1 = controlDataList->at(i);

        SmartControlData data2 = controlDataStore.at(i-1);
        QString item2 = controlDataList->at(i-1);

        controlDataList->replace(i-1,item1);
        controlDataStore.replace(i-1,data1);

        controlDataList->replace(i,item2);
        controlDataStore.replace(i,data2);

        controlDataListModel->setStringList(*controlDataList);
        controlChartView->setModel(controlDataListModel);

        QModelIndex index = controlDataListModel->index(i-1);
        controlChartView->setCurrentIndex(index);
    }
}

void OneSmartControl::FlowChartWidget::downButtonHandle()
{
    int i = controlChartView->currentIndex().row();

    if(i<controlDataStore.size()-1&&i<controlDataList->size()-1)
    {
        SmartControlData data1 = controlDataStore.at(i);
        QString item1 = controlDataList->at(i);

        SmartControlData data2 = controlDataStore.at(i+1);
        QString item2 = controlDataList->at(i+1);

        controlDataList->replace(i+1,item1);
        controlDataStore.replace(i+1,data1);

        controlDataList->replace(i,item2);
        controlDataStore.replace(i,data2);

        controlDataListModel->setStringList(*controlDataList);
        controlChartView->setModel(controlDataListModel);

        QModelIndex index = controlDataListModel->index(i+1);
        controlChartView->setCurrentIndex(index);
    }
}

void OneSmartControl::FlowChartWidget::deleteButtonHandle()
{
    int i = controlChartView->currentIndex().row();
    controlDataList->removeAt(i);
    controlDataStore.removeAt(i);

    controlDataListModel->setStringList(*controlDataList);
    controlChartView->setModel(controlDataListModel);

    if(i>0)
    {
        QModelIndex index = controlDataListModel->index(i-1);
        controlChartView->setCurrentIndex(index);
    }
    else controlChartView->clearSelection();
}

void OneSmartControl::FlowChartWidget::playButtonHandle()
{
    if(robot.connection.isConnected()&&!running)
    {
        loadButton->setEnabled(false);
        saveButton->setEnabled(false);
        deleteButton->setEnabled(false);
        upButton->setEnabled(false);
        downButton->setEnabled(false);

        emit playlistOn();

        running = true;
        playButton->setIcon(QIcon(":/images/icons/stop.png"));
        activatePlayList();
    }
    else
    {
        loadButton->setEnabled(true);
        saveButton->setEnabled(true);
        deleteButton->setEnabled(true);
        upButton->setEnabled(true);
        downButton->setEnabled(true);

        controlChartView->setSelectionMode(QAbstractItemView::SingleSelection);
        emit playlistOff();

        running = false;
        playButton->setIcon(QIcon(":/images/icons/play.png"));
        robot.connection.stopTransmission();
    }
}

void OneSmartControl::FlowChartWidget::loadButtonHandle()
{
    if(QtAndroid::androidSdkVersion() >= 23)
    {
        const QString READ_EXTERNAL_STORAGE("android.permission.READ_EXTERNAL_STORAGE");
        QtAndroid::requestPermissionsSync(QStringList() << READ_EXTERNAL_STORAGE);
    }

    //QString fileName = QFileDialog::getOpenFileName(this,tr("Open Flowchart"), QStandardPaths::displayName(QStandardPaths::DownloadLocation), tr("Flowchart (*.fc)"));
    //qDebug() << fileName;
    QStringList fileNames;
    fileDialog->setNameFilter(tr("Flowchart (*.fc)"));
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setViewMode(QFileDialog::Detail);
    if (fileDialog->exec())fileNames = fileDialog->selectedFiles();
    //qDebug() << fileNames;
}

void OneSmartControl::FlowChartWidget::fileSelected(const QString &filename)
{
    qDebug() << filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    controlDataStore.clear();

    QTextStream stream(&file);

    int header = 3;

    while (!stream.atEnd())
    {
        if(header == 0)
        {
            QString line = stream.readLine();
            SmartControlData data;
            data.fromDataString(line);
            controlDataStore.append(data);
        }
        else
        {
            QString line = stream.readLine();
            header--;
        }
    }

    controlDataList->clear();

    for (int i=0; i<controlDataStore.size();i++)
    {
        SmartControlData data = controlDataStore.at(i);
        controlDataList->append(data.toString());
    }

    controlDataListModel->setStringList(*controlDataList);
    controlChartView->setModel(controlDataListModel);
}

void OneSmartControl::FlowChartWidget::saveButtonHandle()
{
    if(QtAndroid::androidSdkVersion() >= 23)
    {
        const QString WRITE_EXTERNAL_STORAGE("android.permission.WRITE_EXTERNAL_STORAGE");
        QtAndroid::requestPermissionsSync(QStringList() << WRITE_EXTERNAL_STORAGE);
    }

    QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_HH_mm_ss");
    QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString filePath = path + "/Flowchart_" + timestamp +".fc";

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Flowchart"),filePath,tr("Flowchart (*.fc)"));

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);
    stream << "Delta-Robot One Smart Control Flowchart" << "\n";

    stream << "Version: " << OneSmartControl::version.toString() << "\n";

    stream << "Timestamp: " << timestamp << "\n";

    for (int i=0; i<controlDataStore.size();i++)
    {
        SmartControlData data = controlDataStore.at(i);
        stream << data.toDataString() << "\n";
    }
}

void OneSmartControl::FlowChartWidget::activatePlayList()
{
    QFont font("Arial Rounded MT Bold", 28);

    selectedRow=-1;
    QModelIndex index = controlDataListModel->index(selectedRow);
    controlChartView->setCurrentIndex(index);
    controlChartView->repaint();

    for (int i = 0;i<controlDataStore.size();i++)
    {
        controlData = controlDataStore.at(i);
        if(controlData.dataid == ID::move)
        {
            robot.move.ptp(controlData.xPosition,controlData.yPosition,controlData.zPosition,controlData.velocity);
        }
        if(controlData.dataid == ID::gripper)
        {
            if(controlData.gripperStatus == true) robot.gripper.close();
            else robot.gripper.open();
        }
        if(controlData.dataid == ID::light)
        {
            if(controlData.colour!=Protocol::lightoff)robot.light.setColour(controlData.colour,controlData.intensity);
            else robot.light.off();
        }
        if(controlData.dataid == ID::waitFor)
        {
            robot.functions.waitFor(controlData.waitFortime);
        }
    }
}

void OneSmartControl::FlowChartWidget::freeChannel()
{
    running = false;
    playButton->setIcon(QIcon(":/images/icons/play.png"));

    loadButton->setEnabled(true);
    saveButton->setEnabled(true);
    deleteButton->setEnabled(true);
    upButton->setEnabled(true);
    downButton->setEnabled(true);

    controlChartView->setSelectionMode(QAbstractItemView::SingleSelection);

    emit playlistOff();
}

void OneSmartControl::FlowChartWidget::nextCommand()
{
    if(running)
    {
        selectedRow++;
        QModelIndex index = controlDataListModel->index(selectedRow);
        controlChartView->setCurrentIndex(index);
        controlChartView->repaint();
    }
}
