#ifndef LOGSENSOR_H
#define LOGSENSOR_H
#include <iostream>
#include <fstream>
#include "sensor.h"

class LogSensors
{
public:
    LogSensors(std::string fileLocation);
    ~LogSensors();
    // write sensor values to log file
    void writeSensorValue(int id, Sensor::SensorValue value);
private:
    std::ofstream m_file;
};

#endif // LOGSENSOR_H
