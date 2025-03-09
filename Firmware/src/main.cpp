

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266mDNS.h>

#include <UniversalTelegramBot.h>

#include "parameters.h"
#include "GPIOmap.h"
#include "rlogger.h"
#include "tempsensors.h"
#include "string.h"

// String chat_id2;

// Telemetry
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
/*
UniversalTelegramBot bot(BOT_TOKEN, secured_client);


RLogger rlog;



unsigned long Bot_lasttime;        //millis de el ultimo mensaje
unsigned long main_lasttime;       //millis de la ultima medicion
unsigned long rlogger_lasttime;    //millis de el ultimo envio a telemetria

// Sensors
tempSensors tSensors;

String curTempArray[DEVICECOUNT] = {"noData", "noData", "noData", "noData"};
String curStatusArray[DEVICECOUNT] = {"noData","noData","noData","noData"};

uint8_t currentDevice = 1;

*/

#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

class WebServer
{
public:
  WebServer() {}
  void begin()
  {
    if (!LittleFS.begin())
    {
      Serial.println("Failed to mount file system");
      return;
    }
    server.on("/", HTTP_GET, std::bind(&WebServer::handleRoot, this));
    server.on("/styles.css", HTTP_GET, std::bind(&WebServer::handleStyles, this));
    server.on("/ip", HTTP_GET, std::bind(&WebServer::handleIP, this));
    server.begin();
    webSocket.begin();
    webSocket.onEvent(std::bind(&WebServer::onWebSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
  }
  void loop()
  {
    server.handleClient();
    webSocket.loop();
  }

private:
  ESP8266WebServer server{80};
  WebSocketsServer webSocket{81};
  void handleRoot()
  {
    File file = LittleFS.open("/index.html", "r");
    if (!file)
    {
      Serial.println("Failed to open file");
      return;
    }
    server.streamFile(file, "text/html");
    file.close();
  }
  void handleStyles()
  {
    File file = LittleFS.open("/styles.css", "r");
    if (!file)
    {
      Serial.println("Failed to open file");
      return;
    }
    server.streamFile(file, "text/css");
    file.close();
  }
  void handleIP()
  {
    String ipAddress = WiFi.localIP().toString();
    server.send(200, "text/plain", ipAddress);
  }

  void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
  {
    switch (type)
    {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
    {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      webSocket.sendTXT(num, "Connected");
      break;
    }
    case WStype_TEXT:
      Serial.printf("[%u] Received text: %s\n", num, payload);
      webSocket.broadcastTXT(payload, length);
      break;
    }
  }
};

WebServer webServer;

void setup()
{
  Serial.begin(115200);
  // Establecer el modo WiFi y desconectarse de un AP si fue Anteriormente conectada
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("incufish"))
  {
    Serial.println("Error configurando mDNS");
  }

  MDNS.addService("http","tcp",80);

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  webServer.begin();
}

void loop()
{
  MDNS.update();
  webServer.loop();
}

/*

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    chat_id2 = chat_id;
    Serial.print("New Message from chat_id: ");
    Serial.println(chat_id2);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Pa";

    if (text == "/start") {
      String welcome = "Bienvenido al BOT de IncuFish, " + from_name + ".\n";
      bot.sendMessage(chat_id, welcome);
      String keyboardJson = "[[\"/getTemps\"], [\"/getStates\"]]";
      bot.sendMessageWithReplyKeyboard(chat_id, "Las opciones estan en el teclado", "", keyboardJson, true);
    }

    if (text == "/getTemps") {
      String temp = "";
      for(int i = 0; i < DEVICECOUNT; i++)
      temp = temp + devicesID[i] + ": " + String(curTempArray[i]) + " | ";
      bot.sendMessage(chat_id, temp);
    }

    if (text == "/getStates") {
      String temp = "";
      for(int i = 0; i < DEVICECOUNT; i++)
      temp = temp + devicesID[i] + ": " + curStatusArray[i] + " | ";
      bot.sendMessage(chat_id, temp);
    }

    if (text == "/getChatID") {
      bot.sendMessage(chat_id, String(chat_id));
    }
  }
}

void setup()
{

  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  // Establecer el modo WiFi y desconectarse de un AP si fue Anteriormente conectada
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  // initialize components
  GPIO_init();
  //rlog.init();
  tSensors.init();
  for (int i = 0; i<chatIDsCount; i++)
  {
    #ifdef INITMESSAGE
      bot.sendMessage(chatIDs[i], INITMESSAGE);
    #endif
    delay(10);
  }
}

void loop()
{
  // Telegram Bot response logic
  if (millis() > Bot_lasttime + Bot_mtbs)
  {
    Bot_lasttime = millis();
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("Telegram bot got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
  }

// Main logic to manage relays based on current temperature
  if (millis() > main_lasttime + main_mtbs)
  {
    main_lasttime = millis();

    float sensorValue = tSensors.readSensor(currentDevice);
    float setTemp = setTempArray[currentDevice - 1];
    if(sensorValue == -100)
    {
      curTempArray[currentDevice -1] = "ERROR";
      curStatusArray[currentDevice -1] = "ERROR";
      for (int i = 0; i<chatIDsCount; i++)
      {
        #ifdef SENSORERRORMESSAGE
          String message = String(SENSORERRORMESSAGE) + devicesID[currentDevice -1];
          bot.sendMessage(chatIDs[i], message);
        #endif
        delay(10);
      }
    }
    else
    {
    String status = activateRelay(currentDevice, setTemp, sensorValue, HYSTERESIS);
    curStatusArray[currentDevice -1] = status;
    curTempArray[currentDevice -1] = String(sensorValue, 2);
    }

// Telemetry to Google Sheets
  if (millis() > rlogger_lasttime + rlogger_mtbs)
  {
    rlogger_lasttime = millis();
    float setTemp = setTempArray[currentDevice - 1];
    String setTemp_str = String(setTemp,2);
    rlog.sendTemp(devicesID[currentDevice - 1], setTemp_str, curTempArray[currentDevice -1], curStatusArray[currentDevice -1]);
  }

    currentDevice++;
    if (currentDevice > DEVICECOUNT)
    {
      currentDevice = 1;
    }
  }
}

*/