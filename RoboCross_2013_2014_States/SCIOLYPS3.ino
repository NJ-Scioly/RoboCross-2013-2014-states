#include <PS3BT.h>                                                    //Include the necessary libraries.
#include <Servo.h>
#include "Def.h"

// Constant servo actions
const int MS = 91; // angle that stops the motor
const int MCC = 140;
const int MC = 20;

void setup() {
  // Serial and Bluetooth communication
  Serial.begin(115200);                                              
  if (Usb.Init() == -1) {                                            
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));              

  // Pin modes
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  
  pinMode(HINGE_1_PIN, OUTPUT);
  pinMode(HINGE_2_PIN, OUTPUT);
  
  pinMode(CLAW_PIN, OUTPUT);
  pinMode(PAN_PIN, OUTPUT);
  
  // Attach motors
  rightMotor1.attach(RIGHT_MOTOR_PIN);
  rightMotor2.attach(RIGHT_MOTOR_PIN);
  
  leftMotor1.attach(LEFT_MOTOR_PIN);
  leftMotor2.attach(LEFT_MOTOR_PIN);
  
  hinge1.attach(HINGE_1_PIN);
  hinge2.attach(HINGE_2_PIN);
  
  claw.attach(CLAW_PIN);
  pan.attach(PAN_PIN);
}

/** Writes angle to all right motors*/
void writeToRight(int angle) {
  rightMotor1.write(angle);
  rightMotor2.write(angle);  
}

/** Writes angle to all left motors*/
void writeToLeft(int angle) {
  leftMotor1.write(angle);
  leftMotor2.write(angle);  
}

void stopMotors() {
 writeToLeft(MS); 
 writeToRight(MS);
}


void loop() {
  Usb.Task();

  if(PS3.PS3Connected || PS3.PS3NavigationConnected) {
    writeToRight(map(PS3.getAnalogHat(RightHatY), 0, 255, MCC, MC));
    writeToLeft(map(PS3.getAnalogHat(LeftHatY), 0, 255, MC, MCC));
    
    if(PS3.getButtonClick(OPEN_CLAW)) {
      claw.write(MCC);
    } else if (PS3.getButtonClick(CLOSE_CLAW)) {
      claw.write(MC);
    } else {
      claw.write(MS); 
    }
    
    if(PS3.getButtonClick(HINGE_1_UP)) {
      hinge1.write(MCC); 
    } else if (PS3.getButtonClick(HINGE_1_DOWN)) {
      hinge1.write(MC);
    } else {
      claw.write(MS); 
    }
    
    if(PS3.getButtonClick(HINGE_2_UP)) {
      hinge2.write(MCC); 
    } else if (PS3.getButtonClick(HINGE_2_DOWN)) {
      hinge2.write(MC);
    } else {
      claw.write(MS); 
    }
    
    if(PS3.getButtonClick(PAN_LEFT)) {
      pan.write(MCC); 
    } else if (PS3.getButtonClick(PAN_RIGHT)) {
      pan.write(MC);
    } else {
      claw.write(MS); 
    }
    
  } else {
    stopMotors();
  }
    
  if(PS3.getButtonClick(PS)) {
    PS3.disconnect();
  }
}

