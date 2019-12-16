
void color_Check(){
  // baseRGB();
  topRGB();
  color_Output = 1;

  if (color_Output != 5)
  {
    // halt();
    if (color_OutputT == color_Output)
    {
      runServo();
      color_Output = 5;
      Serial.print("hi");
    }
    else
    {
      runStepper(45,'A');
      Serial.println("Hello");
    }
  }
}

void baseRGB(){

  digitalWrite(S2_B, LOW);
  digitalWrite(S3_B, LOW);
  // Reading the output frequency
  redFrequency = pulseIn(color_base_output, LOW);
  // Printing the RED (R) value
  redColor = map(redFrequency,260,900,255,0);
  redColor = constrain(redColor,0,255);

  digitalWrite(S2_B, HIGH);
  digitalWrite(S3_B, HIGH);
  // Reading the output frequency
  greenFrequency = pulseIn(color_base_output, LOW);
  // Printing the GREEN (G) value
  greenColor = map(greenFrequency,450,1000,255,0);
  greenColor = constrain(greenColor,0,255);

  digitalWrite(S2_B, LOW);
  digitalWrite(S3_B, HIGH);
  // Reading the output frequency
  blueFrequency = pulseIn(color_base_output, LOW);
  // Printing the BLUE (B) value
  blueColor = map(blueFrequency,560,900,255,0);
  blueColor = constrain(blueColor,0,255);

  // Serial.print(redFrequency);
  Serial.print(redColor);
  Serial.print(" ");
  // Serial.print(greenFrequency);
  Serial.print(greenColor);
  Serial.print(" ");
  // Serial.print(blueFrequency);
  Serial.print(blueColor);
  Serial.print(" ");


  if ((redColor > 80 && redColor < 130) && (greenColor > 170 && greenColor < 220) && blueColor > 240){
    color_Output = 1; //blue = 0, green = 1, yellow = 2, brown = 3

  } else if ((redColor > 40 && redColor) < 60 && (greenColor > 55 && greenColor < 90) && blueColor < 20){
    color_Output = 2; //blue = 0, green = 1, yellow = 2, brown = 3

  } else if ((redColor > 190 && redColor < 230) && greenColor > 225 && blueColor > 240){
    color_Output = 11; //blue = 0, green = 1, yellow = 2, brown = 3

  } else if ((redColor > 95 && redColor < 115) && (greenColor > 10 && greenColor < 30) && blueColor < 25){
    color_Output = 4; //blue = 0, green = 1, yellow = 2, brown = 3

  } else {
    color_Output = 5;
  }
  Serial.println(color_Output);
}

void topRGB(){

  digitalWrite(S2_T, LOW);
  digitalWrite(S3_T, LOW);
  // Reading the output frequency
  redFrequencyT = pulseIn(color_top_output, LOW);
  // Printing the RED (R) value
  redColorT = map(redFrequencyT,140,630,255,0);
  redColorT = constrain(redColorT,0,255);

  digitalWrite(S2_T, HIGH);
  digitalWrite(S3_T, HIGH);
  // Reading the output frequency
  greenFrequencyT = pulseIn(color_top_output, LOW);
  // Printing the GREEN (G) value
  greenColorT = map(greenFrequencyT,210,610,255,0);
  greenColorT = constrain(greenColorT,0,255);

  digitalWrite(S2_T, LOW);
  digitalWrite(S3_T, HIGH);
  // Reading the output frequency
  blueFrequencyT = pulseIn(color_top_output, LOW);
  // Printing the BLUE (B) value
  blueColorT = map(blueFrequencyT,250,600,255,0);
  blueColorT = constrain(blueColorT,0,255);

  Serial.print(redFrequencyT);
  // Serial.print(redColorT);
  Serial.print(" ");
  Serial.print(greenFrequencyT);
  // Serial.print(greenColorT);
  Serial.print(" ");
  Serial.print(blueFrequencyT);
  // Serial.print(blueColorT);

if (redColorT > 60 && redColorT < 110 && greenColorT > 120 && greenColorT < 160 && blueColorT > 240)
  {
    color_OutputT = 0; //blue = 0, green = 1, yellow = 2, brown = 3
  }
else if (redColorT > 110 && redColorT < 160 && greenColorT > 140 && greenColorT < 195 && blueColorT > 100 && blueColorT < 160)
  {
    color_OutputT = 1; //blue = 0, green = 1, yellow = 2, brown = 3
  }
else if (redColorT > 240 && greenColorT > 240 && blueColorT > 200 && blueColorT < 240)
  {
    color_OutputT = 2; //blue = 0, green = 1, yellow = 2, brown = 3
  }
else if (redColorT > 170 && redColorT < 225 && greenColorT > 50 && greenColorT < 110 && blueColorT > 90 && blueColorT < 145)
  {
    color_OutputT = 3; //blue = 0, green = 1, yellow = 2, brown = 3
  }
else
  {
    color_OutputT = 5;
  }
  Serial.print(" ");
  Serial.println(color_OutputT);

}

void grdRGB(){

  digitalWrite(S2_B, LOW);
  digitalWrite(S3_B, LOW);
  //count OUT, pRed, RED
  redColor = pulseIn(color_base_output, digitalRead(color_base_output) == HIGH ? LOW : HIGH);
  digitalWrite(S3_B, HIGH);
  //count OUT, pBLUE, BLUE
  blueColor = pulseIn(color_base_output, digitalRead(color_base_output) == HIGH ? LOW : HIGH);
  digitalWrite(S2_B, HIGH);
  //count OUT, pGreen, GREEN
  greenColor = pulseIn(color_base_output, digitalRead(color_base_output) == HIGH ? LOW : HIGH);

  if ((redColor >= 30 && redColor <= 38) && (greenColor >= 40 && greenColor <= 50) && (blueColor >= 51 && blueColor <= 60)){
    color_Output = 1; // yellow

  }else if((redColor >= 44 && redColor <= 48) && (greenColor >= 52 && greenColor <= 56) && (blueColor >= 39 && blueColor <= 50)){
    color_Output = 3; // white

  }else{
    color_Output = 0;
  }
}

void dispColors(){
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
