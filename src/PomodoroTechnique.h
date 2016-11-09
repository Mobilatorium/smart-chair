#ifndef PomodoroTechnique_h
#define PomodoroTechnique_h

#include <Arduino.h>
#include "EnergyBar.h"
#include "FirebaseDatabasePT.h"
#include "NtpClient.h"
#include <Ultrasonic.h>

class PomodoroTechnique {
  
private:
  uint32_t unixTime_s;
  uint32_t initTime_s;
  uint8_t energy;
  uint32_t pomodoroDuration_min;
  uint64_t lastSitCheck_ms;
  uint64_t nextConfigCheck_ms;
  boolean isPersonSitting;
  uint16_t durationPerPoint_ms;
  uint8_t rangeThreshold;
  EnergyBar energyBar;
  FirebaseDatabasePT firebaseDatabasePT;
  Ultrasonic ultrasonic;

  void saveEnergy();
  void checkConfig();

public:
  PomodoroTechnique(uint8_t _pin_barDclk,
      uint8_t _pin_barDi,
      uint8_t _pin_ultrasonicRangeFinder,
      uint8_t _pomodorDuration_min,
      uint8_t _rangeThreshold);
  void init();
  void setPomodorDuration_min(uint8_t _pomodorDuration_min);
  uint8_t getEnergy();
  void check();
};

#endif
