#include <Arduino.h>
#include "PomodoroTechnique.h"

/*Create pomodoroTechnique with Led bar on pins 2 (DCLK) and
13 (DI) (Digital3 on WiolLink) with forward directions of LED
and IR Distance Interupter on 14 pin and duration 2 minuts
*/
PomodoroTechnique pomodoroTechnique(2, 13, 14, 2);


void setup() {
  //Turn on GPIO on Wio Board
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);

  //Start serial port
  Serial.begin(28800);

  //Init pomodoroTechnique
  pomodoroTechnique.init();
  Serial.println("setup finished");
}

void loop() {
  pomodoroTechnique.check();
}
