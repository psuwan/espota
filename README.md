# espota

Simplified Structure
- espota/
    - espota.ino        ← main logic
    - ├── WiFiManager.h
    - ├── WiFiManager.cpp
    - ├── OTAUpdater.h
    - └── OTAUpdater.cpp

EnhancementEnhancements
Network Management: Dual WiFi and Ethernet with reconnection logic and event logging.
Memory Management: EEPROM for persistent config and SPIFFS for logs, plus heap monitoring.
Parameter Handling: Dynamic updates via a web interface, saved to EEPROM.
Modularity: Clean separation of declarations (.h) and implementations (.cpp).
