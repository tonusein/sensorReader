#include <iostream>
#include <chrono>
#include <cstdint>

#include "sensorreadserver.h"
#include "sensorrequestserver.h"
#include "logsensors.h"
#include "sensors.h"

using namespace std;

static string logFileLocation = "sensorLog.csv";
static LogSensors logSensors(logFileLocation);
static void sensorRead(int id, int type , Sensor::SensorValue value);
static Sensors sensors;

int main( int argc, const char* argv[] )
{
    SensorReadServer sensorServer(12345);
    sensorServer.start(sensorRead);
    SensorRequestServer sensorRequestServer(12346,shared_ptr<Sensors>(&sensors) );
    sensorRequestServer.start();

    while (1)
    {
        this_thread::sleep_for(chrono::seconds(1));
        auto sensorsId = sensors.getSensorsId();
        sort(sensorsId.begin(), sensorsId.end());
        for (auto itm : sensorsId)
        {
            cout << "Sensor Id: " << itm;
            cout << " Avg value: ";
            auto sensorAvgVal = sensors.getLast10AvgSensorValue(itm);

            switch (sensorAvgVal.which()) {
            case 0:
                cout << boost::get<int64_t>(sensorAvgVal);
                break;
            case 1:
                cout << boost::get<uint64_t>(sensorAvgVal);
                break;
            case 2:
                cout << boost::get<double>(sensorAvgVal);
                break;
            }
            cout << endl;

        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}

void sensorRead(int id, int type, Sensor::SensorValue value)
{
    logSensors.writeSensorValue(id,value);
    sensors.addData(id,type, value);
}

