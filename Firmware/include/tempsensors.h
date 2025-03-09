#ifndef tempsensors_h
#define tempsensors_h

#include "GPIOmap.h"

#include <OneWire.h>
#include <DallasTemperature.h>

class tempSensors
{
private:
    OneWire sensorWire1;
    DallasTemperature tempSensor1;
    OneWire sensorWire2;
    DallasTemperature tempSensor2;
    OneWire sensorWire3;
    DallasTemperature tempSensor3;
    OneWire sensorWire4;
    DallasTemperature tempSensor4;
    OneWire sensorWire5;
    DallasTemperature tempSensor5;

public:
    tempSensors();
    void init(void);
    float readSensor(short sensor);
    float readAVG(void);
};

#endif