#ifndef WiFiSetup_h
#define WiFiSetup_h

#include <WiFiManager.h>

class WiFiSetup {

public:
  WiFiSetup(const char *apName, const char *apPassword);
  bool begin();
  void loop();

private:
  const char *_apName;
  const char *_apPassword;

  WiFiManager _wm;
};

#endif
