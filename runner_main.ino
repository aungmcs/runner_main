#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"


void loop(){

/*/
  // color_Check();
  // baseRGB();
  // go1feet();
  // solveMaze();
  driveForward(100,100);
  // displayCounts();
  // delay(500);
  // grdRGB();
  // dispColors();
//   for (int r = 0; r < 120; r++){
//     runStepper(45, 'A');
// }

/*/
//====================================================//
//------------Maze Solving Algo ----------------------//
//====================================================//
  getSonar();
  baseRGB();

  if(color_Output < 5)
  {
    sorting = true;
  }


  // go straight
  if((sonarLeft == true && sonarRight == true) || (sonarLeft == true && sonarRight == false)) {

    if (sorting == true){
      for (int r = 0; r < 120; r++){
        stop();
      }
      resetCounts();
      for (int r = 0; r < 120; r++){
        go1feet();
      }
      for (int r = 0; r < 7; r++){
        runStepper(45, 'A');
      }
      runServo();
      sorting = false;

    } else {
      start_turn = false;
      move('s');
    }
  }

//-------------------------------
  // turn left
  if (sonarLeft == false){
    start_turn = true;
  }

  if (start_turn == true){

    if(sorting == true){
      resetCounts();
      for (int r = 0; r < 120; r++){
        go6inches();
      }
      resetCounts();
      for (int r = 0; r < 120; r++){
        turnLeft();
      }
      resetCounts();
      for (int r = 0; r < 120; r++){
        go7inches();
      }
      for (int r = 0; r < 7; r++){
        runStepper(45, 'A');
      }
      runServo();
      sorting = false;
//----------------------------------------
    } else {
      resetCounts();
      for (int r = 0; r < 120; r++){
        go6inches();
      }
      resetCounts();
      for (int r = 0; r < 120; r++){
        turnLeft();
      }
      resetCounts();
      for (int r = 0; r < 120; r++){
        go7inches();
      }
    }

    start_turn = false;
  }

//-----------------------------------
  // turn right
  if (sonarLeft == true && dF < 6.00)
  {
    for (int r = 0; r < 120; r++){
      stop();
    }
    delay(500);
    resetCounts();
    for (int r = 0; r < 120; r++){
      turnRight();
    }

    if (sorting == true){
      resetCounts();
      for (int r = 0; r < 120; r++){
        go6inches();
      }
      for (int r = 0; r < 7; r++){
        runStepper(45, 'A');
      }
      runServo();
      sorting = false;
    }
  }
//-----------------------------------------
  // //dead end
  // if (sonarLeft == true && dF < 6.00 && sonarRight == true)
  // {
  //   for (int r = 0; r < 120; r++){
  //     stop();
  //     }
  //   delay(500);
  //   resetCounts();
  //   for (int r = 0; r < 120; r++){
  //     turnRight();
  //     }
  // }

//==============================================================



/**/
}
