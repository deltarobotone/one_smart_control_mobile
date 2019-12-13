#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "config.h"
#include "easyprotocol.h"
#include "smartcontroldata.h"

namespace OneSmartControl
{

class TimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TimeWidget(OneSmartControl::SmartControlData &smartControlData, uint &screenSize, QWidget *parent = nullptr);

private:
    uint screenSize;
    OneSmartControl::SmartControlData &controlData;

    QGridLayout *basicLayout;

    QLabel *tLabel;
    QSlider *tSlider;

    QPushButton *toChartButton;

    float time = 0.0F;

    void createLayout();

signals:
    void dataChanged();
    void toChart();

private slots:
    void tSliderValueChanged(int value);
    void toChartButtonHandle();
};

} // OneSmartControl


#endif // TIMEWIDGET_H
