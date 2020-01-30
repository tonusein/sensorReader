#include "sensors.h"
#include <thread>
using namespace std;

Sensors::Sensors()
{

}

void Sensors::addData(int sensorId, int initType, Sensor::SensorValue sensorValue)
{
    unique_lock<mutex> lck (m_mtx);
    //find the sensor and add data
    auto sensor = getSensor(sensorId);
    if (sensor != nullptr)
    {
        if (sensor->getInitType() != initType) return; //bad reading
        sensor->addData(sensorValue);
        return;
    }

    //sensor is not found so create new one
    Sensor newSensor (sensorId,initType);
    newSensor.addData(sensorValue);
    m_sensors.push_back(newSensor);
}

Sensor::SensorValue Sensors::getLastSensorValue(int sensorId)
{
    unique_lock<mutex> lck (m_mtx);
    return getSensor(sensorId)->getLastSensorValue();
}

Sensor::SensorValue Sensors::getLast10AvgSensorValue(int sensorId)
{
    unique_lock<mutex> lck (m_mtx);
    return getSensor(sensorId)->getLast10AvgSensorValue();
}

Sensor::SensorValue Sensors::getAvgSensorValue(int sensorId)
{
    unique_lock<mutex> lck (m_mtx);
    return getSensor(sensorId)->getAvgSensorValue();
}

int Sensors::getInitType(int sensorId)
{
    return getSensor(sensorId)->getInitType();
}

int Sensors::getNrOfSensors()
{
    return m_sensors.size();
}

vector<int> Sensors::getSensorsId()
{
    vector<int> out;

    for (auto &itm : m_sensors )
    {
        out.push_back(itm.getId());
    }
    return out;
}

Sensor *Sensors::getSensor(int id)
{
    for (auto &itm : m_sensors)
    {
        if (itm.getId() == id) return &itm;
    }
    return nullptr;
}
