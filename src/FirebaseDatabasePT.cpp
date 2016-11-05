#include "FirebaseDatabasePT.h"

FirebaseDatabasePT::FirebaseDatabasePT() {

}

void FirebaseDatabasePT::init() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
};

void FirebaseDatabasePT::setEnergy(uint8_t _energy) {

};

void FirebaseDatabasePT::standUp() {

};

void FirebaseDatabasePT::sitDown() {

};
