#ifndef SENSOR_H
#define SENSOR_H
#include <vector>
#include <cstdint>
#include <chrono>

class SensorData
{
public:
    enum DataReadType
    {
        DataReadType_UInt64,
        DataReadType_Int64,
        DataReadType_Double,
        DataType_Unknown
    };

    SensorData();
    SensorData(int id, int type, uint64_t data);

    int getId();
    DataReadType getDataReadType();
    uint64_t getValueUInt64();
    int64_t getValueInt64();
    double getValueDouble();
    std::chrono::high_resolution_clock::time_point  getReadTime();
private:
    void convertRawData(std::vector<char> data);
    std::chrono::high_resolution_clock::time_point m_readTime;
    int m_id = -1;
    int m_dataType = 0;
    DataReadType m_dataReadType;
    uint64_t m_data = 0;
};

#endif // SENSOR_H
