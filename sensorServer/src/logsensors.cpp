#include "logsensors.h"
#include <iomanip>
#include <chrono>
#include <cstdint>

using namespace std;

//convet timestamp to string with format "YYYY-MM-DD HH:MM:SS."ms"
static string timePoint2String(chrono::system_clock::time_point point);

LogSensors::LogSensors(string fileLocation)
{
    m_file.open(fileLocation);
}

LogSensors::~LogSensors()
{
    m_file.close();
}

void LogSensors::writeSensorValue(int id, Sensor::SensorValue value)
{
    auto time = chrono::high_resolution_clock::now();
    m_file << timePoint2String(time) << ";";
    m_file << id << ";";
    // we need to know what type is the value
    switch (value.which()) {
    case 0:
        m_file << boost::get<int64_t>(value);
        break;
    case 1:
        m_file << boost::get<uint64_t>(value);
        break;
    case 2:
        m_file << boost::get<double>(value);
        break;
    }
     m_file << endl;
}


string timePoint2String(chrono::system_clock::time_point point)
{
    time_t time = chrono::system_clock::to_time_t(point);
    tm timetm = *std::localtime(&time);
    stringstream ss;
    ss << put_time(&timetm, "%F %X");
    ss << ".";
    ss << chrono::duration_cast<chrono::milliseconds>(point.time_since_epoch()).count() % 1000;
    return ss.str();
}
