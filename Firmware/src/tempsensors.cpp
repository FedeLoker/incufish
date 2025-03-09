#include "tempsensors.h"

tempSensors::tempSensors()
{
    sensorWire1.begin(TEMP_1);
    sensorWire2.begin(TEMP_2);
    sensorWire3.begin(TEMP_3);
    sensorWire4.begin(TEMP_4);

    tempSensor1.setOneWire(&sensorWire1);
    tempSensor2.setOneWire(&sensorWire2);
    tempSensor3.setOneWire(&sensorWire3);
    tempSensor4.setOneWire(&sensorWire4);
}

void tempSensors::init(void)
{
    tempSensor1.begin();
    tempSensor2.begin();
    tempSensor3.begin();
    tempSensor4.begin();
}

float tempSensors::readSensor(short sensor)
{
    float sensor_value = 100;
    if (sensor == 1)
    {
        tempSensor1.requestTemperatures();
        sensor_value = tempSensor1.getTempCByIndex(0);
    }
    else if (sensor == 2)
    {
        tempSensor2.requestTemperatures();
        sensor_value = tempSensor2.getTempCByIndex(0);
    }
    else if (sensor == 3)
    {
        tempSensor3.requestTemperatures();
        sensor_value = tempSensor3.getTempCByIndex(0);
    }
    else if (sensor == 4)
    {
        tempSensor4.requestTemperatures();
        sensor_value = tempSensor4.getTempCByIndex(0);
    }
    return sensor_value;
}

float tempSensors::readAVG(void)
{
    float sensor_value = (readSensor(1) + readSensor(2) + readSensor(3) + readSensor(4)) / 4;
    return sensor_value;
}