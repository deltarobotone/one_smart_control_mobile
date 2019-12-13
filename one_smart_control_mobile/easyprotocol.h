#ifndef EASYPROTOCOL
#define EASYPROTOCOL

#include <QDateTime>
#include <QObject>
#include <QQueue>
#include <QIODevice>
#include <QThread>
#include <QTimer>
#include <iostream>
#include <cmath>
#include "bluetooth/device.h"

namespace Protocol
{
const std::string gripperopen = "GRIPPEROPEN";
const std::string gripperclose = "GRIPPERCLOSE";
const std::string lighton = "LIGHTON";
const std::string lightoff = "LIGHTOFF";
const std::string lightred = "RED";
const std::string lightgreen = "GREEN";
const std::string lightblue = "BLUE";
const std::string lightyellow = "YELLOW";
const std::string lightmagenta = "MAGENTA";
const std::string lightcyan = "CYAN";
const std::string lightwhite = "WHITE";
const std::string extmotoron = "EXTMOTORON";
const std::string extmotoroff = "EXTMOTOROFF";
};

namespace Colour
{
const std::string red = Protocol::lightred;
const std::string green = Protocol::lightgreen;
const std::string blue = Protocol::lightblue;
const std::string yellow = Protocol::lightyellow;
const std::string magenta = Protocol::lightmagenta;
const std::string cyan = Protocol::lightcyan;
const std::string white = Protocol::lightwhite;
};

namespace ID
{
const std::string move = "M";
const std::string light = "L";
const std::string gripper = "G";
const std::string extMmotor = "E";
const std::string waitFor = "T";
};


class Pos
{
public:
    Pos();
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
};

class Utils
{
public:
    Utils();
    std::string valueToString(float value);
    std::string posToString(Pos position);
    void fillData(std::string &txString, int length=22);
};

class BluetoothLowEnergyDevice: public QObject
{
    Q_OBJECT
private:
    bool connected = false;
    bool block = false;
    bool init = false;
    int scanStatusValue = 0;
    int handshakes = 0;
    std::string rxstr = "";
    std::string check = "";
    std::string receivedData = "";

    QQueue<std::string> queueTXData;

    const QString UARTUUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
    const QString RXUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";
    const QString TXUUID = "0000ffe1-0000-1000-8000-00805f9b34fb";

    void waitFor(int milliseconds);
    void send();

    QLowEnergyService *bleService;
    QLowEnergyDescriptor m_notificationDescTx;

    QList<QObject *> devices;
    QList<QObject *> services;
    QList<QObject *> characteristics;

    QList<QString> deviceList;
    QList<QLowEnergyService*> serviceList;
    QList<QLowEnergyCharacteristic> characteristicList;

    QList<QString> uuidList;
    QList<QString> deviceAdressList;

    bool serviceUART = false;
    bool characteristicRX = false;
    bool characteristicTX = false;


public:
    explicit BluetoothLowEnergyDevice(QObject *parent = nullptr);

    Device bleDevice;

    QList<QString> getDeviceList();
    QList<QLowEnergyService*> getServiceList();
    QList<QLowEnergyCharacteristic> getCharacteristicList();

    void connectDevice(int deviceIndex);
    void disconnectDevice();
    void startDeviceDiscovery();

    void enableNotification();

    void write(std::string txString);

    std::string read();

    void stopTransmission();

    bool isConnected();

signals:
    void newDevices();
    void newServices();
    void newCharacteristics();
    void scanFinished();
    void scanStarted();

    void connectingDevice();
    void deviceConnected(char id);
    void deviceDisconnected();

    void freeChannel();
    void dataTransmitted();
    void dataReceived();
    void nextCommand();

    void handshakeFailed();
    void updateScanValue(int value);

public slots:
    void handshake();

    void devicesUpdated();
    void servicesUpdated();
    void characteristicsUpdated();
    void stateChanged();
    void disconnected();

    void receive(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void transmit(std::string txString);
    void disableBlocking();
};


class Basic
{
protected:
    char robotid ='1';
    char deviceid = '1';
    BluetoothLowEnergyDevice &ble;
    Utils utils;
public:
    Basic(BluetoothLowEnergyDevice &connection);
    void setID(char robotid = '1', char deviceid = '1');
};

class Move:public Basic
{
public:
    Move(BluetoothLowEnergyDevice &connection);
    void ptp(float positionX, float positionY, float positionZ, float speed = 50.0);
    void ptp(Pos position, float speed = 50.0);
};

class Gripper:public Basic
{
public:
    Gripper(BluetoothLowEnergyDevice &connection);
    void open();
    void close();
};

class Light:public Basic
{
public:
    Light(BluetoothLowEnergyDevice &connection);

    void on(float intensity = 100.0);
    void off();
    void setColour(std::string colour, float intensity = 100.0);
    void setIntensity(float intensity = 100.0);
};

class ExtMotor:public Basic
{
public:
    ExtMotor(BluetoothLowEnergyDevice &connection);
    void start(float speed = 255.0);
    void stop();
    void setSpeed(float speed);
};

class Functions :public Basic
{
public:
    Functions(BluetoothLowEnergyDevice &connection);
    void waitFor(unsigned long milliseconds);
};

class EasyProtocol
{
private:
    char robotid = '1';
    std::string module = "HM-10";

public:
    EasyProtocol();
    ~EasyProtocol();

    BluetoothLowEnergyDevice connection;
    Functions functions;
    Move move;
    Gripper gripper;
    Light light;
    ExtMotor extmotor;

    std::string getModule();
    char getRobotID();
};

#endif
