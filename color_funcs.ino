
void sortingTest(int colorType){

  baseRGB();
  topRGB();
  color_Output = colorType;

  if (color_Output != 5){
    if (color_OutputT == color_Output){
      runServo();
      color_Output = 5;

    }else{
      runStepper(45,'A');
    }
  }
}

void colorCheck(){
  /*
   * check the color data at the top to the one at the bottom
   * upon matching rotate the servo motor to drop off the cubes
   */
  for (int r = 0; r < 15; r++){
    runStepper(45, 'A');
    topRGB();
    if (blueT==true && blue==true)
    {
      runServo();
      blue = false;
      blueT = false;
      break;
    }

    if (green == true && greenT == true)
    {
      runServo();
      green = false;
      greenT = false;
      break;
    }

    if (yellow == true && yellowT == true)
    {
      runServo();
      yellow = false;
      yellowT = false;
      break;
    }

    if (brown == true && brownT == true)
    {
      runServo();
      brown = false;
      brownT = false;
      break;
    }
  }
}

void baseRGB(){
  // retrieve data from the color sensor at the bottom of the robot

  digitalWrite(S2_B, LOW);
  digitalWrite(S3_B, LOW);
  // Reading the output frequency
  redFrequency = pulseIn(color_base_output, LOW);
  // Printing the RED (R) value
  redColor = map(redFrequency,250,1200,255,0);
  redColor = constrain(redColor,0,255);

  digitalWrite(S2_B, HIGH);
  digitalWrite(S3_B, HIGH);
  // Reading the output frequency
  greenFrequency = pulseIn(color_base_output, LOW);
  // Printing the GREEN (G) value
  greenColor = map(greenFrequency,250,1300,255,0);
  greenColor = constrain(greenColor,0,255);

  digitalWrite(S2_B, LOW);
  digitalWrite(S3_B, HIGH);
  // Reading the output frequency
  blueFrequency = pulseIn(color_base_output, LOW);
  // Printing the BLUE (B) value
  blueColor = map(blueFrequency,250,900,255,0);
  blueColor = constrain(blueColor,0,255);

//--------------------------------------------------------------------------//
//-----  blue = 1, green = 2, yellow = 3, brown = 4, white = 5 -------------//
//--------------------------------------------------------------------------//

  if (redColor < 60 && greenColor < 60 && blueColor > 20 && blueColor < 140){
    color_Output = 1; //blue = 0, green = 1, yellow = 2, brown = 3
    blue = true;

  }else if (redColor > 20 && redColor < 110 && greenColor > 110 && greenColor < 190 && blueColor > 65 && blueColor < 150){
    color_Output = 2;
    green = true;

  }else if (redColor > 220 && greenColor > 220 && blueColor > 160 && blueColor < 230){
    color_Output = 3;
    yellow = true;

  }else if (redColor > 60 && redColor < 170 && greenColor < 80 && blueColor < 80){
    color_Output = 4;
    brown = true;

  }else if (redColor < 30 && greenColor < 30 && blueColor < 30){
    color_Output = 12;
    black = true;

  }else if (redColor > 235 && greenColor > 235 && blueColor > 245){
    color_Output = 5;
  }
}

void topRGB(){
  // retrieve data from the color sensor at the top of the robot

  digitalWrite(S2_T, LOW);
  digitalWrite(S3_T, LOW);
  // Reading the output frequency
  redFrequencyT = pulseIn(color_top_output, LOW);
  // Printing the RED (R) value
  redColorT = map(redFrequencyT,120,950,255,0);
  redColorT = constrain(redColorT,0,255);

  digitalWrite(S2_T, HIGH);
  digitalWrite(S3_T, HIGH);
  // Reading the output frequency
  greenFrequencyT = pulseIn(color_top_output, LOW);
  // Printing the GREEN (G) value
  greenColorT = map(greenFrequencyT,200,950,255,0);
  greenColorT = constrain(greenColorT,0,255);

  digitalWrite(S2_T, LOW);
  digitalWrite(S3_T, HIGH);
  // Reading the output frequency
  blueFrequencyT = pulseIn(color_top_output, LOW);
  // Printing the BLUE (B) value
  blueColorT = map(blueFrequencyT,250,900,255,0);
  blueColorT = constrain(blueColorT,0,255);

  Serial.print(redColorT);

  Serial.print(" ");
  Serial.print(greenColorT);

  Serial.print(" ");
  Serial.print(blueColorT);

  //--------------------------------------------------------------------------//
  //-----  blue = 1, green = 2, yellow = 3, brown = 4, white = 5 -------------//
  //--------------------------------------------------------------------------//


  if (redColorT < 50  && greenColorT > 40 && greenColorT < 120 && blueColorT > 160 && blueColorT < 240){
    color_OutputT = 1; //blue = 0, green = 1, yellow = 2, brown = 3
    blueT = true;

  }else if (redColorT > 110 && redColorT < 210 && greenColorT > 170  && blueColorT > 180){
    color_OutputT = 2; //blue = 0, green = 1, yellow = 2, brown = 3
    greenT = true;

  }else if (redColorT > 200 && greenColorT > 200 && blueColorT > 150 && blueColorT < 220){
    color_OutputT = 3; //blue = 0, green = 1, yellow = 2, brown = 3
    yellowT = true;

  }else if (redColorT > 70 && redColorT < 150 &&  greenColorT < 60 && blueColorT > 15 && blueColorT < 85){
    color_OutputT = 4; //blue = 0, green = 1, yellow = 2, brown = 3
    brownT = true;

  }else{
    color_OutputT = 5;
  }


  Serial.print(" ");
  Serial.println(color_OutputT);

}

void dispColors(){
  // display the bottom color sensor data
  Serial.print("R =");
  Serial.print(redColor, DEC);
  Serial.print(" G = ");
  Serial.print(greenColor, DEC);
  Serial.print(" B = ");
  Serial.print(blueColor, DEC);
  Serial.print(" ");
  Serial.print(color_Output);
  Serial.println(" ");
}
