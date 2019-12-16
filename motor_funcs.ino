
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

 if (decision == 'n'){// no sonar help
   error_left = desire_speed - actual_velo_left;
   error_right = desire_speed - actual_velo_right;
 }

 else if (decision == 's'){// with sonar help
   error_left = desire_left_speed - actual_velo_left;
   error_right = desire_right_speed - actual_velo_right;

 }else if(decision == 't'){//turnLeft with curvature
   error_left = 1.0 - actual_velo_left;
   error_right = (1.0 *7.773) - actual_velo_right; //curve radius 4
 }



 volt_left = (Kp1*error_left) + (Ki1*(error_left + prv_error_left)) + (Kd1*(error_left - prv_error_left));


 volt_right = (Kp2*error_right) + (Ki2*(error_right + prv_error_right)) + (Kd2*(error_right - prv_error_right));


 bit_left = (volt_left / 12.0) * 255.0;
 bit_left = constrain(bit_left, 0, 255);


 bit_right = (volt_right / 12.0) * 255.0;
 bit_right = constrain(bit_right, 0, 255);


//=========================================================
//             45 degree ultrasonics come in
//=========================================================

if ( dist_frontLeft > 0.00 && dist_frontLeft < 6.00 ){
 //reverse right motor dir
 digitalWrite(cw_left, HIGH);
 digitalWrite(ccw_left, LOW);
 digitalWrite (cw_right,HIGH);
 digitalWrite (ccw_right,LOW);

} else if (dist_frontRight > 0.00 && dist_frontRight < 6.00){
 //reverse left motor dir
 digitalWrite (cw_left,LOW);
 digitalWrite (ccw_left,HIGH);
 digitalWrite(cw_right, LOW);
 digitalWrite(ccw_right, HIGH);


} else if ((dist_frontLeft > 0.00 && dist_frontLeft < 6.00) && (dist_frontRight > 0.00 && dist_frontRight < 6.00)){
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

 // digitalWrite(cw_left, HIGH);
 // digitalWrite(ccw_left, LOW);
 // analogWrite(pwm_left, bit_left);

 // digitalWrite(cw_right, LOW);
 // digitalWrite(ccw_right, HIGH);
 // analogWrite(pwm_right, bit_right);

//-----------------------------------

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

  desire_angle = 270.0;

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.04; //0.02
  Kd_left = 0.025;


  Kp_right = 0.04; //0.02
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


  Kp_left = 0.04; //0.02
  Kd_left = 0.025;


  Kp_right = 0.04; //0.02
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


void rockerTurn(){

  now_time = millis();


   // from count to angle of the rotation of the wheels
  angle_left = (360.0/660.0) * countLeft; //check both speeds again.
  angle_right = (360.0/660.0) * countRight;

  desire_left_speed = 2.0;
  desire_right_speed = desire_left_speed * 6.1;

  // from degree to radian conversion
  radian_left = angle_left * (PI/180.0);
  radian_right = angle_right * (PI/180.0);


  dt = now_time - prv_time; // dt is fine


  // angular velocity = d(angle) / dt --> unit = rad/s
  actual_velo_left = (radian_left - prv_radian_left)   / (double)(dt*0.001);
  actual_velo_right =  (radian_right - prv_radian_right)  / (double)(dt*0.001);


  error_left = desire_left_speed - actual_velo_left;
  error_right = desire_right_speed - actual_velo_right;

  volt_left = (Kp1*error_left) +
              (Ki1*(error_left + prv_error_left))+
              (Kd1*(error_left - prv_error_left));


  volt_right = (Kp2*error_right) +
               (Ki2*(error_right + prv_error_right)) +
               (Kd2*(error_right - prv_error_right));


  bit_left = (volt_left / 12.0) * 255.0;
  bit_left = constrain(bit_left, 0, 255);


  bit_right = (volt_right / 12.0) * 255.0;
  bit_right = constrain(bit_right, 0, 255);

 // digitalWrite(cw_left, HIGH);
 // digitalWrite(ccw_left, LOW);
 // analogWrite(pwm_left, bit_left);
 //
 // digitalWrite(cw_right, LOW);
 // digitalWrite(ccw_right, HIGH);
 // analogWrite(pwm_right, bit_right);


//=========================================================
//                45 guys come in
//=========================================================

 if ( dist_frontLeft > 0.00 && dist_frontLeft < 7.00 ){
  //reverse right motor dir
  digitalWrite(cw_left, HIGH);
  digitalWrite(ccw_left, LOW);
  digitalWrite (cw_right,HIGH);
  digitalWrite (ccw_right,LOW);
  analogWrite(pwm_left, bit_left);
  analogWrite(pwm_right, bit_right - 7.00);

}else if (dist_frontRight > 0.00 && dist_frontRight < 7.00 ){
    //reverse left motor dir
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left,HIGH);
    digitalWrite(cw_right, LOW);
    digitalWrite(ccw_right, HIGH);
    analogWrite(pwm_left, bit_left);
    analogWrite(pwm_right, bit_right);


  } else{
    //straight
   digitalWrite(cw_left, HIGH);
   digitalWrite(ccw_left, LOW);
   digitalWrite(cw_right, LOW);
   digitalWrite(ccw_right, HIGH);
   analogWrite(pwm_left, bit_left);
   analogWrite(pwm_right, bit_right);

  }


//
//   if (sonarFront == false){
//
//   analogWrite(pwm_left, bit_left);
//   analogWrite(pwm_right, bit_right);
//
//  } else if (sonarFront == true){
//    analogWrite(pwm_left, 0.00);
//    analogWrite(pwm_right, 0.00);
// }

//========================================================

  // digitalWrite(cw_left, HIGH);
  // digitalWrite(ccw_left, LOW);
  // analogWrite(pwm_left, bit_left);

  // digitalWrite(cw_right, LOW);
  // digitalWrite(ccw_right, HIGH);
  // analogWrite(pwm_right, bit_right);

//-----------------------------------

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


void go12cm(){

  desire_angle =270.0;  //240 //110

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.02;
  Kd_left = 0.025;


  Kp_right = 0.02;
  Kd_right = 0.04;


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,200);
  rightBit = constrain (rightBit,0,200);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left, HIGH);
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


