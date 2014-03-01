//************************************************************************
//PIN OUTS
//************************************************************************

#define LEFT_MOTOR_PIN 2
#define RIGHT_MOTOR_PIN 3

#define HINGE_1_PIN 5
#define PAN_PIN 6

#define HINGE_2_PIN 9
#define CLAW_PIN 10

//************************************************************************
//ASSIGN BUTTONS
//************************************************************************

#define HINGE_1_UP L1 
#define HINGE_1_DOWN L2 

#define HINGE_2_UP R1 
#define HINGE_2_DOWN R2 

#define PAN_LEFT SQUARE 
#define PAN_RIGHT CIRCLE 

#define OPEN_CLAW TRIANGLE 
#define CLOSE_CLAW CROSS 

//************************************************************************
//SERVOS
//************************************************************************

Servo rightMotor1;
Servo rightMotor2;

Servo leftMotor1;
Servo leftMotor2;

Servo hinge1;
Servo hinge2;

Servo pan;
Servo claw;

//************************************************************************
//PS3 CONTROLLER
//************************************************************************

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd); 


