#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

struct RungeKutta {
  		float fourth_Prev;
  		float third_Prev;
  		float second_Prev;
  		float Prev;
	};

struct RungeKutta RK1;	
struct RungeKutta RK2;

float computeRungeKutta (struct RungeKutta *rk, float current) {

  rk->Prev = rk->Prev +  0.16667 * ( rk->fourth_Prev + 2*rk->third_Prev + 2*rk->second_Prev + current);

  rk->fourth_Prev = rk->third_Prev;
  rk->third_Prev = rk->second_Prev;
  rk->second_Prev = current;

  return rk->Prev;
}

const int sensorRotationScaleDPS = 250; //(can be 250, 500, or 2000)

//Sensitivity from data sheet in mdps/digit (millidegrees per second) with DPS conversion
const float SoDR_250 = 8.75f/1000.0f;
const float SoDR_500 = 17.50f/1000.0f;
const float SoDR_2000 = 70.0f/1000.0f;

//Digital zero-rate level from data sheet in dps (degrees per second)
/*const float DVoff_250 = 10.0f;
const float DVoff_500 = 15.0f;
const float DVoff_2000 = 75.0f;*/

//Save the scale value that will be used when the program starts
float scaleFactor = 0.0f;

//Digital zero-rate values (calculated from calibration instead of data sheet)
float DVoff_X1 = 0.0f;
float DVoff_Y1 = 0.0f;
float DVoff_Z1 = 0.0f;

float DVoff_X2 = 0.0f;
float DVoff_Y2 = 0.0f;
float DVoff_Z2 = 0.0f;

const float DVOffScale = 1.2f;

int L3G4200D_Address = 105; //I2C address of the L3G4200D

//actual sensor readings
float xVal1 = 0.0f;
float yVal1 = 0.0f;
float zVal1 = 0.0f;

float xVal2 = 0.0f;
float yVal2 = 0.0f;
float zVal2 = 0.0f;

//last time in ms
float lastTimeMS;

//Servo object to control the servo
Servo servo1;
Servo servo2;
const int pos1 = 100;
const int pos2 = 100;

// Timing variables
unsigned long time;
int sampleTime = 10;  // The sampling period of the gyro

// Computed angles
float angleX1 = 0.0f;
float angleY1 = 0.0f;
float angleZ1 = 0.0f;

float angleX2 = 0.0f;
float angleY2 = 0.0f;
float angleZ2 = 0.0f;

float spamTimer = -1.0f;
float spamInterval = 0.0125f; //seconds

float timeElapsed = 0.0f;

bool isCalibrating = true;
float calibrationTimer = 3.0f;
