#include "sensor.h"


using namespace std;
using namespace boost;


// this will sum SensorValues
struct Add : public static_visitor<Sensor::SensorValue> {
    template <typename T, typename U>
    auto operator() (T a, U b) const -> decltype(a+b) { return a + b; }
};

// this will divide SensorValues
struct Div : public static_visitor<Sensor::SensorValue> {
    template <typename T, typename U>
    auto operator() (T a, U b) const -> decltype(a/b) { return a / b; }
};

static Sensor::SensorValue calAvg(vector<Sensor::SensorValue> values);

Sensor::Sensor(int id, int type)
{
    m_id = id;
    m_iniType = type;
}

void Sensor::addData(Sensor::SensorValue data)
{
    m_data.push_back(data);
}

int Sensor::getInitType()
{
    return m_iniType;
}

int Sensor::getId()
{
    return m_id;
}

Sensor::SensorValue Sensor::getLast10AvgSensorValue()
{
    vector<SensorValue> last10Values;

    if (m_data.empty())
    {
        return SensorValue();
    }

    if (m_data.size() < 10)
    {
        last10Values = m_data;
    }
    else
    {
        last10Values.insert(last10Values.begin(), m_data.end() -10, m_data.end());
    }
    return calAvg(last10Values);
}

Sensor::SensorValue Sensor::getAvgSensorValue()
{
    if (m_data.empty())
    {
        return SensorValue();
    }


    return calAvg(m_data);
}

Sensor::SensorValue Sensor::getLastSensorValue()
{
    if (m_data.empty())
    {
        return SensorValue();
    }
    return m_data.back();
}

Sensor::SensorValue calAvg(vector<Sensor::SensorValue> values)
{
    Sensor::SensorValue sum;

    for (size_t i = 0 ; i < values.size(); i++)
    {
        sum = boost::apply_visitor(Add(), sum, values[i]);
    }
    Sensor::SensorValue div = values.size();

    return  boost::apply_visitor(Div(), sum, div);
}

template<typename T>
T Sensor::convertSensorValue(Sensor::SensorValue sensorValue)
{
    return get<T>(sensorValue);
}
