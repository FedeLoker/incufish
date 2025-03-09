#include "rlogger.h"

RLogger::RLogger()
{
}

bool RLogger::init()
{
    bool output = 1;

    // Use HTTPSRedirect class to create a new TLS connection
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");

    Serial.print("Connecting to ");
    Serial.println(host);

    // Try to connect for a maximum of 5 times
    bool flag = false;
    for (int i = 0; i < 5; i++)
    {
        int retval = client->connect(host, httpsPort);
        if (retval == 1)
        {
            flag = true;
            Serial.println("Connected");
            break;
        }
        else
        {
            Serial.println("Connection failed. Retrying...");
            output = 0;
        }
    }
    if (!flag)
    {
        Serial.print("Could not connect to server: ");
        Serial.println(host);
        output = 0;
    }
    delete client;    // delete HTTPSRedirect object
    client = nullptr; // delete HTTPSRedirect object

    return output;
}

bool RLogger::sendTemp(String device_id, String set_temp, String current_temp, String status)
{

    bool output = 1;
    String payload_base = "{\"command\": \"insert_row\", \"sheet_name\": \"Hoja 1\", \"values\": ";
    String payload = "";
    String url = String("/macros/s/") + GScriptId + "/exec";

    static bool flag = false;
    if (!flag)
    {
        client = new HTTPSRedirect(httpsPort);
        client->setInsecure();
        flag = true;
        client->setPrintResponseBody(true);
        client->setContentTypeHeader("application/json");
    }
    if (client != nullptr)
    {
        if (!client->connected())
        {
            Serial.println("Conecting");
            client->connect(host, httpsPort);
        }
    }
    else
    {
        Serial.println("Error creating client object!");
        output = 0;
    }

    // Create json object string to send to Google Sheets
    payload = payload_base + "\"" + device_id + "," + set_temp + "," + current_temp + "," + status + "\"}";

    // Publish data to Google Sheets
    Serial.println("Publishing data...");
    Serial.println(payload);
    if (client->POST(url, host, payload))
    {
        output = 1;
        client->stop();
    }
    else
    {
        Serial.println("Error while connecting");
        output = 0;
    }

    return output;
}