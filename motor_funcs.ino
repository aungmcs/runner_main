//----------------------------------------------------//
//-----------  Go Straight With own PID  -------------//
//----------------------------------------------------//

void pidController(){
  /* output: required bits (volts) to the motors
           : bit_right and bit_left in the range of 0 to 255
   */


   now_time = millis();



    // from count to angle of the rotation of the wheels
   angle_left = (360.0/660.0) * countLeft; //check both speeds again.
   angle_right = (360.0/660.0) * countRight;



   // from degree to radian conversion
   radian_left = angle_left * (PI/180.0);
   radian_right = angle_right * (PI/180.0);



   dt = now_time - prv_time; // dt is fine



   // angular velocity = d(angle) / dt --> unit = rad/s
   // actual_velo_left = (radian_left - prv_radian_left) * 1000  / dt;
   // actual_velo_right =  (radian_right - prv_radian_right) * 1000  / dt;

   actual_velo_left = (radian_left - prv_radian_left)   / (double)(dt*0.001);
   actual_velo_right =  (radian_right - prv_radian_right)  / (double)(dt*0.001);

   getSonar();
   sonarGuided();

   // error_left = desire_speed - actual_velo_left;
   // error_right = desire_speed - actual_velo_right;

   error_left = desire_left_speed - actual_velo_left;
   error_right = desire_right_speed - actual_velo_right;


   volt_left = (Kp1*error_left) + (Ki1*(error_left + prv_error_left))+ (Kd1*(error_left - prv_error_left));


   volt_right = (Kp2*error_right) + (Ki2*(error_right + prv_error_right)) + (Kd2*(error_right - prv_error_right));


   bit_left = (volt_left / 12.0) * 255.0;
   bit_left = constrain(bit_left, 0, 255);
   // if (bit_left > 255.0) { bit_left = 255.0; }
   // else { bit_left = bit_left; }


   bit_right = (volt_right / 12.0) * 255.0;
   bit_right = constrain(bit_right, 0, 255);
   // if (bit_right > 255.0){bit_right = 255.0;}
   // else{bit_right = bit_right;}


   // driveForward(bit_left, bit_right);
   digitalWrite(cw_left, HIGH);
   digitalWrite(ccw_left, LOW);
   analogWrite(pwm_left, bit_left);

   digitalWrite(cw_right, LOW);
   digitalWrite(ccw_right, HIGH);
   analogWrite(pwm_right, bit_right);

   // Without serial the motors don't operate
   // Serial.print("Desire Speed: ");
   // Serial.print(desire_speed);
   // Serial.print(" Left Motor: ");
   // Serial.print(actual_velo_left);
   // Serial.print(" Right Motor: ");
   // Serial.println(actual_velo_right);

   // Serial.print("Desire Speed: ");
   Serial.print(desire_speed);
   Serial.print(" ");
   Serial.print(actual_velo_left);
   Serial.print(" ");
   Serial.println(actual_velo_right);


   prv_time = now_time;

   prv_radian_left = radian_left;
   prv_radian_right = radian_right;

   prv_error_left = error_left;
   // prv_error_right = error_right;

}


void readEncoder1(){
  /* generates counts from the left motor encoder*/

  if(digitalRead(encoderPinA1) == digitalRead(encoderPinB1))
  {
    countLeft = countLeft + 1;
  }
  else
  {
    countLeft = countLeft - 1;
  }
}


void readEncoder2(){
  /* generates counts from the right motor encoder */

  if(digitalRead(encoderPinA2) == digitalRead(encoderPinB2))
  {
    countRight = countRight - 1;
  }
  else
  {
    countRight = countRight + 1;
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


void driveForward(double leftSpeed, double rightSpeed){

  /* drives both motors with the desire speed (without PID)*/

  digitalWrite(cw_left, HIGH);
  digitalWrite(ccw_left, LOW);
  analogWrite(pwm_left, leftSpeed);

  digitalWrite(cw_right, LOW);
  digitalWrite(ccw_right, HIGH);
  analogWrite(pwm_right, rightSpeed);
}
