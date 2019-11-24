void getSonar(){
  /*
    this func gets distance from the three ultrasonic sensors and
    convert it into boolean values based on the distance threshold
  */
  dist_left = sonar[0].ping_cm();
  dist_front = sonar[1].ping_cm();
  dist_right = sonar[2].ping_cm();

  if(dist_left > 6){sonarLeft = 0;}
  else{sonarLeft = 1;}

  if(dist_front > 5){sonarFront = 0;}
  else{sonarFront = 1;}

  if(dist_right > 6){sonarRight = 0;}
  else{sonarRight = 1;}


}


void sonarGuided(){
  /*
    the desire left and right speed are calculated based on
    the left and right wall distance from the robot
  */
  dist_error = dist_left - dist_right;
  sonar_pid = 0.8 * dist_error;

  // left veering scenerio
  if (sonar_pid < 0){
    desire_right_speed = desire_speed - (-1.0*sonar_pid);
    desire_left_speed = desire_speed;
  }
  else if (sonar_pid > 0){
    desire_left_speed = desire_speed - sonar_pid;
    desire_right_speed = desire_speed;
  }
  else if (sonar_pid == 0){
    desire_left_speed = desire_speed;
    desire_right_speed = desire_speed;
  }
}

void displayDist(){
  /*
    display the distances from the ultrasonic sensors
  */
  getSonar();
  Serial.print(dist_left);
  Serial.print(" ");
  Serial.print(dist_front);
  Serial.print(" ");
  Serial.println(dist_right);

}
