#ifndef Parameters_h
#define Parameters_h

#include "string.h"

// WiFi
const char *ssid = "";
const char *password = "";

// Telegram BOT Token
#define BOT_TOKEN ""

String chatIDs[] = {""};
int chatIDsCount = 1;

#define DEVICECOUNT 4
String devicesID[DEVICECOUNT] = {"Incu01", "Incu02", "Incu03", "Incu04"};
float setTempArray[DEVICECOUNT] = {9.00, 12.00, 18.00, 24.00};

#define INITMESSAGE "HOLA! Me acabo de reniciar"

#define SENSORERRORMESSAGE "No responde el sensor correspondiente a "

#define TOLERANCEERRORMESSAGE "Diferencia de tempreratura excesiva en "

// sensors

#define HYSTERESIS 0.70

// looping times
unsigned long Bot_mtbs = 50;         // Tiempo medio entre el escaneo de mensajes [ms]
unsigned long main_mtbs = 20000;     // Tiempo medio entre mediciones [ms]
unsigned long rlogger_mtbs = 600000; // Tiempo medio entre reportes a telemetria [ms]

#endif