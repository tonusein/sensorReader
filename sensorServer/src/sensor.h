#ifndef SENSOR_H
#define SENSOR_H
#include <cstdint>
#include <boost/variant.hpp>
#include <vector>
#include <thread>
#include <memory>

class Sensor
{
public:
    typedef boost::variant<int64_t, uint64_t, double> SensorValue;
    Sensor(int id, int type);

    template <typename T>
    static T convertSensorValue(SensorValue sensorValue);

    void addData(SensorValue data);
    int getInitType();
    int getId();
    SensorValue getLastSensorValue();
    SensorValue getLast10AvgSensorValue();
    SensorValue getAvgSensorValue();


private:
    int m_id;
    int m_iniType;
    std::vector<SensorValue> m_data;


};

#endif // SENSOR_H
