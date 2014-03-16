
#include <PS3BT.h>                                                           
#include <Servo.h>
#include "Def.h"


//**************************************************************************************************************************************************************************************************************
//SETUP
//**************************************************************************************************************************************************************************************************************

void setup() 
{
  //************************************************************************
  //SERIAL COMMUNICATION INITIALIZATION
  //************************************************************************
    
  Serial.begin(115200);  
  Serial1.begin(115200); 
  
  //************************************************************************
  //PS3 LIBRARY INITIALIZATION
  //************************************************************************
   
  if (Usb.Init() == -1) 
  {                                            
    Serial.print(F("\r\nOSC did not start"));
    Serial1.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  Serial1.print(F("\r\nPS3 Bluetooth Library Started"));

  //************************************************************************
  //SERVO DEFINITIONS
  //************************************************************************  
  
  leftMotor.attach(LEFT_MOTOR_PIN);
  rightMotor.attach(RIGHT_MOTOR_PIN);
  
  panMotor.attach(PAN_MOTOR_PIN);
  hinge1Motor.attach(HINGE_1_MOTOR_PIN);
  hinge2Motor.attach(HINGE_2_MOTOR_PIN);
  clawMotor.attach(CLAW_MOTOR_PIN);
  
} //END void setup()

//**************************************************************************************************************************************************************************************************************
//MAIN LOOP
//**************************************************************************************************************************************************************************************************************

void loop() 
{
  
  //************************************************************************
  //LOOP TIMING
  //************************************************************************
  
  currentTime = millis();
  
  //************************************************************************
  //REFRESH PS3 CONTROLLER DATA
  //************************************************************************
  
  Usb.Task();
  
  //************************************************************************************************************************************************
  //IF PS3 CONTROLLER IS CONNECTED
  //************************************************************************************************************************************************
  
  if(PS3.PS3Connected || PS3.PS3NavigationConnected) 
  {    
    
    //************************************************************************
    //DRIVE
    //************************************************************************
      leftStick = map(PS3.getAnalogHat(LeftHatY), 0, 255, THROTTLE_MAX, THROTTLE_MIN);
      rightStick = map(PS3.getAnalogHat(RightHatY), 0, 255, THROTTLE_MIN, THROTTLE_MAX); 
      if(PS3.getButtonClick(UP)) 
      {
        leftOffset = leftOffset + 1;
      }
      if(PS3.getButtonClick(DOWN)) 
      {
        leftOffset = leftOffset - 1;
      }
      if(PS3.getButtonClick(RIGHT)) 
      {
        rightOffset = rightOffset + 1;
      }
      if(PS3.getButtonClick(LEFT)) 
      {
        rightOffset = rightOffset - 1;
      }
      leftMotor.write(leftStick + leftOffset);
      rightMotor.write(rightStick + rightOffset);
    
    //************************************************************************
    //PAN
    //************************************************************************
      if(PS3.getButtonPress(PAN_RIGHT)) 
      {
        panMotor.write(MCC);
        
        if(dataToggle){
         Serial.println("Panning right!");
        }
        
      }else
      
      if(PS3.getButtonPress(PAN_LEFT)) 
      {
        panMotor.write(MC);
        if(dataToggle){
         Serial.println("Panning left!");
         }
      }
      
      else{
        panMotor.write(MS);
      }   
      
    //************************************************************************
    //HINGE 1
    //************************************************************************
      if(PS3.getButtonPress(HINGE_1_UP)) 
      {
        hinge1Motor.write(MCC);
        
        if(dataToggle){
         Serial.println("Hinge 1 going up!");
        }
        
      }else
      
      if(PS3.getButtonPress(HINGE_1_DOWN)) 
      {
        hinge1Motor.write(MC);
        if(dataToggle){
         Serial.println("Hinge 1 going down!");
         }
      }
      
      else{
        hinge1Motor.write(MS);
      }        
    //************************************************************************
    //HINGE 2
    //************************************************************************
      if(PS3.getButtonPress(HINGE_2_UP)) 
      {
        hinge2Motor.write(MCC);
        
        if(dataToggle){
         Serial.println("Hinge 2 going up!");
        }
        
      }else
      
      if(PS3.getButtonPress(HINGE_2_DOWN)) 
      {
        hinge2Motor.write(MC);
        if(dataToggle){
         Serial.println("Hinge 2 going down!");
         }
      }
      
      else{
        hinge2Motor.write(MS);
      }               
      
    //************************************************************************
    //CLAW
    //************************************************************************
    
      if(PS3.getButtonPress(OPEN_CLAW)) 
      {
        clawMotor.write(MCC);
        
        if(dataToggle){
         Serial.println("Claw opening");
        }
        
      }else
      
      if(PS3.getButtonPress(CLOSE_CLAW)) 
      {
        clawMotor.write(MC);
        if(dataToggle){
         Serial.println("Claw closing!");
         }
      }
      
      else{
        clawMotor.write(MS);
      }               
      
   
    //************************************************************************
    //PS3 CONTROLLER STATUS
    //************************************************************************
   
    if(PS3.getButtonClick(SELECT)) {
      Serial.print(F("\r\nSelect - ")); 
      //Serial.println(PS3.getStatusString());
      Serial1.print(F("\r\nSelect - ")); 
      //Serial1.println(PS3.getStatusString());      
    }
    
    //************************************************************************
    //PS3 CONTROLLER DISCONNECT SEQUENCE
    //************************************************************************
    
    if(PS3.getButtonClick(PS)) {
      PS3.disconnect();
    }
     
   
    //************************************************************************
    //DATA TOGGLE
    //************************************************************************
    
    if(PS3.getButtonClick(DATA_TOGGLE))
    {
      dataToggle = !dataToggle;
    }
    
    //************************************************************************
    //DATA CODE
    //************************************************************************
    
    if(dataToggle)
    {     
      //************************************************************************
      //DRIVING PRINTOUT
      //************************************************************************
      
         Serial.print("Left: ");
         Serial.print(leftStick + leftOffset);
         Serial.print("\t");
         Serial.print("Right: ");
         Serial.print(rightStick + rightOffset);
         Serial1.print("Left: ");
         Serial1.print(leftStick + leftOffset);
         Serial1.print("\t");
         Serial1.print("Right: ");
         Serial1.print(rightStick + rightOffset);
       
    } //END dataToggle
    
  } //END PS3.PS3Connected || PS3.PS3NavigationConnected
  
  //************************************************************************************************************************************************
  //IF PS3 CONTROLLER IS NOT CONNECTED
  //************************************************************************************************************************************************
  
  else
   {
    leftMotor.write(CENTER);
    rightMotor.write(CENTER);
    }
   
   if(dataToggle)
   {
     Serial.print("\t");
     Serial.print("Loop time: ");
     Serial.println(millis() - currentTime);
     Serial1.print("\t");
     Serial1.print("Loop time: ");
     Serial1.println(millis() - currentTime);
   }
   
} //END void loop()
