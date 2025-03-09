#ifndef rlogger_h
#define rlogger_h

#include "GPIOmap.h"
#include "HTTPSRedirect.h"
#include "string.h"

class RLogger
{
private:
    const char *host = "script.google.com";
    const int httpsPort = 443;
    const char *fingerprint = "";
    String url = String("/macros/s/") + GScriptId + "/exec";
    // Enter Google Script Deployment ID:
    const char *GScriptId = "";
    HTTPSRedirect *client = nullptr;

public:
    RLogger();
    bool init();
    bool sendTemp(String device_id, String set_temp, String current_temp, String mode);
};

#endif