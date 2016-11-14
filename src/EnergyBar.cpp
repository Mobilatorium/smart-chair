#include "Energybar.h"

EnergyBar::EnergyBar(uint8_t pinDclk, uint8_t pinDi, uint8_t direction)
    : _ledBar(pinDclk, pinDi, direction) {

}

void EnergyBar::init() {
  _ledBar.begin();
  setEnergy(255);
}

void EnergyBar::setEnergy(uint8_t energy) {
  uint16_t barsStatus = 1;
  for (uint8_t i = 1; i < 10, energy >= 25 * i; ++i) {
      bitSet(barsStatus, i);
  }
  _ledBar.setBits(barsStatus);
}
