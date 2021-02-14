
void move(char decision){
  /*
      output: required bits (volts) to the motors
              bit_right and bit_left in the range of 0 to 255
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
 actual_velo_left = (radian_left - prv_radian_left)   / (double)(dt*0.001);
 actual_velo_right =  (radian_right - prv_radian_right)  / (double)(dt*0.001);


 // returns the desire left and right speed based on (dist_left - dist_right)
 sonarGuided();

 // without ultrasonic help
 if (decision == 'n'){
   error_left = desire_speed - actual_velo_left;
   error_right = desire_speed - actual_velo_right;
 }

 // with ultrasonic help
 else if (decision == 's'){
   error_left = desire_left_speed - actual_velo_left;
   error_right = desire_right_speed - actual_velo_right;

//turnLeft with curvature
 }else if(decision == 't'){
   error_left = 1.0 - actual_velo_left;
   error_right = (1.0 *7.773) - actual_velo_right;
 }



 volt_left = (Kp1*error_left) + (Ki1*(error_left + prv_error_left)) + (Kd1*(error_left - prv_error_left));


 volt_right = (Kp2*error_right) + (Ki2*(error_right + prv_error_right)) + (Kd2*(error_right - prv_error_right));


 bit_left = (volt_left / 12.0) * 255.0;
 bit_left = constrain(bit_left, 0, 255);


 bit_right = (volt_right / 12.0) * 255.0;
 bit_right = constrain(bit_right, 0, 255);


//==================================================================
//     Two 45 degree ultrasonics for reorientating the robot
//==================================================================

if ( dFl > 0.00 && dFl < 6.00 ){
 //reverse right motor dir
 digitalWrite(cw_left, HIGH);
 digitalWrite(ccw_left, LOW);
 digitalWrite (cw_right,HIGH);
 digitalWrite (ccw_right,LOW);

} else if (dFr > 0.00 && dFr < 6.00){
 //reverse left motor dir
 digitalWrite (cw_left,LOW);
 digitalWrite (ccw_left,HIGH);
 digitalWrite(cw_right, LOW);
 digitalWrite(ccw_right, HIGH);


} else if ((dFl > 0.00 && dFl < 6.00) && (dFr > 0.00 && dFr < 6.00)){
  //in dead end
  digitalWrite(cw_left, HIGH);
  digitalWrite(ccw_left, LOW);
  digitalWrite(cw_right, LOW);
  digitalWrite(ccw_right, HIGH);
}
else{
   //straight
  digitalWrite(cw_left, HIGH);
  digitalWrite(ccw_left, LOW);
  digitalWrite(cw_right, LOW);
  digitalWrite(ccw_right, HIGH);

}


if (dF >= 6){

 analogWrite(pwm_left, bit_left);
 analogWrite(pwm_right, bit_right);

} else if (dF < 6){
  analogWrite(pwm_left, 0.00);
  analogWrite(pwm_right, 0.00);

}

//========================================================


 Serial.print(desire_speed);
 Serial.print(" ");
 Serial.print(actual_velo_left);
 Serial.print(" ");
 Serial.println(actual_velo_right);


 prv_time = now_time;

 prv_radian_left = radian_left;
 prv_radian_right = radian_right;

 prv_error_left = error_left;
 prv_error_right = error_right;

}


void turnLeft(){
  //Rotate the robot 90 degrees left from its axis

  // desire angle of the wheels needed to rotate the robot
  desire_angle = 270.0;

  // actual angle of the wheels travelled, retrieved from the encoder
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  // angle error
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.04;
  Kd_left = 0.025;


  Kp_right = 0.04;
  Kd_right = 0.04;

  // (de/dt)
  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  // PID calculation
  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  // motor volt to 8bit conversion
  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;



  leftBit = constrain (leftBit,0,255);
  rightBit = constrain (rightBit,0,255);



  // deciding the direction of both motors based on the angle error
  if ( left_error > 0 ){
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right,HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


prv_left_error = left_error;
prv_right_error = right_error;


}


void turn45(){
  desire_angle = 135.0; //135

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.04;
  Kd_left = 0.025;


  Kp_right = 0.035;
  Kd_right = 0.04;
  //
  // Kp_left = 0.009;
  // Kd_left = 0.07;
  // Ki_left = 0.0001;
  //
  //
  // Kp_right = 0.009;
  // Kd_right = 0.07;
  // Ki_right = 0.0001;




  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);



  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));



  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;



  leftBit = constrain (leftBit,0,255);
  rightBit = constrain (rightBit,0,255);



  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right,HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;


}


void turnRight(){

  desire_angle = 270.0;

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.04; //0.02//0.04
  Kd_left = 0.025;


  Kp_right = 0.04; //0.02//0.04
  Kd_right = 0.04;


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,255);
  rightBit = constrain (rightBit,0,255);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right, LOW);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right,HIGH);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;



}


void go6inches(){
  //moves the robot 6 inches forward

  // desire angle of the wheels needed to move foward 6 inches
  desire_angle = 246.00;

    // actual angle of the wheels travelled, retrieved from the encoder
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  // angle error
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.2;
  Kd_left = 0.0;


  Kp_right = 0.2;
  Kd_right = 0.0;

  // (de/dt)
  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);

  // PID calculation
  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));

  // motor volt to 8bit conversion
  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,50);
  rightBit = constrain (rightBit,0,50);


  // deciding the direction of both motors based on the angle error
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right, HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }

  if (dF >0 && dF < 6.00){
    rightBit = 0;
    leftBit = 0;
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


prv_left_error = left_error;
prv_right_error = right_error;

}


void go5inches(){
  desire_angle = 200.00;    //500

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.06; //0.026
  Kd_left = 0.0; //0.0


  Kp_right = 0.06; //0.026
  Kd_right = 0.0; //0.0


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,50);
  rightBit = constrain (rightBit,0,50);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right, HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;
}


void go2inches(){
  desire_angle = 82.00;    //500

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.03; //0.026
  Kd_left = 0.0; //0.0


  Kp_right = 0.03; //0.026
  Kd_right = 0.0; //0.0


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,50);
  rightBit = constrain (rightBit,0,50);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right, HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;
}


void go4inches(){
  desire_angle = 164.00;    //500

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.05; //0.026
  Kd_left = 0.0; //0.0


  Kp_right = 0.05; //0.026
  Kd_right = 0.0; //0.0


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,50);
  rightBit = constrain (rightBit,0,50);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right, HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;
}


void go1feet(){
  desire_angle = 492.00;    //500

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.9; //0.026
  Kd_left = 0.0; //0.0


  Kp_right = 0.9; //0.026
  Kd_right = 0.0; //0.0


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,50);
  rightBit = constrain (rightBit,0,50);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right, HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;

}


void stop(){
  desire_angle = 0.00;    //500

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.07; //0.026
  Kd_left = 0.0; //0.0


  Kp_right = 0.07; //0.026
  Kd_right = 0.0; //0.0


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,50);
  rightBit = constrain (rightBit,0,50);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right, HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }



Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;
}


void go7inches(){
  desire_angle = 289.00; // 289

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.25; //0.071 // 0.25
  Kd_left = 0.0;


  Kp_right = 0.25; //0.25
  Kd_right = 0.0;


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,50);
  rightBit = constrain (rightBit,0,50);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    analogWrite (pwm_left,leftBit);
  }

  if ( right_error > 0 ){
    digitalWrite (cw_right,LOW);
    digitalWrite (ccw_right, HIGH);
    analogWrite (pwm_right,rightBit);
  }else{
    digitalWrite (cw_right,HIGH);
    digitalWrite (ccw_right,LOW);
    analogWrite (pwm_right,rightBit);
  }

  if (dF >0 && dF < 6.00){
    rightBit = 0;
    leftBit = 0;
  }


Serial.print (left_error);
Serial.print(" ");
Serial.print (Kd_left *( left_diff_error ));
Serial.print(" ");
Serial.println(right_error);


// Serial.print (angle_left);
// Serial.print(" ");
// Serial.print (Kd_left *( left_diff_error ));
// Serial.print(" ");
// Serial.println(angle_right);

prv_left_error = left_error;
prv_right_error = right_error;
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


void resetCounts(){
  //reset the encoder counts
  countLeft = 0.0;
  countRight = 0.0;
}


void followLeft(){
// left wall following maze solving alogrithm

  getSonar();

  // straight motion
  if((sonarLeft == true && sonarRight == true) || (sonarLeft == true && sonarRight == false)){
      start_turn = false;
      move('s');

  }

//-------------------------------

  // time to turn left
  if (sonarLeft == false){
    start_turn = true;
  }

  if (start_turn == true){
      resetCounts();
      for (int r = 0; r < 70; r++){
        go6inches();
      }
      resetCounts();
      for (int r = 0; r < 70; r++){
        turnLeft();
      }
      resetCounts();
      for (int r = 0; r < 70; r++){
        go7inches();
      }
      start_turn = false;
  }

//-----------------------------------

  // time to turn right
  if (sonarLeft == true && dF < 6.00)
  {
    resetCounts();
    for (int r = 0; r < 70; r++){
      stop();
      }
    delay(500);
    resetCounts();
    for (int r = 0; r < 70; r++){
      turnRight();
      }
  }
}


void followRight(){
  // right wall following alogrithm

  getSonar();

  // straight motion between walls
  if((sonarLeft == true && sonarRight == true) || (sonarRight == true && sonarLeft == false)){
      // straight = true;
      start_turn = false;
      move('s');

  }

//-------------------------------

  // time to trun right
  if (sonarRight == false){
    start_turn = true;
  }

  if (start_turn == true){
      resetCounts();
      for (int r = 0; r < 80; r++){
        go6inches();
      }
      resetCounts();
      for (int r = 0; r < 80; r++){
        turnRight();
      }
      resetCounts();
      for (int r = 0; r < 80; r++){
        go7inches();
      }
      start_turn = false;
  }

//-----------------------------------

  // time to turn left
  if (sonarRight == true && dF < 6.00)
  {
    for (int r = 0; r < 70; r++){
      stop();
      }
    delay(500);
    resetCounts();
    for (int r = 0; r < 80; r++){
      turnLeft();
      }
  }
}


void perLeft() {
  getSonar();
  baseRGB();

  if (color_Output < 5){
    colorDetected = true;

  }else{
    colorDetected = false;
  }

  // left turn scenerio
  if (colorDetected == true && turncomplete == true){
    resetCounts();
    for (int r = 0; r < 5; r++){
      stop();
    }
    for (int r = 0; r < 2; r++){
      runStepper(45,'A');
    }
    runServo();

    // colorDetected = false;
  }

  // right turn scenerio
  // if (straightColor == true && turncomplete == true){
  //   resetCounts();
  //   for (int r = 0; r < 70; r++){
  //     stop();
  //   }
  //   for (int r = 0; r < 7; r++){
  //     runStepper(45,'A');
  //   }
  //   runServo();
  //
  //   right_turn_done = true;
  //   // turncomplete = false;
  //   straightColor = false;
  // }

  if (color_Output == 5 && straightColor == true){
    resetCounts();
    for (int r = 0; r < 5; r++){
      stop();
    }
    for (int r = 0; r < 1; r++){
      runStepper(45,'A');
    }
    runServo();
    straightColor = false;

  }

  if((sonarLeft == true && sonarRight == true) || (sonarLeft == true && sonarRight == false)){
    if (colorDetected == true){
      straightColor = true;

    }
    turncomplete = false;
    start_turn = false;
    move('s');

  }

  //-------------------------------

  if (sonarLeft == false){
    turncomplete = false;
    start_turn = true;
  }

  if (start_turn == true){
      resetCounts();
      for (int r = 0; r < 70; r++){
        go6inches();
      }
      resetCounts();
      for (int r = 0; r < 70; r++){
        turnLeft();
      }
      resetCounts();
      for (int r = 0; r < 70; r++){
        go7inches();
      }
      turncomplete = true;
      start_turn = false;
  }

  //-----------------------------------

  if (sonarLeft == true && dF < 6.00)
  {
    // right_turn_done = false;
    resetCounts();
    for (int r = 0; r < 5; r++){
      stop();
      }
    delay(200);
    resetCounts();
    for (int r = 0; r < 70; r++){
      turnRight();
      }

    // turncomplete = true;
  }

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


}


void leftie(){
  // left wall following maze alogrithm with urban facility assisstant feature

  getSonar();

  // retrieve color data from the base of the robot
  baseRGB();

  if (color_Output < 5){
    colorDetected = true;

  }else if(color_Output >=5 && color_Output < 8){
    colorDetected = false;
  }


  //===================================================================//
  //=======   Checking the colored cubes dropping scenerio  ===========//
  //===================================================================//

  // dropping in left turn scenerio
  if (colorDetected == true && turncomplete == true){
    resetCounts();
    for (int r = 0; r < 3; r++){
      stop();
    }
    colorCheck();

  }

  //dropping while straight motion scenerio
  if (color_Output == 5 && straightColor == true){
    resetCounts();
    for (int r = 0; r < 3; r++){
      stop();
    }
    colorCheck();
    straightColor = false;

  }

  //===============================================================//
  //==========    Maze Solving Robot Motion =======================//
  //===============================================================//

  // straight motion
  if((sonarLeft == true && sonarRight == true) || (sonarRight == false && sonarLeft == true)){
    if (colorDetected == true){
      straightColor = true;
    }

    turncomplete = false;
    start_turn = false;
    move('s');

  }

  //-------------------------------

  // left turn
  if (sonarLeft == false){
    turncomplete = false;
    start_turn = true;
  }

  if (start_turn == true){
    resetCounts();
    for (int r = 0; r < 70; r++){
      go6inches();
    }
    resetCounts();
    for (int r = 0; r < 70; r++){
      turnLeft();
    }
    resetCounts();
    for (int r = 0; r < 70; r++){
      go7inches();
    }
    turncomplete = true;
    start_turn = false;
  }

  //-----------------------------------

  // right turn
  if (sonarLeft == true && dF < 6.00)
  {
    resetCounts();
    for (int r = 0; r < 3; r++){
      stop();
      }
    delay(200);//////////////////////
    resetCounts();
    for (int r = 0; r < 70; r++){
      turnRight();
      }
  }
  //-------------------------------------
  //end point
  if (black == true){
    resetCounts();
    for (int r = 0; r < 3; r++){
      stop();
    }
    resetCounts();
    for (int r = 0; r < 70; r++){
      go2inches();
    }
    while(1);
  }
}


void rightie(){
  // right wall following algorithm with cube dropping alogrithm
  // check leftie for proper information and comments

  getSonar();
  baseRGB();

  if (color_Output < 5){
    colorDetected = true;

  }else if(color_Output >=5 && color_Output < 8){
    colorDetected = false;
  }
  //-------------------------------------------------------------------
  // left turn scenerio
  if (colorDetected == true && turncomplete == true){
    resetCounts();
    for (int r = 0; r < 3; r++){
      stop();
    }
    colorCheck();

  }

  //straight scenerio
  if (color_Output == 5 && straightColor == true){
    resetCounts();
    for (int r = 0; r < 3; r++){
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
    for (int r = 0; r < 3; r++){
      stop();
      }
    delay(200);//////////////////////
    resetCounts();
    for (int r = 0; r < 70; r++){
      turnLeft();
      }
  }
  //-------------------------------------
  //end point
  if (black == true){
    resetCounts();
    for (int r = 0; r < 3; r++){
      stop();
    }
    resetCounts();
    for (int r = 0; r < 70; r++){
      go2inches();
    }
    while(1);
  }
}


void perRight(){
  getSonar();
  baseRGB();

  if (color_Output < 5){
    colorDetected = true;

  }else{
    colorDetected = false;
  }

  // left turn scenerio
  if (colorDetected == true && turncomplete == true){
    resetCounts();
    for (int r = 0; r < 5; r++){
      stop();
    }
    for (int r = 0; r < 1; r++){
      runStepper(45,'A');
    }
    runServo();

    // colorDetected = false;
  }

  // right turn scenerio
  // if (straightColor == true && turncomplete == true){
  //   resetCounts();
  //   for (int r = 0; r < 70; r++){
  //     stop();
  //   }
  //   for (int r = 0; r < 7; r++){
  //     runStepper(45,'A');
  //   }
  //   runServo();
  //
  //   right_turn_done = true;
  //   // turncomplete = false;
  //   straightColor = false;
  // }

  if (color_Output == 5 && straightColor == true){
    resetCounts();
    for (int r = 0; r < 5; r++){
      stop();
    }
    for (int r = 0; r < 1; r++){
      runStepper(45,'A');
    }
    runServo();
    straightColor = false;

  }

  if((sonarLeft == true && sonarRight == true) || (sonarRight == true && sonarLeft == false)){
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
    // right_turn_done = false;
    resetCounts();
    for (int r = 0; r < 5; r++){
      stop();
      }
    delay(200);
    resetCounts();
    for (int r = 0; r < 70; r++){
      turnLeft();
      }

    // turncomplete = true;
  }

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
}

//---------------------Upper Mechanism Control------------------------//

void runStepper (float degree, char direct) //Run 45 degrees turns every 1 second
{
  if ( direct == 'C' )
  {
    digitalWrite(dir,HIGH);
  }
  else if ( direct == 'A' )
  {
    digitalWrite(dir,LOW);
  }

  int steps = 1600*degree/360;

  for (i = 0; i < steps; i++ ){
    digitalWrite(stp,HIGH);
    delay(1);
    digitalWrite(stp,LOW);
    delay(1);
  }
  delay(1000);
}

void runServo(){
    myServo.write(30);
    delay(2000);
    myServo.write(98);
}
