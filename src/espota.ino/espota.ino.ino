#include <WiFi.h>         // For ESP32
// #include <ESP8266WiFi.h>  // For ESP8266
#include <ArduinoOTA.h>   // OTA support

const char* ap_ssid = "ESP-OTA-AP";
const char* ap_password = "@dmin1234S";  // Must be at least 8 characters

void setup() {
  Serial.begin(115200);
  Serial.println("Booting in AP mode...");

  // Set up Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // OTA setup
  ArduinoOTA.setHostname("esp-ota-ap");

  ArduinoOTA.onStart([]() {
    Serial.println("Start updating...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nUpdate Complete");
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error[%u]: ", error);
  });

  ArduinoOTA.begin();
  Serial.println("OTA Ready (AP mode)");
}

void loop() {
  ArduinoOTA.handle();  // Required to process OTA events
}