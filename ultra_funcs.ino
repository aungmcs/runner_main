void getSonar(){
  /*
    this func gets distance from the three ultrasonic sensors and
    convert it into boolean values based on the distance threshold
  */
  unsigned int dist_left = sonar[0].ping_cm();
  unsigned int dist_front = sonar[1].ping_cm();
  unsigned int dist_right = sonar[2].ping_cm();

  if(dist_left >= 1 && dist_left <= 3){sonarLeft = 1;}
  else{sonarLeft = 0;}

  if(dist_front >= 1 && dist_front <= 3){sonarFront = 1;}
  else{sonarFront = 0;}

  if(dist_right >= 1 && dist_right <= 3){sonarRight = 1;}
  else{sonarRight = 0;}

  sonarData = {sonarLeft, sonarFront, sonarRight};
}
