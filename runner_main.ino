#include <NewPing.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"

void loop(){

  // turnLeft();

  // displayDist();
// if (realTurn == false){
//
//   getSonar();
//   sonar_help = true;
//   goStraight (sonar_help);
// }
//
//   if (sonarFront == 1 ){
//     shouldTurn = true;
//   }
//
//   if (shouldTurn==true){
//     resetCounts();
//     realTurn = true;
//     shouldTurn = false;
//   }
//
//   if (realTurn==true){
//     turnLeft();
//   }
   getSonar();
   // sonar_help = true;
   // goStraight (sonar_help);

     if (dist_left < 9 && dist_right < 9){
       sonar_help = true;
       goStraight(sonar_help);
     }
     else{
       sonar_help = false;
       goStraight(sonar_help);
     }


if (sonarFront == 1)
{
  resetCounts ();
  for (int q = 0; q < 200; q++)
  {
    turnLeft();
  }
}
}

//------------------------------

  // getSonar();
  //
  // if (sonarLeft == 0){
  //   if (sonarFront == 1){
  //     resetCounts();
  //     start_timer = millis();
  //     turnLeft();
  //     if (start_timer >= 3000){
  //       turnComplete = true;
  //     }
  //   }
  // }
  //
  //   else{
  //     if(turnComplete == true){
  //       if (dist_left < 9 && dist_right < 9){
  //         sonar_help = true;
  //         goStraight(sonar_help);
  //       }
  //       else{
  //         sonar_help = false;
  //         goStraight(sonar_help);
  //       }
  //     }
  //   }
  //
  //   if (sonarLeft==1){
  //     if (sonarFront == 0){
  //       if (dist_left < 7 && dist_right < 7){
  //         sonar_help = true;
  //         goStraight(sonar_help);
  //       }
  //       else{
  //         sonar_help = false;
  //         goStraight(sonar_help);
  //       }
  //     }
  //     else{
  //       digitalWrite(cw_left, LOW);
  //       digitalWrite(ccw_left, LOW);
  //       analogWrite(pwm_left, 0);
  //
  //       digitalWrite(cw_right, LOW);
  //       digitalWrite(ccw_right, LOW);
  //       analogWrite(pwm_right, 0);
  //     }
  //   }




//   if (dist_left < 9 && dist_right < 9){
//     sonar_help = true;
//     goStraight(sonar_help);
//   }
//   else{
//     sonar_help = false;
//     goStraight(sonar_help);
//   }
//
// }
