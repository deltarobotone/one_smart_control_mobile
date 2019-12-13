# include "easyprotocol.h"

BluetoothLowEnergyDevice::BluetoothLowEnergyDevice(QObject *parent):
    QObject(parent)
{
    connect(&bleDevice,SIGNAL(devicesUpdated()),this,SLOT(devicesUpdated()));
    connect(&bleDevice,SIGNAL(servicesUpdated()),this,SLOT(servicesUpdated()));
    connect(&bleDevice,SIGNAL(characteristicsUpdated()),this,SLOT(characteristicsUpdated()));
    connect(&bleDevice,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(&bleDevice,SIGNAL(stateChanged()),this,SLOT(stateChanged()));
}

void BluetoothLowEnergyDevice::startDeviceDiscovery()
{
    serviceUART = false;
    characteristicRX = false;
    characteristicTX = false;

    devices.clear();
    services.clear();
    characteristics.clear();
    characteristicList.clear();
    serviceList.clear();
    uuidList.clear();
    deviceAdressList.clear();
    deviceList.clear();

    bleDevice.startDeviceDiscovery();
};

void BluetoothLowEnergyDevice::connectDevice(int deviceIndex)
{
    std::string rxstr = "";
    std::string check = "";
    handshakes = 0;
    bleDevice.scanServices(deviceAdressList.at(deviceIndex));
}

void BluetoothLowEnergyDevice::disconnectDevice(void)
{
    bleService->writeDescriptor(m_notificationDescTx, QByteArray::fromHex("0000"));

    disconnect(bleService, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),this, SLOT(receive(QLowEnergyCharacteristic,QByteArray)));

    bleDevice.disconnectFromDevice();

    connected = false;
    disconnected();
}

QList<QString> BluetoothLowEnergyDevice::getDeviceList(){return deviceList;};
QList<QLowEnergyService*> BluetoothLowEnergyDevice::getServiceList(){return serviceList;};
QList<QLowEnergyCharacteristic> BluetoothLowEnergyDevice::getCharacteristicList(){return characteristicList;};

void BluetoothLowEnergyDevice::enableNotification()
{
    const QLowEnergyCharacteristic TxChar = bleService->characteristic(QBluetoothUuid(QUuid(TXUUID)));
    m_notificationDescTx = TxChar.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
    bleService->writeDescriptor(m_notificationDescTx, QByteArray::fromHex("0100"));
    connect(bleService, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),this, SLOT(receive(QLowEnergyCharacteristic,QByteArray)));
}

void BluetoothLowEnergyDevice::receive(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
    if (c.uuid()==QBluetoothUuid(QUuid(TXUUID)))
    {
        receivedData = std::string(value);

        if (!init)handshake();
        else
        {
            if (!queueTXData.isEmpty())send();
            else emit freeChannel();
        }
    }
}

void BluetoothLowEnergyDevice::send()
{
    if (!queueTXData.isEmpty())
    {
        if(block==false)
        {
            emit nextCommand();
            std::string txString = queueTXData.dequeue();
            if(txString != "T")
            {
                transmit(txString);
            }
            else
            {
                std::string time = queueTXData.dequeue();
                waitFor(std::stoi(time));
            }
        }
    }
}

void BluetoothLowEnergyDevice::transmit(std::string txString)
{
    QByteArray HighData,LowData;

    HighData.append(QString::fromStdString(txString));
    LowData.append(QString::fromStdString(txString));

    HighData.remove(11,21);
    LowData.remove(0,11);

    const QLowEnergyCharacteristic  RxChar = bleService->characteristic(QBluetoothUuid(QUuid(RXUUID)));
    bleService->writeCharacteristic(RxChar,HighData, QLowEnergyService::WriteWithoutResponse);
    bleService->writeCharacteristic(RxChar,LowData, QLowEnergyService::WriteWithoutResponse);
    emit dataTransmitted();
}

void BluetoothLowEnergyDevice::stopTransmission()
{
    queueTXData.clear();
}

void BluetoothLowEnergyDevice::write(std::string txString)
{
    queueTXData.enqueue(txString);
    return;
}

std::string BluetoothLowEnergyDevice::read()
{
    std::string data = receivedData;
    receivedData = "";
    return data;
}

