#ifndef PomodoroTechnique_h
#define PomodoroTechnique_h

#include <Arduino.h>
#include "EnergyBar.h"
#include "FirebaseDatabasePT.h"

class PomodoroTechnique {
private:
  uint8_t energy;
  uint32_t lastCheck_ms;
  EnergyBar energyBar;
  uint8_t pin_irDistInterupter;
  boolean isPersonSitting;
  uint16_t durationPerPoint_ms;
  FirebaseDatabasePT firebaseDatabasePT;
public:
  PomodoroTechnique(uint8_t _pin_barDclk,
      uint8_t _pin_barDi,
      uint8_t _pin_irDistInterupter,
      uint8_t _pomodorDuration_min);
  void init();
  void setPomodorDuration_min(uint8_t _pomodorDuration_min);
  uint8_t getEnergy();
  void check();
};

#endif
