void getSonar(){
  /*
    this func gets distance from the five ultrasonic sensors and
    convert it into boolean values based on the distance threshold
  */
  dL = sonar[0].ping_cm(); // left distance
  dF = sonar[1].ping_cm(); // front distance
  dR = sonar[2].ping_cm(); // right distance
  dFr = sonar[3].ping_cm(); // front right
  dFl = sonar[4].ping_cm(); // front left


//--------------------------------------------
// sensor values filtration and walls detection
//----------------------------------------------

// left
  if(dL > 0.00 && dL < 10.00){
    sonarLeft = true; // left wall detected
    dist_left = dL;

  }else if (dL >= 10.00){
    sonarLeft = false;
    dist_left = 0.00;
  }

//---------------

// front left
  if(dFl > 0.00 && dFl < 10.00){
    dist_frontLeft = dFl;

  }else if (dL >= 10.00){
    dist_frontLeft = dFl;
  }

//--------------

// front
  if(dF > 0.00 && dF <= 6.00){
    sonarFront = true;
    dist_front = dF; // front wall detected

  }else if (dF > 6.00){
    sonarFront = false;
    dist_front = dF;
  }

//----------------

// front right
  if(dFr > 0.00 && dFr < 10.00){
    dist_frontRight = dFr;

  }else if (dFr >= 10.00){
    dist_frontRight = dFr;
  }

//---------------

// right
  if(dR > 0.00 && dR < 8.00){
    sonarRight = true; // right wall detected
    dist_right = dR;

  }else if(dR >= 8.00){
    sonarRight = false;
    dist_right = 0.00;
  }

}


void sonarGuided(){
  /*
    the desire left and right speeds are calculated based on
    the left and right wall distance from the robot
  */
  dist_error = dist_left - dist_right;

  if(sonarLeft == true && sonarRight == true){
    desire_dist_error = 0.0;

  }
  if(sonarLeft == false && sonarRight == true){
    desire_dist_error = -3.0;

  }
  if(sonarLeft == true && sonarRight == false){
    desire_dist_error = 3.0;
  }


  error_diff = desire_dist_error - dist_error;
  sonar_pid = (0.9 * error_diff) + (0.1* (error_diff - prv_error_diff)) ; // 4.0 oscillates alot



  // left veering scenerio
  if (sonar_pid < 0){
    desire_left_speed = desire_speed - (-1.0*sonar_pid);
    desire_right_speed = desire_speed;


  // right veering scenerio
  }else if (sonar_pid > 0){
    desire_right_speed = desire_speed - sonar_pid;
    desire_left_speed = desire_speed;


  // robot in the center scenerio
  }else if(sonar_pid == 0){
    desire_right_speed = desire_speed;
    desire_left_speed = desire_speed;
  }


  prv_error_diff = error_diff;
}


void sonarGuided2(){
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

  }else if (sonar_pid > 0){
    desire_left_speed = desire_speed - sonar_pid;
    desire_right_speed = desire_speed;

  }else if (sonar_pid == 0){
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
  Serial.print(dFl);
  Serial.print(" ");
  Serial.print(dist_front);
  Serial.print(" ");
  Serial.print(dFr);
  Serial.print(" ");
  Serial.println(dist_right);

}
