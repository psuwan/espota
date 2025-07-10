#include "WebServerManager.h"
#include "NetworkManager.h"

#if defined(ESP32)
  #include <WebServer.h>
#else
  #include <ESP8266WebServer.h>
#endif

WebServer server(80);  // Declare global web server instance

void handleRoot() {
  Serial.println("📡 Received request on /");  // <- THIS should print when browser hits IP
  String html = "<!DOCTYPE html><html><head><title>ESP OTA</title></head><body>";
  html += "<h1>ESP Web Server</h1>";
  html += "<p>IP Address: " + getLocalIP() + "</p>";
  html += "<p>WiFi AP IP: " + WiFi.softAPIP().toString() + "</p>";
  html += "<p>Hostname: " + getHostname() + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void startWebServer() {
  server.on("/", handleRoot);  // register handler
  server.begin();              // start web server
  Serial.println("🌐 Web server started at port 80");
}
WebServer& getServer() {
  return server;
}
