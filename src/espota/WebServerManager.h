#ifndef WEBSERVER_MANAGER_H
#define WEBSERVER_MANAGER_H

#if defined(ESP32)
  #include <WebServer.h>
#else
  #include <ESP8266WebServer.h>
#endif

void startWebServer();
WebServer& getServer();  // Declare global access function

#endif
