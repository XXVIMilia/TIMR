/*Code adapted from Scott Fitzgerald's servo "Sweep" example, modified by John Bennett to work with ESP32s. (found in the arduino examples menu) 
  Code by Thingiverse user Tokyo_Bird's "Arduino controlled 2-joint 8-servo 4-legged Walking Robot" (https://www.thingiverse.com/thing:4905975/files)
  has also been modified to suit this project. Without their work this part of this project would have not been possible. 
  At least not within the 72 hr window of a Hackathon.
*/

#include <ESP32Servo.h>
//Define all servo legs, format for servo name is "servo<Front/Back><Left/Right><Tibia/Femur>" - Tibia being lower leg and Femur being upper leg
//So the Front Right Tibia would be called "servoFRT"
// 16 (17?) servo objects can be created on the ESP32
Servo FRT;
Servo FRF;
Servo FLT;
Servo FLF;
Servo BLT;
Servo BLF;
Servo BRT;
Servo BRF;

// Asign each servo to the pin number it is attatched to
int servoFRT = 32;
int servoFRF = 33;
int servoFLT = 25;
int servoFLF = 26;
int servoBLT = 27;
int servoBLF = 14;
int servoBRT = 12;
int servoBRF = 13;

int FRFOffset = 120;
int FRTOffset = 15;
int FLFOffset = 60;
int FLTOffset = 165;
int BLFOffset = 100;
int BLTOffset = 165;
int BRFOffset = 70;
int BRTOffset = 15;

//Misc. variables
int test = 0;          // Flag for whether the self test/servo center routine has been run
bool idleMode = true;  // Flag for if the hand tracker is not being used and the robot is in "idle demo mode"

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  FRT.setPeriodHertz(50);  // standard 50 hz servo
  FRF.setPeriodHertz(50);
  FLT.setPeriodHertz(50);
  FLF.setPeriodHertz(50);
  BLT.setPeriodHertz(50);
  BLF.setPeriodHertz(50);
  BRT.setPeriodHertz(50);
  BRF.setPeriodHertz(50);

  // attaches the all servos to their respective pins using default min/max of 1000us and 2000us
  // different servos may require different min/max settings for an accurate 0 to 180 sweep
  FRT.attach(servoFRT);
  FRF.attach(servoFRF);
  FLT.attach(servoFLT);
  FLF.attach(servoFLF);
  BLT.attach(servoBLT);
  BLF.attach(servoBLF);
  BRT.attach(servoBRT);
  BRF.attach(servoBRF);

  pinMode(2, OUTPUT);  // Internal LED for diagnostic purposes
}


void loop() {
  if (test == 0) {     // Self test
    centerServos();
    test = 1;
    idle(random(1, 10));
  }

// While in Idle Mode, do a bunch of random actions
  while (idleMode == true) {
    switch (random(1, 12)) {
      case (1):
        idle(random(1, 10));
        break;
      case 2:
        leftTurn(random(1, 11));
        break;
      case 3:
        rightTurn(random(1, 11));
        break;
      case 4:
        wave(random(2, 6));
        break;
      case 5:
        bounce(random(1, 6));
        break;
      case 6:
        stand(random(1, 11));
        break;
      case 7:
        sit(random(1, 11));
        break;
      case 8:
        randomBeep(random(1, 15));
        break;
      default:
        forward(random(1, 11));
        idle(random(1, 10));
        break;
    }
    idle(random(1, 10));
  }
}

// Self test function
void centerServos() {

  // Flash light on ESP32 to warn user that initialization is starting
  for (int i = 4; i > 0; i--) {
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }

  // Final warning and delay
  digitalWrite(2, HIGH);
  delay(2000);
  digitalWrite(2, LOW);
  delay(2000);

  // Center all servos
  FRT.write(90);
  FRF.write(90);
  FLT.write(90);
  FLF.write(90);
  BLT.write(90);
  BLF.write(90);
  BRT.write(90);
  BRF.write(90);
  delay(1000);

  //Flash lights indicating servo centering is done
  for (int i = 5; i > 0; i--) {
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(100);
  }

  //Short delay after centering
  delay(2000);
}


void idle(unsigned int idleMultiplier) {
  delay(200 * idleMultiplier);
}


