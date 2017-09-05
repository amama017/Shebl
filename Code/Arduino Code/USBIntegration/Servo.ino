#include <Servo.h>

// define global variables
#define howmanyservos 3                                                                         // constant - how many servos to control from 1 to 48
int pos=150;
int Swing_Leg=0;
int serial_start = 0;
int serial_count = 0;
int Angles[12];
// define servos
Servo frontLeftLeg[howmanyservos];
Servo frontRightLeg[howmanyservos];
Servo backLeftLeg[howmanyservos];
Servo backRightLeg[howmanyservos];

void Get_Serial()
{
  //Initial Handshake  
  while(true)
  {
    if(Serial.available() > 0)
    {
       int c = Serial.read();
       if(c == 251 && serial_start == 0)
       {
         Serial.write(250);
         serial_start = 1;
         break;
       }
       delay(20);
    }
  }
  //Read data
  while(serial_start == 1 && serial_count < 13)
  {
    if(Serial.available() > 0)
    {
      //Get the Swing Leg Number
      if(serial_count == 0)
         Swing_Leg = Serial.read();
      //Get the Angles
      else
        Angles[serial_count-1] = Serial.read() - 25;
       serial_count++;
    }
    else
      delay(20);
  }
  //serial_start = 0;
  serial_count = 0;
}


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
  Serial.begin(57600);
  
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
  //Get the Angles from the Computer
  Get_Serial();
  
  if(Swing_Leg == 1){ //Back Right
    MoveBackRightLeg(0,Angles[0],Angles[1]);
    
    MoveFrontRightLeg(0,Angles[6],Angles[7]); //L2
    MoveBackLeftLeg(0,Angles[8],Angles[9]); //L3
    MoveFrontLeftLeg(0,Angles[10],Angles[11]); //L4
    delay(100);
    
    MoveBackRightLeg(0,Angles[2],Angles[3]); //L1
    delay(200);
    MoveBackRightLeg(0,Angles[4],Angles[5]);
    delay(200);
    
  } else if(Swing_Leg == 2){ //Front Right
    MoveFrontRightLeg(0,Angles[0],Angles[1]);

    MoveBackRightLeg(0,Angles[6],Angles[7]); //L1
    MoveBackLeftLeg(0,Angles[8],Angles[9]); //L3
    MoveFrontLeftLeg(0,Angles[10],Angles[11]); //L4
    delay(100);
    
    MoveFrontRightLeg(0,Angles[2],Angles[3]); //L2
    delay(200);
    MoveFrontRightLeg(0,Angles[4],Angles[5]);
    delay(200);
    
  } else if(Swing_Leg == 3){ //Back Left
    MoveBackLeftLeg(0,Angles[0],Angles[1]);
    
    MoveBackRightLeg(0,Angles[6],Angles[7]); //L1
    MoveFrontRightLeg(0,Angles[8],Angles[9]); //L2
    MoveFrontLeftLeg(0,Angles[10],Angles[11]); //L4
    delay(100);
    
    MoveBackLeftLeg(0,Angles[2],Angles[3]); //L3
    delay(200);
    MoveBackLeftLeg(0,Angles[4],Angles[5]);
    delay(200);
    
  } else if(Swing_Leg == 4){ //Front Left
    MoveFrontLeftLeg(0,Angles[0],Angles[1]);
    
    MoveBackRightLeg(0,Angles[6],Angles[7]); //L1
    MoveFrontRightLeg(0,Angles[8],Angles[9]); //L2
    MoveBackLeftLeg(0,Angles[10],Angles[11]); //L3
    delay(100);
    
    MoveFrontLeftLeg(0,Angles[2],Angles[3]); //L4
    delay(200);
    MoveFrontLeftLeg(0,Angles[4],Angles[5]);
    delay(200);
    
  } else {
    //Error
    return;
  }
  
  //Acknowledge Handshake  
  while(true)
  {
    if(Serial.available() > 0)
    {
       int c = Serial.read();
       if(c == 250 && serial_start == 1)
       {
         Serial.write(251);
         serial_start = 0;
         break;
       }
       delay(20);
    }
  }
}


