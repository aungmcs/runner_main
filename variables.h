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
const double desire_speed = 8.00;
double desire_left_speed, desire_right_speed;


const double Kp1 = 3.80, Ki1 = 0.00, Kd1 = 0.00;
const double Kp2 = 3.80, Ki2 = 0.00, Kd2 = 0.00;

unsigned long now_time, prv_time, dt;

double angle_left;
double angle_right;

double radian_left;
double radian_right;

double error_left;
double error_right;

double volt_left;
double volt_right;
//----------//
// 90 turn
double desire_angle;
double left_error, right_error, left_diff_error, right_diff_error;
double prv_left_error, prv_right_error;
double Kp_left, Kd_left, Ki_left;
double Kp_right, Kd_right, Ki_right;
double leftMotorVolt, rightMotorVolt, leftBit, rightBit;

unsigned long time_now, prvTm;
bool turncomplete = false;
bool start_turn = false;

bool shouldTurn = false;
bool realTurn = false;


//--------------------------------------------------------

//ultrasonic pins
#define SONAR_NUM 5
#define MAX_DISTANCE 200
#define PING_INTERVAL 33
// ping interval 33ms
NewPing sonar[SONAR_NUM] = {
  NewPing(29,28,MAX_DISTANCE),//left,
  NewPing(43,42,MAX_DISTANCE),//front,
  NewPing(53,52,MAX_DISTANCE),//right
  NewPing(15,14,MAX_DISTANCE),//front right
  NewPing(31,30,MAX_DISTANCE)//front left
};

bool sonarLeft, sonarRight, sonarFront;

double dFl, dFr, prv_dFr;
double dist_frontLeft, dist_frontRight;

double dist_left;
double dist_front;
double dist_right;
double dist_error;
double desire_dist_error;
double sonar_pid;
double error_diff, prv_error_diff;
bool sonar_help;
double dL, dR, dF;
double prv_dR, prv_dL, prv_dF;

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

//------------------------------------------------

//compass
// #define HMC5883L_Address 0x1E
//
// /* Register address for the X Y and Z data */
// #define X 3
// #define Y 7
// #define Z 5
//
// float x,y;
// int actual_heading;
// int desire_heading;
// int heading_error;
