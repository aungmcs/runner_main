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

 attachInterrupt(digitalPinToInterrupt(18), readEncoder1 ,CHANGE);
 attachInterrupt(digitalPinToInterrupt(19), readEncoder2 ,CHANGE);

//ultrasonic --> not needed

}
