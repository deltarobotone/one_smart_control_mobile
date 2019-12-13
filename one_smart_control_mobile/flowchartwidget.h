#ifndef FLOWCHARTWIDGET_H
#define FLOWCHARTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QUrl>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardPaths>
#include <QtAndroidExtras/QtAndroid>
#include <QApplication>

#include "config.h"
#include "easyprotocol.h"
#include "smartcontroldata.h"
#include "timewidget.h"

namespace OneSmartControl
{

class FlowChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlowChartWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent = nullptr);

private:
    uint screenSize;
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;

    QVBoxLayout *basicLayout;
    QHBoxLayout *buttonRowLayout;
    QWidget *buttonRow;

    QListView *controlChartView;
    QStringList *controlDataList;
    QStringListModel *controlDataListModel;

    QList<OneSmartControl::SmartControlData> controlDataStore;

    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *deleteButton;
    QPushButton *playButton;
    QPushButton *upButton;
    QPushButton *downButton;

    bool running = false;
    int selectedRow = 0;

    QFileDialog *fileDialog;
    void createLayout();
    void activatePlayList();

public slots:
    void addData();
    void fileSelected(const QString &filename);
    void freeChannel();
    void nextCommand();

private slots:

    void loadButtonHandle();
    void saveButtonHandle();
    void deleteButtonHandle();
    void playButtonHandle();
    void upButtonHandle();
    void downButtonHandle();

signals:
    void playlistOn();
    void playlistOff();
};

} // OneSmartControl

#endif // FLOWCHARTWIDGET_H
