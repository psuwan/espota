#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <Arduino.h>
#include <IPAddress.h>

// Default static IP config (for non-DHCP networks)
#define DEFAULT_STATIC_IP     IPAddress(192, 168, 1, 100)
#define DEFAULT_GATEWAY       IPAddress(192, 168, 1, 1)
#define DEFAULT_SUBNET        IPAddress(255, 255, 255, 0)
#define DEFAULT_DNS           IPAddress(8, 8, 8, 8)

void setupNetwork();
String getLocalIP();
String getHostname();

#endif