void go10cm(){

  desire_angle =220.0;  //240 //110

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.02;
  Kd_left = 0.025;


  Kp_right = 0.02;
  Kd_right = 0.04;


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,200);
  rightBit = constrain (rightBit,0,200);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left, HIGH);
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


void go1cm(){
  desire_angle =50.0;  //240 //110

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.09;
  Kd_left = 0.0;


  Kp_right = 0.09;
  Kd_right = 0.00;


  left_diff_error = (left_error - prv_left_error);
  right_diff_error = (right_error - prv_right_error);


  leftMotorVolt = (Kp_left * left_error) + (Kd_left * left_diff_error) + (Ki_left * (left_error + prv_left_error));
  rightMotorVolt = (Kp_right * right_error) + (Kd_right * right_diff_error) + (Ki_right * (right_error + prv_right_error));


  leftBit = (abs(leftMotorVolt) / 12.0) * 255;
  rightBit = (abs(rightMotorVolt) / 12.0)* 255;


  leftBit = constrain (leftBit,0,200);
  rightBit = constrain (rightBit,0,200);


  //Turn both motors to position
  if ( left_error > 0 ){
    digitalWrite (cw_left,HIGH);
    digitalWrite (ccw_left,LOW);
    analogWrite (pwm_left,leftBit);
  }else{
    digitalWrite (cw_left,LOW);
    digitalWrite (ccw_left, HIGH);
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


void go6inches(){
  desire_angle = 246.00;    //500

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


void go7inches(){
  desire_angle = 289.00;

  //Angle Travelled
  angle_left = (360.0/660.0) * abs( countLeft );
  angle_right = (360.0/660.0) * abs ( countRight );


  //PID Calculations for left and right motors
  left_error = desire_angle - angle_left;
  right_error = desire_angle - angle_right;


  Kp_left = 0.071;
  Kd_left = 0.0;


  Kp_right = 0.071;
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
  countLeft = 0.0;
  countRight = 0.0;
}


void stop(){
  digitalWrite(cw_left, LOW);
  digitalWrite(ccw_left, HIGH);
  analogWrite(pwm_left, 10);

  digitalWrite(cw_right, HIGH);
  digitalWrite(ccw_right, LOW);
  analogWrite(pwm_right, 10);

}

void turns45(){
  // // 45 turns
  // /*
  //   // if (start_turn== true){
  //   //   resetCounts();
  //   //   for (int r = 0; r < 120; r++){
  //   //     go1cm();
  //   //   }
  //   //
  //   //   resetCounts();
  //   //   for (int r = 0; r < 120; r++){
  //   //     turn45();
  //   //   }
  //   //   resetCounts();
  //   //   for (int r = 0; r < 120; r++){
  //   //     go10cm();
  //   //   }
  //   //   //----------------
  //   //   resetCounts();
  //   //   for (int r = 0; r < 120; r++){
  //   //     turn45();
  //   //   }
  //   //   resetCounts();
  //   //   for (int r = 0; r < 120; r++){
  //   //     go10cm();
  //   //   }
  //
  //     //-----------------------
  //     // resetCounts();
  //     // for (int r = 0; r < 120; r++){
  //     //   turn45();
  //     // }
  //     // resetCounts();
  //     // for (int r = 0; r < 120; r++){
  //     //   go10cm();
  //     // }
  //     // //-----------------------
  //     // resetCounts();
  //     // for (int r = 0; r < 120; r++){
  //     //   turn45();
  //     // }
  //     // resetCounts();
  //     // for (int r = 0; r < 120; r++){
  //     //   go12cm();
  //     // }
  //   //   start_turn = false;
  //   // }
  // */
}

void solveMaze(){

  getSonar();

  if((sonarLeft == true && sonarRight == true) || (sonarLeft == true && sonarRight == false)){
      // straight = true;
      start_turn = false;
      move('s');

  }

//-------------------------------

  if (sonarLeft == false){
    start_turn = true;
  }

  if (start_turn == true){
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
      start_turn = false;
  }

//-----------------------------------

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
  }
}