int fowardDelay = 200;
void forward(unsigned int step) {
  while (step-- > 0) {
    FRT.write(FRTOffset + 30);
    BLT.write(BLTOffset + 30);
    delay(fowardDelay);
    FRF.write(FRFOffset + 30);
    BRF.write(BRFOffset - 30);
    FLF.write(FLFOffset);
    BLF.write(BLFOffset);
    delay(fowardDelay);
    FRT.write(FRTOffset);
    BLT.write(BLTOffset);
    delay(100);

    FLT.write(FLTOffset - 30);
    BRT.write(BRTOffset - 30);
    delay(fowardDelay);
    FRF.write(FRFOffset);
    BRF.write(BRFOffset);
    FLF.write(FLFOffset - 30);
    BLF.write(BLFOffset + 30);
    delay(fowardDelay);
    FLT.write(FLTOffset);
    BRT.write(BRTOffset);
    delay(100);
  }
}

int rightDelay = 200;
void rightTurn(unsigned int step) {
  while (step-- > 0) {
    FLT.write(FLTOffset - 30);
    BRT.write(BRTOffset - 30);
    delay(rightDelay);
    FRF.write(FRFOffset + 30);
    BRF.write(BRFOffset - 30);
    FLF.write(FLFOffset - 30);
    BLF.write(BLFOffset + 30);
    delay(rightDelay);
    FLT.write(FLTOffset);
    BRT.write(BRTOffset);
    delay(100);

    FRT.write(FRTOffset + 30);
    BLT.write(BLTOffset + 30);
    delay(rightDelay);
    FRF.write(FRFOffset);
    BRF.write(BRFOffset);
    FLF.write(FLFOffset);
    BLF.write(BLFOffset);
    delay(rightDelay);
    FRT.write(FRTOffset);
    BLT.write(BLTOffset);
    delay(100);
  }
}

int leftDelay = 200;
void leftTurn(unsigned int step) {
  while (step-- > 0) {
    FRT.write(FRTOffset + 30);
    BLT.write(BLTOffset + 30);
    delay(leftDelay);
    FRF.write(FRFOffset + 30);
    BRF.write(BRFOffset - 30);
    FLF.write(FLFOffset - 30);
    BLF.write(BLFOffset + 30);
    delay(leftDelay);
    FRT.write(FRTOffset);
    FLT.write(FLTOffset);
    delay(100);

    FLT.write(FLTOffset - 30);
    BRT.write(BRTOffset - 30);
    delay(leftDelay);
    FRF.write(FRFOffset);
    BRF.write(BRFOffset);
    FLF.write(FLFOffset);
    BLF.write(BLFOffset);
    delay(leftDelay);
    FLT.write(FLTOffset);
    BRT.write(BRTOffset);
    delay(100);
  }
}
int waveDelay = 300;
void wave(unsigned int step) {
  stand(0);
  BRT.write(BRTOffset - 30);

  while (step-- > 0) {
    FLT.write(30);
    FLF.write(FLFOffset + 60);
    delay(waveDelay);
    FLF.write(FLFOffset - 60);
    delay(waveDelay);
  }
}

int bounceDelay = 300;
void bounce(unsigned int step) {
  while (step-- > 0) {
    sit(0);
    delay(bounceDelay);
    stand(0);
    delay(bounceDelay);
  }
}

void sit(unsigned int wait) {
  FRF.write(FRFOffset + 15);
  FRT.write(FRTOffset + 50);
  FLF.write(FLFOffset - 15);
  FLT.write(FLTOffset - 55);
  BLF.write(BLFOffset + 35);
  BLT.write(BLTOffset - 85);
  BRF.write(BRFOffset - 25);
  BRT.write(BRTOffset + 95);
  delay(wait * 200);
}

void stand(unsigned int wait) {
  FRF.write(FRFOffset);
  FRT.write(FRTOffset);
  FLF.write(FLFOffset);
  FLT.write(FLTOffset);
  BLF.write(BLFOffset);
  BLT.write(BLTOffset);
  BRF.write(BRFOffset);
  BRT.write(BRTOffset);
  delay(wait * 200);
}

void randomBeep(unsigned int beeps) {
  tone(23, random(100, 6000), random(50, 300));
}