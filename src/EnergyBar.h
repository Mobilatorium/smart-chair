#ifndef EnergyBar_h
#define EnergyBar_h

#include <Arduino.h>
#include <Grove_LED_Bar.h>

class EnergyBar {
private:
  Grove_LED_Bar ledBar;
public:
  //Create object with Grove_LED_Bar on specified ports
  EnergyBar(uint8_t _pin_dclk, uint8_t _pin_di, uint8_t _direction);
  //Init Grove_LED_Bar object
  void init();
  //SetEnergy in proportion to the energy variable (limits from 0 to 255)
  void setEnergy(uint8_t _energy);
  //TODO function for blink on lowest and highest level
  //void blink();
};

#endif
