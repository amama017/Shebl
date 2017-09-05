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
  
  frontLeftLeg[0].write(94); //-ve (Inside), +ve (Outside)
  frontLeftLeg[1].write(95); //-ve (Inside), +ve (Outside)
  frontLeftLeg[2].write(90); //+ve (Inside), -ve (Outside)
  delay(25);
  backLeftLeg[0].write(90); //+ve (Inside), -ve (Outside)
  backLeftLeg[1].write(86); //+ve (Inside), -ve (Outside)
  backLeftLeg[2].write(94); //-ve (Inside), +ve (Outside)
  delay(25);
  frontRightLeg[0].write(90); //+ve (Inside), -ve (Outside)
  frontRightLeg[1].write(93); //+ve (Inside), -ve (Outside)
  frontRightLeg[2].write(84); //-ve (Inside), +ve (Outside)
  delay(25);
  backRightLeg[0].write(94); //-ve (Inside), +ve (Outside)
  backRightLeg[1].write(85); //-ve (Inside), +ve (Outside)
  backRightLeg[2].write(92); //+ve (Inside), -ve (Outside)
  delay(25);
}

void loop()
{
  
}

