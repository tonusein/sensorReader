#ifndef SENSORS_H
#define SENSORS_H
#include <vector>
#include <mutex>
#include "sensor.h"

class Sensors
{
public:
    Sensors();
    // add new data to sensor. If sensor does not exist create new one
    void addData(int sensorId, int initType, Sensor::SensorValue sensorValue);

    Sensor::SensorValue getLastSensorValue(int sensorId);
    Sensor::SensorValue getLast10AvgSensorValue(int sensorId);
    Sensor::SensorValue getAvgSensorValue(int sensorId);
    int getInitType(int sensorId);
    int getNrOfSensors();
    std::vector<int> getSensorsId();
    
private:
    std::vector<Sensor> m_sensors;
    Sensor *getSensor(int id);
    //functions are called on multiple threads. so we need mutex
    std::mutex m_mtx;
};

#endif // SENSORS_H
