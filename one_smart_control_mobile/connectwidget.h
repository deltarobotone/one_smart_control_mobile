#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QListView>
#include <QProgressBar>
#include <QStringListModel>

#include "config.h"
#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace OneSmartControl
{

class ConnectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConnectWidget(EasyProtocol &easyProtocol, OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent = nullptr);

private:
    uint screenSize;
    EasyProtocol &robot;
    OneSmartControl::SmartControlData &controlData;

    QVBoxLayout *basicLayout;
    QHBoxLayout *connectLayout;
    QVBoxLayout *statusLayout;

    QWidget *connectWidget;
    QWidget *statusWidget;

    QLabel *statusLabel;
    QLabel *idLabel;
    QLabel *portLabel;

    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QPushButton *refreshButton;

    QProgressBar *scanProgressBar;

    QListView *devicesListView;
    QStringList *devicesStringList;
    QStringListModel *devicesListModel;

    QImage *connectionFailedImage;
    QLabel *connectionfailedWidget;

    int scanProgressValue = 0;
    QTimer *scanProgressTimer;

    void createLayout();

private slots:
    void connectButtonHandle();
    void disconnectButtonHandle();
    void refreshButtonHandle();
    void scanProgressBarHandle(int value);
    void scanProgressTimerHandle();
    void selectionChangedHandle( const QModelIndex& selected, const QModelIndex& deselected );

public slots:
    void scanFinished();
    void scanStarted();
    void deviceDisconnected();
    void connectingDevice();
    void handshakeFailed();
    void deviceConnected(char id);
};

} // OneSmartControl

#endif // CONNECTWIDGET_H
