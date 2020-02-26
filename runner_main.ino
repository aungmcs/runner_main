#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"


void loop(){

  // left wall following maze alogrithm embedded with cube solving feature
  leftie();

}