void BluetoothLowEnergyDevice::waitFor(int milliseconds)
{
    block = true;
    QTimer::singleShot(milliseconds, this, SLOT(disableBlocking()));
}

void BluetoothLowEnergyDevice::disableBlocking()
{
    block = false;
    send();
}
bool BluetoothLowEnergyDevice::isConnected(){return connected;}

void BluetoothLowEnergyDevice::devicesUpdated()
{
    QVariant temp = bleDevice.getDevices();
    devices = temp.value<QList<QObject*>>();

    for (auto d: qAsConst(devices))
    {
        auto device = qobject_cast<DeviceInfo *>(d);
        deviceList.append(device->getName());
        deviceAdressList.append(device->getAddress());
    }
};
void BluetoothLowEnergyDevice::servicesUpdated()
{
    QVariant temp = bleDevice.getServices();
    services = temp.value<QList<QObject*>>();

    for (auto d: qAsConst(services))
    {
        auto service = qobject_cast<ServiceInfo *>(d);
        uuidList.append(service->getUuid());
        serviceList.append(service->service());
    }

    for (int i = 0; i < serviceList.size(); i++)
    {
        if(serviceList.at(i)->serviceUuid()== QBluetoothUuid(QUuid(UARTUUID)))serviceUART = true;
        bleService = serviceList.at(i);
    }

    if(serviceUART)
    {
        bleDevice.connectToService("0xffe0");
    }
};
void BluetoothLowEnergyDevice::characteristicsUpdated()
{
    QVariant temp = bleDevice.getCharacteristics();
    characteristics = temp.value<QList<QObject*>>();

    for (auto d: qAsConst(characteristics))
    {
        auto characteristic = qobject_cast<CharacteristicInfo *>(d);
        characteristicList.append(characteristic->getCharacteristic());
    }

    for (int i = 0; i < characteristicList.size(); i++)
    {
        if(characteristicList.at(i).uuid()== QBluetoothUuid(QUuid(RXUUID)))characteristicRX = true;
        if(characteristicList.at(i).uuid()== QBluetoothUuid(QUuid(TXUUID)))characteristicTX = true;
    }

    if(characteristicRX && characteristicTX)
    {
        emit connectingDevice();
        enableNotification();
    }
};

void BluetoothLowEnergyDevice::disconnected()
{
    serviceUART = false;
    characteristicRX = false;
    characteristicTX = false;

    devices.clear();
    services.clear();
    characteristics.clear();
    characteristicList.clear();
    serviceList.clear();
    uuidList.clear();
    deviceAdressList.clear();
    deviceList.clear();

    emit deviceDisconnected();
    init = false;
    connected = false;
};

void BluetoothLowEnergyDevice::stateChanged()
{
    if(bleDevice.state())
    {
        emit scanStarted();
    }
    else
    {
        emit scanFinished();
    }
}

void BluetoothLowEnergyDevice::handshake()
{
    rxstr = read();

    if (rxstr != "" && rxstr != check)
    {
        check = rxstr;
        rxstr = "";
    }
    else if (check != "" && rxstr == check)
    {
        char rxchar = *rxstr.c_str();
        emit deviceConnected(rxchar);
        init = true;
        connected = true;
    }

    if (handshakes > 2) emit handshakeFailed();
    handshakes++;
}

Utils::Utils()
{
}

std::string Utils::valueToString(float value)
{
    if (value > -1000.0F && value < 1000.0F)
    {
        double upvalue = double(value * 10.0F);
        int temp = int(trunc(upvalue));
        if (temp < 0) temp = temp * -1;
        std::string strint = std::to_string(temp);
        std::string strraw = "";
        std::string strsigned = "";

        if (value > -1.0F && value < 1.0F)
        {
            strraw = "000";
            strraw.append(strint);
        }
        else if (value > -10.0F && value < 10.0F)
        {
            strraw = "00";
            strraw.append(strint);
        }
        else if (value > -100.0F && value < 100.0F)
        {
            strraw = "0";
            strraw.append(strint);
        }
        else if (value > -1000.0F && value < 1000.0F)
        {
            strraw = strint;
        }
        else
        {
            return "0000";
        }

        if (value >= 0.0F)
        {
            strsigned = "+";
            strsigned.append(strraw);
        }
        else
        {
            strsigned = "-";
            strsigned.append(strraw);
        }
        return strsigned;
    }
    return "0000";
}

