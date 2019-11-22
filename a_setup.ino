void setup(){

 Serial.begin(9600);
 // motor pins
 pinMode(pwm_left,OUTPUT);
 pinMode(cw_left,OUTPUT); //MOTOR1
 pinMode(ccw_left,OUTPUT);

 pinMode(pwm_right,OUTPUT);
 pinMode(cw_right,OUTPUT); //MOTOR2
 pinMode(ccw_right,OUTPUT);

 pinMode(encoderPinA1,INPUT);
 pinMode(encoderPinB1,INPUT);

 pinMode(encoderPinA2,INPUT);
 pinMode(encoderPinB2,INPUT);

 attachInterrupt(digitalPinToInterrupt(encoderPinA1), readEncoder1, CHANGE);
 attachInterrupt(digitalPinToInterrupt(encoderPinA2), readEncoder2, CHANGE);

//-----------------------------------------------------------------------

//ultrasonic --> not needed
//--------------------------------------------------------------------

// //bottom color sensor  pins
// pinMode(S0_B, OUTPUT);
// pinMode(S1_B, OUTPUT);
// pinMode(S2_B, OUTPUT);
// pinMode(S3_B, OUTPUT);
//
// // Setting the sensorOut as an input
// pinMode(color_base_output, INPUT);
// // Setting frequency scaling to 20%
// digitalWrite(S0_B,HIGH);
// digitalWrite(S1_B,LOW);

}
