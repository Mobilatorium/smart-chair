#ifndef FirebaseDatabasePT_h
#define FirebaseDatabasePT_h

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include "Config.h"
/*
in Config.h must be defined follow items:
#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"
*/

class FirebaseDatabasePT {
private:

public:
  FirebaseDatabasePT();
  void init();
  void setEnergy(uint8_t _energy);
  void standUp();
  void sitDown();

};

#endif
