#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "variables.h"


void loop(){

/**/
// baseRGB();
// dispColors();
// color_Output = 1;
// colorCheck();
// color_Output = 1;
// color_Check();
// displayCounts();
// perLeft();
// perRight();
rightie();
// topRGB();
  // solveMaze();
  // baseRGB();
  //
  // if (color_Output < 5 ){
  //   if (color_Output == 5 ){
  //     colorDetected = true;
  //   }
  // }


 //  if (prvColor == 1  && currentColor == 5){
 //    driveForward(0,0);
 //    for (int r = 0; r < 80; r++){
 //       runStepper(45, 'A');
 //   }
 //
 // }else{
 //   driveForward(50,50);
 // }


  // getSonar();
  // Serial.println(fwallPossible);
  // displayDist();
   // solveMaze();
  // followRight();
  // color_Check();
  // baseRGB();
  // baseRGBytu();
  // dispColors();
  // go1feet();
  // solveMaze();
  // displayCounts();
  // delay(500);
  // grdRGB();
  // baseRGB();
  // dispColors();
//   for (int r = 0; r < 80; r++){
//     runStepper(45, 'A');
// }

/*/
//====================================================//
//------------Maze Solving Algo ----------------------//
//====================================================//
getSonar();
baseRGBytu();

if (color_Output < 5){
  colorDetected = true;

}else if(color_Output >=5 && color_Output < 8){
  colorDetected = false;
}
//-------------------------------------------------------------------
// left turn scenerio
if (colorDetected == true && turncomplete == true){
  resetCounts();
  for (int r = 0; r < 5; r++){
    stop();
  }
  colorCheck();

}

//straight scenerio
if (color_Output == 5 && straightColor == true){
  resetCounts();
  for (int r = 0; r < 5; r++){
    stop();
  }
  colorCheck();
  straightColor = false;

}
//----------------------------------------------------------------------------
if((sonarLeft == true && sonarRight == true) || (sonarLeft == false && sonarRight == true)){
  if (colorDetected == true){
    straightColor = true;
  }

  turncomplete = false;
  start_turn = false;
  move('s');

}

//-------------------------------

if (sonarRight == false){
  turncomplete = false;
  start_turn = true;
}

if (start_turn == true){
  resetCounts();
  for (int r = 0; r < 5; r++){
    stop();
  }
  resetCounts();
  for (int r = 0; r < 70; r++){
    go6inches();
  }
  resetCounts();
  for (int r = 0; r < 70; r++){
    turnRight();
  }
  resetCounts();
  for (int r = 0; r < 70; r++){
    go7inches();
  }
  turncomplete = true;
  start_turn = false;
}

//-----------------------------------

if (sonarRight == true && dF < 6.00)
{
  resetCounts();
  for (int r = 0; r < 5; r++){
    stop();
    }
  // delay(200);//////////////////////
  resetCounts();
  for (int r = 0; r < 70; r++){
    turnLeft()();
    }
}
//-------------------------------------
//end point
if (black == true){
  resetCounts();
  for (int r = 0; r < 8; r++){
    stop();
  }
  resetCounts();
  for (int r = 0; r < 70; r++){
    go2inches();
  }
  while(1);
}
//==============================================================



/**/
}
