#include <Arduino.h>
#include <Grove_LED_Bar.h>
#include "EnergyBar.h"

//Create energyBar on ports 2 (DCLK) and 13 (DI) (Digital3 on WiolLink)
//with forward directions of LED
EnergyBar energyBar(2,13,0);

void setup() {
  //Turn on GPIO on Wio Board
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);

  //Start serial port
  Serial.begin(115200);

  //Init energyBar
  energyBar.init();
}

void loop() {
  energyBar.setEnergy(0);
  delay(1000);

  energyBar.setEnergy(50);
  delay(1000);

  energyBar.setEnergy(100);
  delay(1000);

  energyBar.setEnergy(150);
  delay(1000);

  energyBar.setEnergy(200);
  delay(1000);

  energyBar.setEnergy(250);
  delay(1000);
}
