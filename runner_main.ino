#include <NewPing.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"

void loop(){
  // getSonar();
  // Serial.print(dist_left);
  // Serial.print(" ");
  // Serial.println(dist_right);
  // driveForward(20.0, 100.0);
  pidController();
  // pidLib();
  // Serial.println(actual_velo_left);
  // displayCounts();
  // goStraight();
  // getHeading();

  //---------------------------------------------
}
