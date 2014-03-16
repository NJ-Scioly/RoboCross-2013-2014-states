//************************************************************************
//PIN OUTS
//************************************************************************

#define LEFT_MOTOR_PIN 2
#define RIGHT_MOTOR_PIN 3

#define PAN_MOTOR_PIN 4
#define HINGE_1_MOTOR_PIN 5
#define HINGE_2_MOTOR_PIN 6
#define CLAW_MOTOR_PIN 7

//************************************************************************
//OFFSETS/LIMITS
//************************************************************************

#define CENTER 91
#define THROTTLE_MAX  140
#define THROTTLE_MIN 20
const int MS = 91; // angle that stops the motor
const int MCC = 140;
const int MC = 20;


//************************************************************************
//ASSIGN BUTTONS
//************************************************************************

#define DATA_TOGGLE START

#define PAN_LEFT SQUARE 
#define PAN_RIGHT CIRCLE 

#define HINGE_1_UP L1 
#define HINGE_1_DOWN L2 

#define HINGE_2_UP TRIANGLE 
#define HINGE_2_DOWN CROSS

#define OPEN_CLAW R1 
#define CLOSE_CLAW R2 

//************************************************************************
//SERVOS
//************************************************************************

Servo leftMotor;
Servo rightMotor;

Servo panMotor;
Servo hinge1Motor;
Servo hinge2Motor;
Servo clawMotor;

int leftStick = 0;
int rightStick = 0;

int leftOffset = -3;  //These store the trim values for the drive motors
int rightOffset = -3;

//************************************************************************
//LOOP VARIABLES
//************************************************************************

boolean dataToggle = false;

long int currentTime = 0;
long int previousTime = 0;

//************************************************************************
//PS3 CONTROLLER
//************************************************************************

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd); 
