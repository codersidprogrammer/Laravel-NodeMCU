#include "CodersIndonesiaHTTP.h"

WiFiClient client;
CodersIndonesiaHTTP httpLib;
DHT dht(D2, DHT11);

String sendHTTPPostRequest(String serverName, String data)
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
    }

    http.end();
    return payload;
  }

  Serial.printf("[Error]: HTTP NULL \n");
  return  "NULL";
}

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  httpLib.begin();
  httpLib.setWiFiClient(client);
  httpLib.setWiFiCredentials("Janganlupasholat", "bismillah");
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = dht.readTemperature(false);
  String server = "http://localhost:8000/api/data/save";
  String data = "sensor=" + (String) temperature;
  String result = sendHTTPPostRequest(server,data);
  Serial.println(result);
  delay(5000);
}