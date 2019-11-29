#include <NewPing.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"

void loop(){

    // getSonar();
    // Serial.println(dist_frontRight);
  getSonar();

  if (dF > 4.00){
  sonar_help = true;
  goStraight(sonar_help);
  }
//-------------
  if (dF <= 4.00){
    for (int q = 0; q < 2; q++){
         stop();
       }

    resetCounts();
    delay(1000);
    for (int q = 0; q < 120; q++){
         turnLeft();
       }
  }

//---------------------------------

//this kindda work for turn with pause
// time_now = millis();
// if (time_now <= 2000)
// {
// digitalWrite(cw_left, HIGH);
// digitalWrite(ccw_left, LOW);
// analogWrite(pwm_left, 40);
//
// digitalWrite(cw_right, HIGH);
// digitalWrite(ccw_right, LOW);
// analogWrite(pwm_right, 40);
//
// }else{
//   digitalWrite(cw_left, LOW);
//   digitalWrite(ccw_left, LOW);
//   analogWrite(pwm_left, 0);
//
//   digitalWrite(cw_right, LOW);
//   digitalWrite(ccw_right, LOW);
//   analogWrite(pwm_right, 0);
// }







}
