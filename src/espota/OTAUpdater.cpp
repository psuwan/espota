#include "OTAUpdater.h"
#include <ArduinoOTA.h>

void setupOTA() {
  ArduinoOTA
    .onStart([]() {
      Serial.println("Start updating...");
    })
    .onEnd([]() {
      Serial.println("\nUpdate complete.");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress * 100) / total);
    })
    .onError([](ota_error_t error) {
      Serial.printf("OTA Error[%u]: ", error);
    });

  ArduinoOTA.begin();
  Serial.println("OTA Ready. Use Arduino IDE to upload.");
}

void handleOTA() {
  ArduinoOTA.handle();
}
