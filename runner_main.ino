#include <NewPing.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"

void loop(){

  // go12cm();

  getSonar();
  // Serial.println(dFl);
  if(sonarLeft == true && sonarRight == true || sonarLeft == true && sonarRight == false){

    move('s');
  }

  if (sonarLeft == false){
    start_turn = true;
  }

 //-----------------------------------------
  if (start_turn== true){
      resetCounts();
      for (int r = 0; r < 120; r++){
        turn45();
        }
      resetCounts();
      for (int r = 0; r < 120; r++){
        go5cm();
        }
      //----------------
      resetCounts();
      for (int r = 0; r < 120; r++){
        turn45();
        }
      resetCounts();
      for (int r = 0; r < 120; r++){
        go5cm();
        }
      //-----------------------
      resetCounts();
      for (int r = 0; r < 120; r++){
        turn45();
        }
      resetCounts();
      for (int r = 0; r < 120; r++){
        go5cm();
        }
      //-----------------------
      resetCounts();
      for (int r = 0; r < 120; r++){
        turn45();
        }
      resetCounts();
      for (int r = 0; r < 120; r++){
        go5cm();
        }
      start_turn = false;
  }

//-----------------------------------
  if (sonarLeft == true && sonarFront == true)
  {
    resetCounts();
    delay(500);
    for (int r = 0; r < 120; r++){
      turnRight();
      }
  }

//=====================================
  //----------------------------------------
//   // Serial.println(dist_frontLeft);
//
// //========================================================
//
//   if (sonarLeft == false){
//
//     resetCounts();
//     for (int i = 0; i < 120; i++){
//       go6inches();
//
//       if ( dist_frontLeft > 0.00 && dist_frontLeft < 7.00 ){
//        //reverse right motor dir
//        digitalWrite(cw_left, HIGH);
//        digitalWrite(ccw_left, LOW);
//        digitalWrite (cw_right,HIGH);
//        digitalWrite (ccw_right,LOW);
//        analogWrite(pwm_left,0);
//        analogWrite(pwm_right,10);     //60
//
//       }else if (dist_frontRight > 0.00 && dist_frontRight < 7.00 ){
//          //reverse left motor dir
//          digitalWrite (cw_left,LOW);
//          digitalWrite (ccw_left,HIGH);
//          digitalWrite(cw_right, LOW);
//          digitalWrite(ccw_right, HIGH);
//          analogWrite(pwm_left,10);
//          analogWrite(pwm_right,0);
//       }
//     }
//     //---------------------------
//     resetCounts();
//     delay(500);
//     for (int q = 0; q < 120; q++){
//       turnLeft();
//     }
//     //-----------------------------
//     resetCounts();
//     for (int w = 0; w < 120; w++){
//       go1feet();
//       if ( dist_frontLeft > 0.00 && dist_frontLeft < 7.00 ){
//        //reverse right motor dir
//        digitalWrite(cw_left, HIGH);
//        digitalWrite(ccw_left, LOW);
//        digitalWrite (cw_right,HIGH);
//        digitalWrite (ccw_right,LOW);
//        analogWrite(pwm_left,0);
//        analogWrite(pwm_right,10);
//
//       }else if (dist_frontRight > 0.00 && dist_frontRight < 7.00 ){
//          //reverse left motor dir
//          digitalWrite (cw_left,LOW);
//          digitalWrite (ccw_left,HIGH);
//          digitalWrite(cw_right, LOW);
//          digitalWrite(ccw_right, HIGH);
//          analogWrite(pwm_left,10);
//          analogWrite(pwm_right,0);
//       }
//     }
//
//
//     if (sonarLeft == true && sonarFront == true)
//     {
//       resetCounts();
//       delay(500);
//       for (int r = 0; r < 120; r++){
//         turnRight();
//       }
//     }
//
//   }
  //=============================================================
































  //
  // if (sonarLeft == false){
  //   if (sonarFront == false){
  //     //go6inches
  //     resetCounts();
  //     // delay(500);
  //     for (int i = 0; i < 120; i++){
  //          go6inches();
  //
  //        }
  //
  //      for (int i = 0; i < 2; i++){
  //           stop();
  //         }
  //     //--------------------
  //     //turn left
  //     resetCounts();
  //     delay(500);
  //     for (int q = 0; q < 120; q++){
  //          turnLeft();
  //        }
  //     //-------------------
  //     //go straight
  //     for (int w = 0; w < 30; w++){
  //          goStraight(true);
  //        }
  //     // goStraight(true);
  //
  //   }else if (sonarFront == true){
  //       //turnLeft
  //       resetCounts();
  //       delay(500);
  //       for (int s = 0; s < 120; s++){
  //            turnLeft();
  //          }
  //
  //       //goStraight(sonarGuided)
  //       // for (int e = 0; e < 50; e++){
  //       //      goStraight(true);
  //       //    }
  //       goStraight(true);
  //    }
  //
  // }else if (sonarLeft == true){
  //   if (sonarFront == true){
  //     resetCounts();
  //     delay(500);
  //     for (int z = 0; z < 120; z++){
  //          turnRight();
  //      }
  //
  //   }else if (sonarFront == false){
  //     goStraight(true);
  //   }
  // }
  //
  //
  //

























// //===================================================
//
//   if (sonarFront == true){
//     for (int a = 0; a < 2; a++){
//       stop();
//     }
//   }
//
// //---------------------------------------
//
//   if (sonarFront == true && sonarLeft == true ){
//     for (int z = 0; z < 2; z++){
//       stop();
//     }
//
//     resetCounts();
//     delay(500);
//     for (int c = 0; c < 120; c++){
//          turnRight();
//        }
//   }
//
// //------------------------------------
//
//   if (sonarFront == true && sonarLeft == true & sonarRight == true ){
//     for (int q = 0; q < 2; q++){
//       stop();
//     }
//
//     resetCounts();
//     delay(500);
//     for (int q = 0; q < 120; q++){
//          turnRight();
//        }
//   }
//

//==========================

//--------------------------
//   getSonar();
//
//   if (sonarFront == false){
//   sonar_help = true;
//   goStraight(sonar_help);
//   }
// //-------------
//   if (sonarFront == true ){
//     for (int q = 0; q < 2; q++){
//       stop();
//     }
//
//     resetCounts();
//     delay(1000);
//     for (int q = 0; q < 120; q++){
//          turnLeft();
//        }
//   }








}
