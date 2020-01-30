#include "sensorreadserver.h"
#include "sensordataconverter.h"

using namespace std;

SensorReadServer::SensorReadServer(int port):
    m_udpServer(port, 10)
{
}

void SensorReadServer::start(std::function<void (int, int,
                                                 Sensor::SensorValue)> callback)
{
    m_callback = callback;
    m_udpServer.start(bind(&SensorReadServer::handleUdpReceive, this, placeholders::_1));
}

void SensorReadServer::handleUdpReceive(std::vector<char> rawData)
{
    int sensorNr = static_cast<int>(rawData[0]);
    int valueType = static_cast<int>(rawData[1]);
    uint64_t data = *reinterpret_cast<uint64_t*>(&rawData[2]);

    Sensor::SensorValue val = SensorDataConverter::rawData2SensorValue(valueType, data);
    m_callback(sensorNr, valueType, val);
}

