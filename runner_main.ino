#include <NewPing.h>
#include <PID_v1.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"

void loop(){
  // driveForward(20.0, 100.0);
  pidController();
  // pidLib();
  // Serial.println(actual_velo_left);
  // displayCounts();
  // goStraight();

  //---------------------------------------------
}
