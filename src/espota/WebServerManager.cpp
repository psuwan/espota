#include "WebServerManager.h"
#include "NetworkManager.h"

#if defined(ESP32)
  #include <WebServer.h>
#else
  #include <ESP8266WebServer.h>
#endif

WebServer server(80);  // Create web server on port 80

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP OTA</title></head><body>";
  html += "<h1>ESP OTA Web Server</h1>";
  html += "<p>IP Address: " + getLocalIP() + "</p>";
  html += "<p>Hostname: " + getHostname() + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void startWebServer() {
  server.on("/", handleRoot);
  server.begin();
  Serial.println("🌐 Web server started. Open http://" + getLocalIP());
}
