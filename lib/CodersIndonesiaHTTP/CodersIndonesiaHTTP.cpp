#include "CodersIndonesiaHTTP.h"

CodersIndonesiaHTTP::CodersIndonesiaHTTP(){}

void CodersIndonesiaHTTP::begin() {
  Serial.begin(9600);
  Serial.println("Starting...");
}

void CodersIndonesiaHTTP::setWiFiClient(WiFiClient& client) {
  _client = &client;
}

void CodersIndonesiaHTTP::setServerName(String serverName)
{
  _serverName = serverName;
}

void CodersIndonesiaHTTP::setServerUpdatePath(const char *updateAddr)
{
  _serverUpdatePath = updateAddr;
}

void CodersIndonesiaHTTP::setServerSavePath(const char *saveAddr)
{
  _serverSavePath = saveAddr;
}

void CodersIndonesiaHTTP::setServerDeletePath(const char *deleteAddr)
{
  _serverDeletePath = deleteAddr;
}

/**
 * Get WiFi Connect status
 * */
bool CodersIndonesiaHTTP::isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

/**
 * Set WiFi Connect 
 * */
void CodersIndonesiaHTTP::setWiFiCredentials(const char *ssid, const char *pass)
{
  Serial.println("[WiFi]: Connecting to ssid");
  WiFi.begin(ssid, pass);
  while (!isConnected())
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("[WiFi]: Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

/**
 * Send GET Request to server
 * 
 * */
String CodersIndonesiaHTTP::sendHTTPGetRequest(String serverName)
{
  HTTPClient http;
  http.begin(*_client, serverName);

  String payload;
  int response = http.GET();

  if (response == HTTP_CODE_OK)
  {
    payload = http.getString();
  }
  else
  {
    _errorCode = response;
  }

  http.end();
  return payload;
}

/**
 * Send PUT Request to server
 * 
 * */
String CodersIndonesiaHTTP::sendHTTPPutRequest(String serverName, String data)
{
  HTTPClient http;
  http.begin(*_client, serverName);

  String payload;
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response = http.PUT(data);

  if (response == HTTP_CODE_OK)
  {
    payload = http.getString();
  }
  else
  {
    _errorCode = response;
  }

  http.end();
  return payload;
}

/**
 * Send POST Request to server
 * 
 * */
String CodersIndonesiaHTTP::sendHTTPPostRequest(String serverName, String data)
{
  HTTPClient http;
  WiFiClient clients;
  if(http.begin(clients, "http://127.0.0.1/api/data/save")) {
    Serial.printf("[Data]: Sending (%s) to (%s) \n", data.c_str(), "http://127.0.0.1/api/data/save");
    String payload;
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int response = http.POST(data);

    if (response == HTTP_CODE_OK)
    {
      payload = http.getString();
    }
    else
    {
      Serial.printf("[Error]: HTTP Request Status %d \n", response);
      _errorCode = response;
    }

    http.end();
    return payload;
  }

  Serial.printf("[Error]: HTTP NULL \n");
  return  "NULL";
}
