#include "NetworkManager.h"
#include "OTAUpdater.h"
#include "WebServerManager.h"

void setup() {
  Serial.begin(115200);
  setupNetwork();      // Ethernet + WiFi fallback
  setupOTA();          // OTA ready
  startWebServer();    // Start HTTP server

  Serial.println("Ready for OTA and Web Access at: " + getLocalIP());
  Serial.println("Hostname: " + getHostname());
}

void loop() {
  handleOTA();         // Keep OTA responsive
}
