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
const double desire_speed = 10.0;
double desire_left_speed, desire_right_speed;


const double Kp1 = 3.80, Ki1 = 0.0, Kd1 = 0.0;
const double Kp2 = 3.80, Ki2 = 0.0, Kd2 = 0.0;

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
double Kp_left, Kd_left;
double Kp_right, Kd_right;
double leftMotorVolt, rightMotorVolt, leftBit, rightBit;

unsigned long start_timer;
bool turnComplete = false;

bool shouldTurn = false;
bool realTurn = false;


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

double dist_left;
double dist_front;
double dist_right;
double dist_error;
double sonar_pid;
bool sonar_help;

//--------------------------------------------------------------

//color sensor at the bottom
#define S0_B 53
#define S1_B 52
#define S2_B 51
#define S3_B 50
#define color_base_output 49

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

int color_Output = 5;

//color sensor at the top
// #define S0_T 47
// #define S1_T 46
// #define S2_T 45
// #define S3_T 44
// #define color_top_output 48

// int redFrequencyT = 0;
// int greenFrequencyT = 0;
// int blueFrequencyT = 0;
//
// int redColorT = 0;
// int greenColorT = 0;
// int blueColorT = 0;

int color_OutputT = 5;
//------------------------------------------------

//compass
#define HMC5883L_Address 0x1E

/* Register address for the X Y and Z data */
#define X 3
#define Y 7
#define Z 5

float x,y;
int actual_heading;
int desire_heading;
int heading_error;

//-------------------Stepper----------------------//
#define stp 36
#define dir 37
#define ms0 38
#define ms1 39
#define ms2 40

int i;
