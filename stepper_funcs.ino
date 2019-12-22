
void runStepper (float degree, char direct){
  // run the stepper motor 45 degrees for every 1 second
  if ( direct == 'C' ){
    digitalWrite(dir,HIGH);

  }else if ( direct == 'A' ){
    digitalWrite(dir,LOW);
  }

  int steps = 1600*degree/360;

  for (i = 0; i < steps; i++ ){
    digitalWrite(stp,HIGH);
    delay(1);
    digitalWrite(stp,LOW);
    delay(1);
  }
  delay(500);
}

void runServo(){
  // runs the servo motor for dropping mechanism
    myServo.write(30);
    delay(1500);
    myServo.write(98);
    delay(1000);
}
