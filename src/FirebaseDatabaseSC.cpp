#include "FirebaseDatabaseSC.h"

FirebaseDatabaseSC::FirebaseDatabaseSC() {

}

void FirebaseDatabaseSC::init() {

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

  NtpClient ntpClient;
  ntpClient.init();
  _unixTimeInSec = ntpClient.getNtpTime();
  _initTimeInSec = millis() / 1000;
};

void FirebaseDatabaseSC::setEnergy(uint8_t energy) {
  Firebase.setInt("energy", energy);
  if (Firebase.failed()) {
      Serial.print("setting /energy failed:");
      Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
  }
};

void FirebaseDatabaseSC::standUp() {
  Firebase.push("/gotup", millis() - _initTimeInSec + _unixTimeInSec);
  if (Firebase.failed()) {
      Serial.print("setting /energy failed:");
      Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
  }
};

void FirebaseDatabaseSC::sitDown() {
  Firebase.push("/satdown", millis() - _initTimeInSec + _unixTimeInSec);
  if (Firebase.failed()) {
      Serial.print("setting /energy failed:");
      Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
  }
};

uint8_t FirebaseDatabaseSC::getFbSittingDurationInSec() {
  int sittingDurationFbInSec = Firebase.getInt("sittingDuration");
  if (Firebase.failed()) {
      Serial.print("getting /sittingDuration failed:");
      Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
      return 0;
  } else {
    return sittingDurationFbInSec;
  }
}

uint8_t FirebaseDatabaseSC::getFbRestoreDurationInSec() {
  int restorationDurationFbInSec = Firebase.getInt("restorationDuration");
  if (Firebase.failed()) {
      Serial.print("getting /restorationDuration failed:");
      Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
      return 0;
  } else {
    return restorationDurationFbInSec;
  }
}
