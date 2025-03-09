#include "GPIOmap.h"

void GPIO_init()
{
    pinMode(RELAY_1, OUTPUT);
    digitalWrite(RELAY_1,HIGH);
    pinMode(RELAY_2, OUTPUT);
    digitalWrite(RELAY_2,HIGH);
    pinMode(RELAY_3, OUTPUT);
    digitalWrite(RELAY_3,HIGH);
    pinMode(RELAY_4, OUTPUT);
    digitalWrite(RELAY_4,HIGH);
}

String activateRelay(uint8_t deviceID, float setTemp, float currentTemp, float hysteresis)
{
    String status = "StandBy";
    bool heating = true;
    if (setTemp - hysteresis > currentTemp)
    {
        status = "Heating";
        heating = false;
    }

    if (deviceID == 1)
    {
        digitalWrite(RELAY_1, heating);
    }
    if (deviceID == 2)
    {
        digitalWrite(RELAY_2, heating);
    }
    if (deviceID == 3)
    {
        digitalWrite(RELAY_3, heating);
    }
    if (deviceID == 4)
    {
        digitalWrite(RELAY_4, heating);
    }

    return status;
}