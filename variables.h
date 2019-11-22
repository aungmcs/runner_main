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

volatile float countLeft, countRight;

// bits produced from pidController()
double bit_left, bit_right;

double prv_error_left, prv_error_right;
double prv_radian_left, prv_radian_right;
double actual_velo_left, actual_velo_right;

// desire speed of the motor in both wheels (rad/s)
const double desire_speed = 15.0;


const double Kp1 = 3.20, Ki1 = 0.0, Kd1 = 0.0;
const double Kp2 = 5.10, Ki2 = 0.0, Kd2 = 0.0;

unsigned long now_time, prv_time, dt;

double angle_left;
double angle_right;

double radian_left;
double radian_right;

double error_left;
double error_right;

double volt_left;
double volt_right;


//--------------------------------------------------------

//ultrasonic pins
#define SONAR_NUM 3
#define MAX_DISTANCE 200

NewPing sonar[SONAR_NUM] = {
  NewPing(34,35,MAX_DISTANCE),//left,
  NewPing(32,33,MAX_DISTANCE),//front,
  NewPing(30,31,MAX_DISTANCE)//right
};

bool sonarLeft, sonarRight, sonarFront;
bool sonarData[] = {0, 0, 0};

//--------------------------------------------------------------

//color sensor at the bottom
// #define S1_B 28
// #define S0_B 29
// #define S3_B 26
// #define S2_B 25
// #define color_base_output 24
//
// int redB = 0;  // red color frequency at the bottom
// int greenB = 0;  // green ||
// int blueB= 0; // blue ||
