#include <Servo.h>

// define global variables
#define howmanyservos 3                                                                         // constant - how many servos to control from 1 to 48
int pos=150;
// define servos
Servo frontLeftLeg[howmanyservos];
Servo frontRightLeg[howmanyservos];
Servo backLeftLeg[howmanyservos];
Servo backRightLeg[howmanyservos];

//T0 & T1 -> Pos at Inside
//T2 always Outside

void MoveFrontLeftLeg(int T0, int T1, int T2)
{
  //Zero Positions
  //Motor1 (T0) 94 //-ve (Inside), +ve (Outside)
  //Motor2 (T1) 95 //-ve (Inside), +ve (Outside)
  //Motor3 (T2) 137 //+ve (Inside), -ve (Outside)
  frontLeftLeg[0].write(94 - T0);
  frontLeftLeg[1].write(95 - T1);
  frontLeftLeg[2].write(137 - T2);
}

void MoveBackLeftLeg(int T0, int T1, int T2)
{
  //Zero Postions
  //Motor1 (T0) 90 //+ve (Inside), -ve (Outside)
  //Motor2 (T1) 86 //+ve (Inside), -ve (Outside)
  //Motor3 (T2) 31 //-ve (Inside), +ve (Outside)
  backLeftLeg[0].write(90 + T0);
  backLeftLeg[1].write(86 + T1);
  backLeftLeg[2].write(31 + T2);
}

void MoveFrontRightLeg(int T0, int T1, int T2)
{
  //Zero Postions
  //Motor1 (T0) 90 //+ve (Inside), -ve (Outside)
  //Motor2 (T1) 93 //+ve (Inside), -ve (Outside)
  //Motor3 (T2) 30 //-ve (Inside), +ve (Outside)
  frontRightLeg[0].write(90 + T0);
  frontRightLeg[1].write(93 + T1);
  frontRightLeg[2].write(30 + T2);
}

void MoveBackRightLeg(int T0, int T1, int T2)
{
  //Zero Postions
  //Motor1 (T0) 94 //-ve (Inside), +ve (Outside)
  //Motor2 (T1) 85 //-ve (Inside), +ve (Outside)
  //Motor3 (T2) 139 //+ve (Inside), -ve (Outside)
  backRightLeg[0].write(94 - T0);
  backRightLeg[1].write(85 - T1);
  backRightLeg[2].write(139 - T2);
}

void setup()
{
  int pin=2;
  for (int i=0;i<howmanyservos;i++)                                                              // loop to initialize servos and arrays                            
  { 
     frontLeftLeg[i].attach(pin);
     pin+=1;
  }
  for (int i=0;i<howmanyservos;i++)                                                              // loop to initialize servos and arrays                            
  { 
     backLeftLeg[i].attach(pin);     
     pin+=1;
  }
  for (int i=0;i<howmanyservos;i++)                                                              // loop to initialize servos and arrays                            
  { 
     frontRightLeg[i].attach(pin);
      pin+=1;
  }
  for (int i=0;i<howmanyservos;i++)                                                              // loop to initialize servos and arrays                            
  { 
     backRightLeg[i].attach(pin);
     pin+=1;
    }
  
  
  //Zero Positions
  MoveFrontLeftLeg(0,0,0);
  MoveBackLeftLeg(0,0,0);
  MoveFrontRightLeg(0,0,0);
  MoveBackRightLeg(0,0,0);
  delay(25);
}

void loop()
{ 
  ///////////////Set to Initial (Shift Quad)
  MoveFrontLeftLeg(0,23,45);
  MoveBackLeftLeg(0,23,45);
  MoveFrontRightLeg(0,23,45);
  MoveBackRightLeg(0,23,45);
  
  ///////////Leg1///////////////Front Left
  delay(200);
  MoveFrontLeftLeg(0,23+8,45+13);
//  MoveBackLeftLeg(0,23,45);
//  MoveFrontRightLeg(0,23,45);
//  MoveBackRightLeg(0,23,45);
  delay(100);
  MoveFrontLeftLeg(0,23+8-11,45+13-4);
  MoveBackLeftLeg(0,23,45);
  MoveFrontRightLeg(0,23,45);
  MoveBackRightLeg(0,23,45);
  delay(200);
  MoveFrontLeftLeg(0,15,41);
//  MoveBackLeftLeg(0,23,45);
//  MoveFrontRightLeg(0,23,45);
//  MoveBackRightLeg(0,23,45);
  
  //////////////Leg2///////////// Back left
  delay(200);
//  MoveFrontLeftLeg(0,34,42);
  MoveBackLeftLeg(0,31,58);
//  MoveBackRightLeg(0,-7,24);
//  MoveFrontRightLeg(0,35,34);
  delay(100);
  MoveFrontLeftLeg(0,34,42);
  MoveBackLeftLeg(0,38,57);
  MoveBackRightLeg(0,-7,24);
  MoveFrontRightLeg(0,35,34);
  delay(200);
//  MoveFrontLeftLeg(0,34,42);
  MoveBackLeftLeg(0,30,45);
//  MoveBackRightLeg(0,-7,24);
//  MoveFrontRightLeg(0,35,34);
  
  ///////////Leg3///////Back Right
  delay(200);
//  MoveFrontLeftLeg(0,35,31);
//  MoveBackLeftLeg(0,20,44);
  MoveBackRightLeg(0,-3,38);
//  MoveFrontRightLeg(0,30,15);
  delay(100);
  MoveFrontLeftLeg(0,35,31);
  MoveBackLeftLeg(0,20,44);
  MoveBackRightLeg(0,9,48);
  MoveFrontRightLeg(0,30,15);
  delay(200);
//  MoveFrontLeftLeg(0,35,31);
//  MoveBackLeftLeg(0,20,44);
  MoveBackRightLeg(0,5,35);
//  MoveFrontRightLeg(0,30,15);

  ////////////Leg4//////front Right
  delay(200);
//  MoveFrontLeftLeg(0,27,45);
//  MoveBackLeftLeg(0,35,40);
//  MoveBackRightLeg(0,27,45);
  MoveFrontRightLeg(0,44,33);
  delay(100);
  MoveFrontLeftLeg(0,27,45);
  MoveBackLeftLeg(0,35,40);
  MoveBackRightLeg(0,27,45);
  MoveFrontRightLeg(0,47,44);
  delay(200);
//  MoveFrontLeftLeg(0,27,45);
//  MoveBackLeftLeg(0,35,40);
//  MoveBackRightLeg(0,27,45);
  MoveFrontRightLeg(0,35,32);
  
  delay(200);
}


