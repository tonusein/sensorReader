#include "sensordataconverter.h"
#include <boost/variant.hpp>
#include <cstdint>

using namespace boost;
using namespace std;

union DatatypeConvert
{
    int8_t Int8;
    int16_t Int16;
    int32_t Int32;
    int64_t Int64;
    uint8_t UInt8;
    uint16_t UInt16;
    uint32_t UInt32;
    uint64_t UInt64;
    float Float;
    double Double;
};


Sensor::SensorValue SensorDataConverter::rawData2SensorValue(int dataType, uint64_t data)
{
    // unsigned types can be direcly done
    // bytes are same
    if ((dataType > 4 && dataType < 9) ||
            dataType == 12 || dataType == 13)
    {
        return Sensor::SensorValue(data);
    }

    DatatypeConvert tempType;
    tempType.UInt64 = data;

    switch (dataType) {
    case 1:
        return Sensor::SensorValue(static_cast<int64_t>(tempType.Int8));
    case 2:
        return Sensor::SensorValue(static_cast<int64_t>(tempType.Int16));
    case 3:
        return Sensor::SensorValue(static_cast<int64_t>(tempType.Int32));
    case 4:
        return Sensor::SensorValue(tempType.Int64);
        //5-8 done at the start
    case 9:
    {
        double valDouble = static_cast<double>(tempType.Float);
        return Sensor::SensorValue(valDouble);
    }
    case 10:
        return Sensor::SensorValue(tempType.Double);
    }
    return Sensor::SensorValue();
}

uint64_t SensorDataConverter::sensorValue2RawData(int dataType,
                                                  Sensor::SensorValue sensorValue)
{
    DatatypeConvert tempType;
    switch (dataType) {
    case 1:
        tempType.Int8 = static_cast<int8_t> (get<int64_t>(sensorValue));
        break;
    case 2:
        tempType.Int16 = static_cast<int16_t> (get<int64_t>(sensorValue));
        break;
    case 3:
        tempType.Int32 = static_cast<int32_t> (get<int64_t>(sensorValue));
        break;
    case 4:
        tempType.Int64 = get<int64_t>(sensorValue);
        break;
    case 5:
    case 12:
    case 13:
        tempType.UInt8 = static_cast<uint8_t> (get<uint64_t>(sensorValue));
        break;
    case 6:
        tempType.UInt16 = static_cast<uint16_t> (get<uint64_t>(sensorValue));
        break;
    case 7:
        tempType.UInt32 = static_cast<uint32_t> (get<uint64_t>(sensorValue));
        break;
    case 8:
        tempType.UInt64 = get<uint64_t>(sensorValue);
        break;
    case 9:
        tempType.Float = static_cast<float>(get<double>(sensorValue));
        break;
    case 10:
        tempType.Double = get<uint64_t>(sensorValue);
        break;

    default:
        break;
    }
    return tempType.UInt64;
}
