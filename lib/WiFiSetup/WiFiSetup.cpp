#include "WiFiSetup.h"

WiFiSetup::WiFiSetup(const char *apName, const char *apPassword) : _apName(apName), _apPassword(apPassword) {}

bool WiFiSetup::begin() {
  _wm.setConfigPortalTimeout(180);  // Set a timeout for the configuration portal (in seconds)

  bool res;

  res = _wm.autoConnect(_apName, _apPassword);  // Attempt to connect to WiFi or start the configuration portal

  if (!res) {
    Serial.println("Failed to connect");
  } else {
    Serial.println("connected...yeey :)");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }

  return res;
}

void WiFiSetup::loop() {
  static unsigned long lastCheckTime = 0;

  if (WiFi.status() != WL_CONNECTED && millis() - lastCheckTime > 5000) {
    lastCheckTime = millis();

    Serial.println("WiFi lost connection. Reconnecting...");
    WiFi.reconnect();
  }
}