Pos::Pos()
{
}

std::string Utils::posToString(Pos position)
{
    std::string strX = valueToString(position.x);
    std::string strY = valueToString(position.y);
    std::string strZ = valueToString(position.z);
    return strX + strY + strZ;
}

void Utils::fillData(std::string &txString, int length)
{
    int i = 0;
    if (int(txString.length()) < length)
    {
        i = int(txString.length());
        while (i < length)
        {
            txString = txString + '#';
            i++;
        }
    }
}

Move::Move(BluetoothLowEnergyDevice &connection) : Basic(connection)
{
}

void Move::ptp(float positionX, float positionY, float positionZ, float speed)
{
    if (ble.isConnected())
    {
        Pos pos;
        pos.x = positionX;
        pos.y = positionY;
        pos.z = positionZ;
        std::string s = utils.posToString(pos);
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + "M" + s + v.erase(0, 1);
        utils.fillData(txString);
        ble.write(txString);
    }
    return;
}

void Move::ptp(Pos position, float speed)
{
    ptp(position.x,position.y,position.z,speed);
    return;
}

Gripper::Gripper(BluetoothLowEnergyDevice &connection) : Basic(connection)
{
}

void Gripper::open()
{
    if (ble.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::gripperopen;
        utils.fillData(txString);
        ble.write(txString);
    }
    return;
}

void Gripper::close()
{
    if (ble.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::gripperclose;
        utils.fillData(txString);
        ble.write(txString);
    }
    return;
}

Light::Light(BluetoothLowEnergyDevice &connection) : Basic(connection)
{
}

void Light::on(float intensity)
{
    if (ble.isConnected())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        ble.write(txString);
    }
    return;
}

void Light::off()
{
    if (ble.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lightoff;
        utils.fillData(txString);
        ble.write(txString);
    }
    return;
}

void Light::setColour(std::string colour, float intensity)
{
    if (ble.isConnected())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton + '#' + colour;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        ble.write(txString);
    }
    return;
}

void Light::setIntensity(float intensity)
{
    if (ble.isConnected())
    {
        std::string vi = utils.valueToString(intensity);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::lighton;
        utils.fillData(txString, 18);
        txString = txString + vi.erase(0, 1);
        ble.write(txString);
    }
    return;
}

ExtMotor::ExtMotor(BluetoothLowEnergyDevice &connection) : Basic(connection)
{
}

void ExtMotor::stop()
{
    if (ble.isConnected())
    {
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoroff;
        utils.fillData(txString);
        ble.write(txString);
    }
    return;
}

void ExtMotor::setSpeed(float speed)
{
    if (ble.isConnected())
    {
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoron;
        utils.fillData(txString, 18);
        txString = txString + v.erase(0, 1);
        ble.write(txString);
    }
    return;
}

void ExtMotor::start(float speed)
{
    if (ble.isConnected())
    {
        std::string v = utils.valueToString(speed);
        std::string txString;
        txString = txString + robotid + deviceid + Protocol::extmotoron;
        utils.fillData(txString, 18);
        txString = txString + v.erase(0, 1);
        ble.write(txString);
    }
    return;
}

Functions::Functions(BluetoothLowEnergyDevice &connection) : Basic(connection)
{
}

void Functions::waitFor(unsigned long milliseconds)
{
    if (ble.isConnected())
    {
        ble.write("T");
        ble.write(std::to_string(milliseconds));
    }
}

EasyProtocol::EasyProtocol() :
    functions(connection),
    move(connection),
    gripper(connection),
    light(connection),
    extmotor(connection)
{
}
EasyProtocol::~EasyProtocol()
{
    if (connection.isConnected())connection.disconnectDevice();
}

char EasyProtocol::getRobotID(){return robotid;};


Basic::Basic(BluetoothLowEnergyDevice &connection) :
    robotid('1'),
    deviceid('1'),
    ble(connection),
    utils()
{    
}

void Basic::setID(char robotid, char deviceid)
{
    this->robotid = robotid;
    this->deviceid = deviceid;
}
