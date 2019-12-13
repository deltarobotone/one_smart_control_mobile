#ifndef SMARTCONTROLMAINWINDOW_H
#define SMARTCONTROLMAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QImage>
#include <QScreen>
#include <QTimer>
#include "sliderwidget.h"
#include "flowchartwidget.h"
#include "lightwidget.h"
#include "gripperwidget.h"
#include "connectwidget.h"

#include "config.h"
#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace Ui {
class SmartControlMainWindow;
}

namespace Page
{
static const uint start = 0;
static const uint prepare = 1;
static const uint connect = 2;
static const uint slider = 3;
static const uint functions= 4;
static const uint flowchart = 5;
}

class SmartControlMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SmartControlMainWindow(QWidget *parent = nullptr);
    ~SmartControlMainWindow();

private:
    uint screenSize;
    EasyProtocol robot;
    OneSmartControl::SmartControlData smartControlData;

    QGroupBox *sliderGroupbox;
    QVBoxLayout *sliderLayout;
    OneSmartControl::SliderWidget *sliderWidget;

    QGroupBox *flowChartGroupbox;
    QVBoxLayout *flowChartLayout;
    OneSmartControl::FlowChartWidget *flowChartWidget;

    QGroupBox *lightGroupbox;
    QVBoxLayout *lightLayout;
    OneSmartControl::LightWidget *lightWidget;

    QGroupBox *gripperGroupbox;
    QVBoxLayout *gripperLayout;
    OneSmartControl::GripperWidget *gripperWidget;

    QGroupBox *connectGroupbox;
    QVBoxLayout *connectLayout;
    OneSmartControl::ConnectWidget *connectWidget;

    QGroupBox *timeGroupbox;
    QVBoxLayout *timeLayout;
    OneSmartControl::TimeWidget *timeWidget;

    QImage *logoImage;
    QLabel *logoWidget;

    QImage *prepareImage;
    QLabel *prepareWidget;

    QLabel *versionLabel;

    Ui::SmartControlMainWindow *ui;
    QVBoxLayout *basicLayout;

    QWidget *buttonWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *leftButton;
    QPushButton *rightButton;

    QLabel *infoLabel;
    QLabel *githubLabel;

    uint page = Page::start;

    void createLayout();
    void changeLayout(uint page);

private slots:
    void leftButtonHandle();
    void rightButtonHandle();

    void showToChartMessage();
    void hideToChartMessage();

    void sliderWidgetBorder();
    void lightWidgetBorder();

    void playlistOn();
    void playlistOff();
};

#endif // SMARTCONTROLMAINWINDOW_H
