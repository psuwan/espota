#include "NetworkManager.h"

#include <ETH.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>

const char* hostname = "espota";  // Will become espota.local
const char* ssid     = "ESP-OTA-AP";
const char* password = "espadmin";

// WT32-ETH01 Ethernet config
#ifndef ETH_PHY_ADDR
  #define ETH_PHY_ADDR 0
#endif

#ifndef ETH_CLK_MODE
  #define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#endif

#define ETH_TYPE        ETH_PHY_LAN8720
#define ETH_PHY_POWER   16
#define ETH_MDC_PIN     23
#define ETH_MDIO_PIN    18

bool eth_connected = false;

void setupNetwork() {
  Serial.println("Starting network...");

  // Start Ethernet
  WiFi.onEvent([](arduino_event_id_t event, arduino_event_info_t info) {
    switch (event) {
      case ARDUINO_EVENT_ETH_START:
        Serial.println("ETH Started");
        ETH.setHostname(hostname);
        break;
      case ARDUINO_EVENT_ETH_CONNECTED:
        Serial.println("ETH Connected");
        break;
      case ARDUINO_EVENT_ETH_GOT_IP:
        Serial.print("ETH IP: ");
        Serial.println(ETH.localIP());
        eth_connected = true;
        break;
      case ARDUINO_EVENT_ETH_DISCONNECTED:
        Serial.println("ETH Disconnected");
        eth_connected = false;
        break;
      default:
        break;
    }
  });

  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
  delay(100);  // let ETH hardware settle

  // Set static IP for Ethernet
  if (ETH.config(DEFAULT_STATIC_IP, DEFAULT_GATEWAY, DEFAULT_SUBNET, DEFAULT_DNS)) {
    Serial.println("✅ Static IP configured");
  } else {
    Serial.println("⚠️ Static IP config failed");
  }

  // Always start WiFi AP mode too (regardless of Ethernet)
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("WiFi AP started. IP: ");
  Serial.println(WiFi.softAPIP());

  // mDNS for both interfaces
  if (MDNS.begin(hostname)) {
    Serial.println("mDNS responder started: " + String(hostname) + ".local");
  } else {
    Serial.println("Error starting mDNS");
  }
}


String getLocalIP() {
  return eth_connected ? ETH.localIP().toString() : WiFi.softAPIP().toString();
}

String getHostname() {
  return String(hostname) + ".local";
}
