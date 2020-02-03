#include "sensorrequestserver.h"
#include "sensordataconverter.h"


using namespace std;


SensorRequestServer::SensorRequestServer(int port, shared_ptr<Sensors> sensors):
    m_udpServer(port, 10)
{
    m_sensors = sensors;
}

void SensorRequestServer::start()
{
    m_udpServer.startaWithReply(bind(&SensorRequestServer::handleUdpReceive, this, placeholders::_1));
}

std::vector<char> SensorRequestServer::handleUdpReceive(std::vector<char> rawData)
{

    int sensorNr = static_cast<int>(rawData[0]);
    int valueKind = static_cast<int>(rawData[1]);
    Sensor::SensorValue sensorValue;
    switch (valueKind) {
    //last value
    case 0:
        sensorValue = m_sensors.get()->getLastSensorValue(sensorNr);
        break;
    //mean of last 10 values
    case 1:
        sensorValue = m_sensors.get()->getLast10AvgSensorValue(sensorNr);
        break;
    //mean of all values
    case 2:
        sensorValue = m_sensors.get()->getAvgSensorValue(sensorNr);
        break;
    default:
        return std::vector<char>();
    }

    int dataType = m_sensors.get()->getInitType(sensorNr);

    auto tempVal = SensorDataConverter::sensorValue2RawData(dataType, sensorValue);

    std::vector<char> sendData ( sizeof(uint64_t) + 2);
    sendData[0] = static_cast<char>(sensorNr);
    sendData[1] = static_cast<char>(dataType);
    memcpy(&sendData.data()[2], reinterpret_cast<char*>(&tempVal), sizeof(uint64_t));

    return sendData;
}
