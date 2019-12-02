
void color_Check()
{
  baseRGB();
  topRGB();

  if (color_Output != 5)
  {
    // halt();
    if (color_Output == color_OutputT)
    {
      runServo();
      delay(1000);
      color_OutputT = 5;
    }
    else
    {
      runStepper(45,'A');
    }
  }
}

void baseRGB(){
  digitalWrite(S2_B, LOW);
  digitalWrite(S3_B, LOW);
  // Reading the output frequency
  redFrequency = pulseIn(color_base_output, LOW);
  // Printing the RED (R) value
  redColor = map(redFrequency,140,540,255,0);
  redColor = constrain(redColor,0,255);

  digitalWrite(S2_B, HIGH);
  digitalWrite(S3_B, HIGH);
  // Reading the output frequency
  greenFrequency = pulseIn(color_base_output, LOW);
  // Printing the GREEN (G) value
  greenColor = map(greenFrequency,220,560,255,0);
  greenColor = constrain(greenColor,0,255);

  digitalWrite(S2_B, LOW);
  digitalWrite(S3_B, HIGH);
  // Reading the output frequency
  blueFrequency = pulseIn(color_base_output, LOW);
  // Printing the BLUE (B) value
  blueColor = map(blueFrequency,290,560,255,0);
  blueColor = constrain(blueColor,0,255);

  // Serial.print(redFrequency);
  Serial.print(redColor);
  Serial.print(" ");
  // Serial.print(greenFrequency);
  Serial.print(greenColor);
  Serial.print(" ");
  // Serial.println(blueFrequency);
  Serial.print(blueColor);
  Serial.print(" ");

  if (redColor > 20 && redColor < 50 && greenColor > 45 && greenColor < 70 && blueColor > 220)
    {
      color_Output = 0; //blue = 0, green = 1, yellow = 2, brown = 3
    }
  if (redColor > 60 && redColor < 80 && greenColor > 50 && greenColor < 70 && blueColor > 10 && blueColor < 40)
    {
      color_Output = 1; //blue = 0, green = 1, yellow = 2, brown = 3
    }
  if (redColor > 220 && greenColor > 200 && greenColor < 225 && blueColor > 130 && blueColor < 170)
    {
      color_Output = 2; //blue = 0, green = 1, yellow = 2, brown = 3
    }
  if (redColor > 115 && redColor < 155 && greenColor > 20 && greenColor < 50 && blueColor > 50 && blueColor < 90)
    {
      color_Output = 3; //blue = 0, green = 1, yellow = 2, brown = 3
    }
    Serial.println(color_Output);
}

void topRGB(){
  color_OutputT = 2;

//   digitalWrite(S2_T, LOW);
//   digitalWrite(S3_T, LOW);
//   // Reading the output frequency
//   redFrequencyT = pulseIn(color_top_output, LOW);
//   // Printing the RED (R) value
//   redColorT = map(redFrequencyT,140,540,255,0);
//   redColorT = constrain(redColorT,0,255);
//
//   digitalWrite(S2_T, HIGH);
//   digitalWrite(S3_T, HIGH);
//   // Reading the output frequency
//   greenFrequencyT = pulseIn(color_top_output, LOW);
//   // Printing the GREEN (G) value
//   greenColorT = map(greenFrequencyT,220,560,255,0);
//   greenColorT = constrain(greenColorT,0,255);
//
//   digitalWrite(S2_T, LOW);
//   digitalWrite(S3_T, HIGH);
//   // Reading the output frequency
//   blueFrequencyT = pulseIn(color_top_output, LOW);
//   // Printing the BLUE (B) value
//   blueColorT = map(blueFrequencyT,290,560,255,0);
//   blueColorT = constrain(blueColorT,0,255);
//
//   Serial.print(redFrequencyT);
//   // Serial.print(redColorT);
//   Serial.print(" ");
//   Serial.print(greenFrequencyT);
//   // Serial.print(greenColorT);
//   Serial.print(" ");
//   Serial.println(blueFrequencyT);
//   // Serial.println(blueColorT);
//
// if (redColorT > 20 && redColorT < 50 && greenColorT > 45 && greenColorT < 70 && blueColorT > 220)
//   {
//     color_OutputT = 0; //blue = 0, green = 1, yellow = 2, brown = 3
//   }
// if (redColorT > 60 && redColorT < 80 && greenColorT > 50 && greenColorT < 70 && blueColorT > 10 && blueColorT < 40)
//   {
//     color_OutputT = 1; //blue = 0, green = 1, yellow = 2, brown = 3
//   }
// if (redColorT > 220 && greenColorT > 200 && greenColorT < 225 && blueColorT > 130 && blueColorT < 170)
//   {
//     color_OutputT = 2; //blue = 0, green = 1, yellow = 2, brown = 3
//   }
// if (redColorT > 115 && redColorT < 155 && greenColorT > 20 && greenColorT < 50 && blueColorT > 50 && blueColorT < 90)
//   {
//     color_OutputTd = 3; //blue = 0, green = 1, yellow = 2, brown = 3
//   }
//   Serial.println(color_OutputT);

}
