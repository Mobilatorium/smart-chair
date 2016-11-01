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
  lastCheck_ms = 0;
}

void PomodoroTechnique::init() {
  energyBar.init();
  firebaseDatabasePT.init();
}

void PomodoroTechnique::setPomodorDuration_min(uint8_t _pomodorDuration_min) {
  durationPerPoint_ms = ((uint64_t)_pomodorDuration_min) * 6000 / 256;
}

uint8_t PomodoroTechnique::getEnergy() {
  return energy;
}

void PomodoroTechnique::check() {
  if ((millis() - lastCheck_ms) > durationPerPoint_ms) {
    if (digitalRead(pin_irDistInterupter) == 0) {
      if (isPersonSitting) {
        isPersonSitting = 0;
        Serial.println("set");
      }
      if (energy > 0) energy--;
    } else {
      if (!isPersonSitting) {
        isPersonSitting = 1;
        Serial.println("got up");
      }
      if (energy < 255) energy++;
    }
    energyBar.setEnergy(energy);
    Serial.print("energy = ");
    Serial.println(energy);
    lastCheck_ms = millis();
  }
}
