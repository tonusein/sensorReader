#include "sensordata.h"
#include <boost/variant.hpp>
SensorData::SensorData()
{

}

SensorData::SensorData(int id, int dataType, uint64_t data)
{
    m_readTime = std::chrono::high_resolution_clock::now();
    m_id = id;
    m_dataType = dataType;
    m_data = data;

    if ((dataType > 0 && dataType <= 4) ||
            (dataType > 11 && dataType <=12))
    {
        m_dataReadType = DataReadType_Int64;
    }
    else if (dataType > 4 && dataType <= 8)
    {
        m_dataReadType = DataReadType_UInt64;
    }
    else if (dataType > 8 && dataType <= 10)
    {
         m_dataReadType = DataReadType_Double;
    }
}

int SensorData::getId()
{
    return m_id;
}

uint64_t SensorData::getValueUInt64()
{

    switch (m_dataType) {
    case DataReadType_UInt64:
        return  m_data;
    case DataReadType_Int64:
    {
        if (*reinterpret_cast<int64_t *>(&m_data) < 0)
        {
            return 0;
        }
        return m_data;
    }
    case DataReadType_Double:
    {
        return static_cast<uint64_t>(m_data);
    }
    }
    return 0;
}

int64_t SensorData::getValueInt64()
{
    switch (m_dataType) {
    case DataReadType_UInt64:
    case DataReadType_Int64:
        return *reinterpret_cast<int64_t *>(&m_data);
    case DataReadType_Double:
        return static_cast<int64_t>(m_data);
    }
    return 0;
}

double SensorData::getValueDouble()
{
    switch (m_dataType) {
    case DataReadType_UInt64:
        return static_cast<uint64_t>(m_data);
    case DataReadType_Int64:
        return static_cast<int64_t>(m_data);
    case DataReadType_Double:
        return  static_cast<double>(*reinterpret_cast<float*>(&m_data));
            }
    return 0;

}

std::chrono::system_clock::time_point SensorData::getReadTime()
{
    return m_readTime;
}
