#ifndef SENSORREQUESTSERVER_H
#define SENSORREQUESTSERVER_H
#include <vector>
#include <memory>
#include "udpserver.h"
#include "sensors.h"

class SensorRequestServer
{
public:
    SensorRequestServer(int port, std::shared_ptr<Sensors> sensors);
    //start the server
    void start();
private:

    UdpServer m_udpServer;
    std::shared_ptr<Sensors> m_sensors;
    std::vector<char> handleUdpReceive(std::vector<char>);
};

#endif // SENSORREQUESTSERVER_H
