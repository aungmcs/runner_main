
void readEncoder1(){
  /* generates counts from the left motor encoder*/

  if(digitalRead(encoderPinA1) == digitalRead(encoderPinB1))
  {
    count1 = count1 - 1;
  }
  else
  {
    count1 = count1 + 1;
  }
}


void readEncoder2(){
  /* generates counts from the right motor encoder */

  if(digitalRead(encoderPinA2) == digitalRead(encoderPinB2))
  {
    count2 = count2 + 1;
  }
  else
  {
    count2 = count2 - 1;
  }
}


void displayCounts(){
  /* prints the value of counts of both motors on serial monitor */

  Serial.print("Left Count:");
  Serial.print(countLeft);
  Serial.print(" || ");
  Serial.print("Right Count:");
  Serial.println(countRight);
}


void driveForward(int leftSpeed, int rightSpeed){

  /* drives both motors with the desire speed (without PID)*/

  digitalWrite(cw_left, LOW);
  digitalWrite(ccw_left, HIGH);
  analogWrite(pwm_left, leftSpeed);

  digitalWrite(cw_right, HIGH);
  digitalWrite(ccw_right, LOW);
  analogWrite(pwm_right, rightSpeed);
}


void pidController(){
  /* output: required bits (volts) to the motors
           : bit_right and bit_left in the range of 0 to 255
   */
  float Kp1 = 2.07, Ki1 = 1.24, Kd1 = 1.34;
  float Kp2 = 9.98, Ki2 = 0.0, Kd2 = 0.39;

  now_time = millis();

   // from count to angle of the rotation of the wheels
  float angle_left = (360.0/666.0) * countLeft;
  float angle_right = (360.0/666.0) * countRight;

  // from degree to radian conversion
  float radian_left = angle_left * (PI/180.0);
  float radian_right = angle_right * (PI/180.0);

  unsigned long dt = now_time - prv_time;

  // angular velocity = d(angle) / dt --> unit = rad/s
  actual_velo_left = (radian_left - prv_radian_left) /
  //                       -------------------------------
                                (double)(dt * 0.001);

  actual_velo_right =  (radian_right - prv_radian_right) /
 //                       ----------------------------------
                                  (double)(dt * 0.001);

  float error_left = desire_speed - actual_velo_left;
  float error_right = desire_speed - actual_velo_right;

  float volt_left = (Kp1*error_left) +
                    (Ki1*(error_left+prv_error_left))+
                    (Kd1*(error_left-prv_error_left))


  float volt_right = (Kp1*error_right) +
                     (Ki1*(error_right + prv_error_right)) +
                     (Kd1*(error_right - prv_error_right))

  bit_left = (volt_left / 12.0) * 255;
  bit_left = constrain(bit_left, 0, 255);

  bit_right = (volt_right / 12.0) * 255;
  bit_right = constrain(bit_right, 0, 255);

  prv_error_left = error_left;
  prv_error_right = error_right;

  prv_radian_left = radian_left;
  prv_radian_right = radian_right;

  prv_time = now_time;
}


void goStraight(){
  /* driving the robot along a straight path
     using a pidController
  */

  pidController();
  driveForward(bit_left, bit_right);
}
