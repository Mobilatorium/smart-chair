#include "PomodoroTechnique.h"

PomodoroTechnique::PomodoroTechnique(uint8_t _pin_barDclk,
    uint8_t _pin_barDi,
    uint8_t _pin_irDistInterupter,
    uint8_t _pomodorDuration_min) :
    energyBar (_pin_barDclk, _pin_barDi, 0) {
  pin_irDistInterupter = _pin_irDistInterupter;
  pinMode(pin_irDistInterupter, INPUT);
  energy = 255;
  setPomodorDuration_min(_pomodorDuration_min);
  lastSitCheck_ms = 0;
  nextConfigCheck_ms = 0;
}

void PomodoroTechnique::init() {
  energyBar.init();
  firebaseDatabasePT.init();
  checkConfig();
  NtpClient ntpClient;
  ntpClient.init();
  unixTime_s = ntpClient.getNtpTime();
  initTime_s = millis() / 1000;
}

void PomodoroTechnique::setPomodorDuration_min(uint8_t _pomodorDuration_min) {
  pomodoroDuration_min = _pomodorDuration_min;
  durationPerPoint_ms = ((uint64_t)_pomodorDuration_min) * 6000 / 256;
  Serial.print("PomodoroDuration set to ");
  Serial.println(pomodoroDuration_min);
}

uint8_t PomodoroTechnique::getEnergy() {
  return energy;
}

void PomodoroTechnique::check() {
  if (lastSitCheck_ms + 1000 < millis()) {
    if (digitalRead(pin_irDistInterupter) == 0) {
      if (isPersonSitting) {
        isPersonSitting = 0;
        Serial.println("sat down");
        Firebase.push("/satdown", millis() - initTime_s + unixTime_s);
        if (Firebase.failed()) {
            Serial.print("setting /energy failed:");
            Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
        }
      } else {
        int energyChange = (millis() - lastSitCheck_ms) / durationPerPoint_ms;
        if (energy > energyChange) {
          energy -= energyChange;
          saveEnergy();
        } else if (energy != 0) {
          energy = 0;
          saveEnergy();
        }
      }
    } else {
      if (!isPersonSitting) {
        isPersonSitting = 1;
        Serial.println("got up");
        Firebase.push("/gotup", millis() - initTime_s + unixTime_s);
        if (Firebase.failed()) {
            Serial.print("setting /energy failed:");
            Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
        }
      } else {
        int energyChange = 5 * (millis() - lastSitCheck_ms)
            / durationPerPoint_ms; //energy restored faster than spend
        if (energy + energyChange < 255) {
          energy += energyChange;
          saveEnergy();
        } else if (energy != 255) {
          energy = 255;
          saveEnergy();
        }
      }
    }
    lastSitCheck_ms = millis();
  }

  if (millis() > nextConfigCheck_ms) {
    checkConfig();
    nextConfigCheck_ms += 20000;
  }
}

void PomodoroTechnique::saveEnergy() {
  energyBar.setEnergy(energy);
  Firebase.setInt("energy", energy);
  if (Firebase.failed()) {
      Serial.print("setting /energy failed:");
      Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
  }
  Serial.print("energy = ");
  Serial.println(energy);
}

void PomodoroTechnique::checkConfig() {
  /*Firebase arduino lib has method for streaming pobject from FirebaseDatabase
  but there is issue that it's not possible to write to base during streaming
  */
  Serial.println("checkConfig");
  int pomodoroDurationFb_min = Firebase.getInt("PomodoroDuration");
  if (Firebase.failed()) {
      Serial.print("getting /PomodoroDuration failed:");
      Serial.println(Firebase.error()); //TODO fix firebase HTTP client error msg
  } else if (pomodoroDurationFb_min != pomodoroDuration_min) {
    setPomodorDuration_min(pomodoroDurationFb_min);
  }
}
