#ifndef FirebaseDatabaseSC_h
#define FirebaseDatabaseSC_h

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include "NtpClient.h"
#include "Config.h"
/*
in Config.h must be defined follow items:
#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"
*/

class FirebaseDatabaseSC {
public:

  FirebaseDatabaseSC();

  void init();
  //save energy to Firebase
  void setEnergy(uint8_t energy);

  //save fact of stand up to Firebase
  void standUp();

  //save fact of sit down to Firebase
  void sitDown();

  //get Sitting Duration from Firebase
  uint8_t getFbSittingDurationInSec();

  //get Restore Duration from Firebase
  uint8_t getFbRestoreDurationInSec();

private:
  uint32_t _unixTimeInSec;
  uint32_t _initTimeInSec;

};

#endif
