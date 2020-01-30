#ifndef SENSORSERVER_H
#define SENSORSERVER_H
#include <vector>
#include "sensor.h"
#include "udpserver.h"

class SensorReadServer
{
public:
    SensorReadServer(int port);
    // start the server with sensor callBack function
    void start(std::function<void(int, int, Sensor::SensorValue data)> callback);
private:
    UdpServer m_udpServer;

    std::function<void(int, int, Sensor::SensorValue data)> m_callback;
    void handleUdpReceive(std::vector<char>);

};
#endif // SENSORSERVER_H
