#if defined(ESP32)
  #include <WiFi.h>
  #include <ArduinoOTA.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ArduinoOTA.h>
#endif

const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Optional: Set OTA hostname
#define OTA_HOSTNAME "ESP_OTA_Device"

void setup() {
  Serial.begin(115200);
  Serial.println("\nBooting...");

#if defined(ESP8266)
  WiFi.mode(WIFI_STA); // For ESP8266
#endif

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected: " + WiFi.localIP().toString());

  // Optional hostname setting
#if defined(ESP32)
  ArduinoOTA.setHostname(OTA_HOSTNAME);
#elif defined(ESP8266)
  ArduinoOTA.setHostname(OTA_HOSTNAME);
#endif

  // Optionally set OTA password
  // ArduinoOTA.setPassword("admin");

  ArduinoOTA.onStart([]() {
    Serial.println("Start updating...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nUpdate complete!");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress * 100) / total);
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
  Serial.println("OTA Ready!");
}

void loop() {
  ArduinoOTA.handle();

}