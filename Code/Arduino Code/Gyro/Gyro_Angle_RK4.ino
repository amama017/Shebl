// Code by: Jody McAdams
// Twitter: @MegaJiXiang
// Website: http://www.jodymcadams.com
// Original code/instructions from: http://bildr.org/2011/06/l3g4200d-arduino/
// License: http://www.opensource.org/licenses/mit-license.php (Go crazy)
// L3G4200D data sheet: http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/DATASHEET/CD00265057.pdf

#include <Wire.h>
#include <MathUtil.h>
#include <Servo.h> 
#include "L3G4200D.h"

//Program init
void setup()
{
  // Initilize Rung Kutta objects
  RK1.Prev = 0;
  RK1.second_Prev = 0;
  RK1.third_Prev = 0;  
  RK1.fourth_Prev = 0;
  
  RK2.Prev = 0;
  RK2.second_Prev = 0;
  RK2.third_Prev = 0;  
  RK2.fourth_Prev = 0;
  
  servo1.attach(9);
  delay(100);
  
  servo2.attach(8);
  delay(100);
  
  Wire.begin();
  Serial.begin(115200);

  L3G4200D_Address = 105;
  Serial.println("starting up L3G4200D ---> address = 105 ...");
  setupL3G4200D(sensorRotationScaleDPS); // Configure L3G4200  - 250, 500 or 2000 deg/sec

  L3G4200D_Address = 104;
  Serial.println("starting up L3G4200D ---> address = 104 ...");
  setupL3G4200D(sensorRotationScaleDPS); // Configure L3G4200  - 250, 500 or 2000 deg/sec
  
  delay(1500); //wait for the sensor to be ready
  Serial.println("L3G4200D started!");
  
  Serial.println("Calibrating...");
  
  lastTimeMS = millis();
  time = millis();
}

//Program loop
void loop()
{
  const float currTimeMS = millis();
  timeElapsed = (currTimeMS-lastTimeMS)/1000.0f;
  lastTimeMS = currTimeMS;
  
  if(millis() - time > sampleTime || isCalibrating)
  {
    time = millis();  // update the time to get the next sample
    
    L3G4200D_Address = 105;
    getGyroValues1();  // This will update x, y, and z with new values
    
    L3G4200D_Address = 104;
    getGyroValues2();  // This will update x, y, and z with new values
    
    if(isCalibrating == true)
      calibrate();
    else {
      spamTimer -= timeElapsed;
      if(spamTimer < 0.0f)
      {
        spamTimer = spamInterval;
        
        Serial.println("Values of sensor1 angles:");
        printValues(angleX1, angleY1, angleZ1);
        
        Serial.println("Values of sensor2 angles:");
        printValues(angleX2, angleY2, angleZ2);
      }
      servo1.write(pos1);
      servo2.write(pos2);      
    }
  }
}

void printValues(float angleX, float angleY, float angleZ) {
    Serial.print("X:");
    Serial.print(angleX);
    Serial.print(", ");
 
    Serial.print("Y:");
    Serial.print(angleY);
    Serial.print(", ");

    Serial.print("Z:");
    Serial.println(angleZ);
}

void calibrate() {
  const float absValX1 = abs(xVal1);
  const float absValY1 = abs(yVal1);
  const float absValZ1 = abs(zVal1);
  //
  const float absValX2 = abs(xVal2);
  const float absValY2 = abs(yVal2);
  const float absValZ2 = abs(zVal2);
  
  
  if(absValX1 > DVoff_X1)
  {
    DVoff_X1 = absValX1;
  }
  
  if(absValY1 > DVoff_Y1)
  {
    DVoff_Y1 = absValY1;
  }
  
  if(absValZ1 > DVoff_Z1)
  {
    DVoff_Z1 = absValZ1;
  }
  //
  if(absValX2 > DVoff_X2)
  {
    DVoff_X2 = absValX2;
  }
  
  if(absValY2 > DVoff_Y2)
  {
    DVoff_Y2 = absValY2;
  }
  
  if(absValZ2 > DVoff_Z2)
  {
    DVoff_Z2 = absValZ2;
  }
  
  calibrationTimer -= timeElapsed;
  
  if(calibrationTimer < 0.0f)
  {
    Serial.println("Calibration complete!");
    
    isCalibrating = false;
    
    //Some fudging to account for the slight
    //amount of movement that slips through
    DVoff_X1 *= DVOffScale;
    DVoff_Y1 *= DVOffScale;
    DVoff_Z1 *= DVOffScale;
    
    DVoff_X2 *= DVOffScale;
    DVoff_Y2 *= DVOffScale;
    DVoff_Z2 *= DVOffScale;    
  }
}

void getGyroValues1()
{
  //Get DPS values from registers
  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  xVal1 = scaleFactor * ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  yVal1 = scaleFactor * ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  zVal1 = scaleFactor * ((zMSB << 8) | zLSB);
  
  if(isCalibrating == false)
  {
      //If the DPS values are less than or equal to the Digital zero-rate levels from
      //the datasheet, set the values to 0
      if(abs(xVal1) <= DVoff_X1)
      {
        xVal1 = 0.0f;
      }
      
      if(abs(yVal1) <= DVoff_Y1)
      {
        yVal1 = 0.0f;
      }
      
      if(abs(zVal1) <= DVoff_Z1)
      {
        zVal1 = 0.0f;
      }
      
      angleZ1 = computeRungeKutta ( &RK1, zVal1) * sampleTime / 1000;
    
      //angleX = WrapAngle(angleX);
      //angleY = WrapAngle(angleY);
      angleZ1 = WrapAngle(angleZ1);
  }  
}
//
void getGyroValues2()
{
  //Get DPS values from registers
  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  xVal2 = scaleFactor * ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  yVal2 = scaleFactor * ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  zVal2 = scaleFactor * ((zMSB << 8) | zLSB);
  
  if(isCalibrating == false)
  {
      //If the DPS values are less than or equal to the Digital zero-rate levels from
      //the datasheet, set the values to 0
      if(abs(xVal2) <= DVoff_X2)
      {
        xVal2 = 0.0f;
      }
      
      if(abs(yVal2) <= DVoff_Y2)
      {
        yVal2 = 0.0f;
      }
      
      if(abs(zVal2) <= DVoff_Z2)
      {
        zVal2 = 0.0f;
      }
      
      angleZ2 = computeRungeKutta ( &RK2, zVal2) * sampleTime / 1000;
    
      //angleX = WrapAngle(angleX);
      //angleY = WrapAngle(angleY);
      angleZ2 = WrapAngle(angleZ2);
  }  
}

int setupL3G4200D(int scale){
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00000000);

  switch(scale)
  {
    case 250:
    {
      writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
      scaleFactor = SoDR_250;
      //DVoff = DVoff_250;
      
      break;
    }
    case 500:
    {
      writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
      scaleFactor = SoDR_500;
      //DVoff = DVoff_500;
      
      break;
    }
    case 2000:
    {
      writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
      scaleFactor = SoDR_2000;
      //DVoff = DVoff_2000;
      
      break;
    }
  }  

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

void writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address){

    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a byte

    while(!Wire.available()) {
        // waiting
    }

    v = Wire.read();
    return v;
}


//If the angle goes beyond 360, wrap it around
float WrapAngle(float angle)
{
  static const float maxAngle = 360.0f;
  
  float finalAngle;
  if(angle > maxAngle)
  {
    return angle - maxAngle;
  }
  else if(angle < -maxAngle)
  {
    return angle + maxAngle;
  }
  else
  {
    return angle;
  }
}
