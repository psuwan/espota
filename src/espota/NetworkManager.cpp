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

  // Event handling for ESP32 core 2.x+
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
      case ARDUINO_EVENT_ETH_STOP:
        Serial.println("ETH Stopped");
        eth_connected = false;
        break;
      default:
        break;
    }
  });

  // Try Ethernet
  ETH.begin(
    ETH_PHY_ADDR,
    ETH_PHY_POWER,
    ETH_MDC_PIN,
    ETH_MDIO_PIN,
    ETH_TYPE,
    ETH_CLK_MODE
  );

  delay(100);
  
  // Static IP setup (default for non-DHCP network)
  if (!ETH.config(DEFAULT_STATIC_IP, DEFAULT_GATEWAY, DEFAULT_SUBNET, DEFAULT_DNS)) {
    Serial.println("⚠️  Failed to set static IP config");
  } else {
    Serial.println("✅ Static IP configured:");
    Serial.print("IP: "); Serial.println(DEFAULT_STATIC_IP);
    Serial.print("Gateway: "); Serial.println(DEFAULT_GATEWAY);
    Serial.print("Subnet: "); Serial.println(DEFAULT_SUBNET);
  }

  // Wait briefly for Ethernet connection
  unsigned long start = millis();
  while (!eth_connected && millis() - start < 3000) {
    delay(100);
    Serial.print(".");
  }

  // Fallback to WiFi AP if Ethernet is not connected
  if (!eth_connected) {
    Serial.println("\nEthernet not connected, starting WiFi AP...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.print("WiFi AP IP: ");
    Serial.println(WiFi.softAPIP());
  }

  // mDNS setup (works for both Ethernet and WiFi)
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
