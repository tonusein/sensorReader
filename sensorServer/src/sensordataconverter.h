#ifndef SENSORDATACONVERTER_H
#define SENSORDATACONVERTER_H
#include <vector>
#include <cstdint>
#include "sensor.h"

class SensorDataConverter
{
public:
    static Sensor::SensorValue rawData2SensorValue(int dataType, uint64_t data);
    static uint64_t sensorValue2RawData(int dataType, Sensor::SensorValue sensorValue);
};

#endif // SENSORDATACONVERTER_H
