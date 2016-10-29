#include "Energybar.h"

EnergyBar::EnergyBar(uint8_t _pin_dclk, uint8_t _pin_di, uint8_t _direction)
    : ledBar(_pin_dclk, _pin_di, _direction) {

}

void EnergyBar::init() {
  ledBar.begin();
}

void EnergyBar::setEnergy(uint8_t _energy) {
  uint16_t barsStatus = 1;
  for (uint8_t i = 1; i < 10, _energy >= 25 * i; ++i) {
      bitSet(barsStatus, i);
  }
  ledBar.setBits(barsStatus);
}
