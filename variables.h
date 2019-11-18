// PIN DECLARATION
//-------------------------
// dc motor pins
#define pwm_left 5
#define cw_left 7
#define ccw_left 8

#define pwm_right 6
#define cw_right 4
#define ccw_right 9

#define encoderPinA1 18
#define encoderPinB1 22
#define encoderPinA2 19
#define encoderPinB2 23
//-----------------------------------------

// ultrasonic pins
#define SONAR_NUM 3
#define MAX_DISTANCE 200


//------------------------------------------------------
//------------------------------------------------------

// VARIABLES
//----------
// motor
volatile float countLeft, countRight;

// bits produced from pidController()
int bit_left, bit_right;

float prv_error_left, prv_error_right;
float prv_radian_left, prv_radian_right;
float actual_velo_left, actual_velo_right;

// desire speed of the motor in both wheels (rad/s)
float desire_speed = 10.0;

unsigned long now_time, prv_time;
//------------------------------------------------------

//ultrasonic sensor
NewPing sonar[SONAR_NUM] = {
  NewPing(,,MAX_DISTANCE),
  NewPing(,,MAX_DISTANCE),
  NewPing(,,MAX_DISTANCE)
};

bool sonarLeft, sonarRight, sonarFront;
bool sonarData[] = {0, 0, 0};
