#ifndef CodersIndonesiaHTTP_h
#define CodersIndonesiaHTTP_h

#include "Arduino.h"

#if defined(ESP8266)

#ifdef ESP8266
  #include <core_version.h>
#endif

#ifdef ESP8266
  extern "C" {
      #include "user_interface.h"
    }
  #include "ESP8266WiFi.h"
  #include "ESP8266HTTPClient.h"
  #include "WiFiClient.h"
#endif

#include "DHT.h"


class CodersIndonesiaHTTP {

  public:
    CodersIndonesiaHTTP();
    void begin();

    void setServerName(String serverName);
    void setServerUpdatePath(const char* updateAddr);
    void setServerSavePath(const char* saveAddr);
    void setServerDeletePath(const char* deleteAddr);
    void setWiFiCredentials(const char *ssid, const char *pass);
    void setWiFiClient(WiFiClient& client);

    bool isConnected();

    String sendHTTPGetRequest(String serverName);
    String sendHTTPPostRequest(String serverName, String data);
    String sendHTTPPutRequest(String serverName, String data);

  private:
    String _serverName;
    const char* _serverUpdatePath;
    const char* _serverSavePath;
    const char* _serverDeletePath;
    int _errorCode;
    WiFiClient* _client;
};

#endif

#endif