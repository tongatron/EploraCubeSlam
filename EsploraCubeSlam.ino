/*
Esplora for CubeSlam

game: https://www.cubeslam.com


CubeSlam (https://www.cubeslam.com) game controller sketch for Arduino Esplora.

Play Google CubeSlam (https://www.cubeslam.com) with an Esplora board.
The games runs on browser (preferably Chrome) and uses
left and right arrow on the keyboard to move the bar.
Press SWITCH 3 to switch between three playing modes:                     

mode 0:   JOYSTICK

mode 1:   BUTTONS
          uses the SWITCH 2 (left arrow) and the SWITCH 4 (right arrow)

mode 2:   ACCELEROMETER
          move the board on X Axes to move the bar
                                        
to press space, press: SWITCH 1 + SWITCH 4

Created on 27 Mar 2015
by Giovanni Bindi - giovanni.bindi@gmail.com
This example code is in the public domain.
*/

#include <Esplora.h>
#include <SPI.h>
#include <TFT.h>

unsigned char prevMode = 0;
unsigned char mode = 0;
const int delayJoystick = 50;
const int delayButtons = 50;
int delayAccelerometer = 0;
int joystickXValue = 0;
int accelXValue = 0;

void setup() {
  pinMode(11, OUTPUT);
  Keyboard.begin();
  EsploraTFT.begin();
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.setTextSize(2);
  EsploraTFT.background(255, 0, 0);
  EsploraTFT.text("CUBE SLAM", 10, 10);
  EsploraTFT.text("play mode:", 10, 50);
  EsploraTFT.text("JOYSTICK", 10, 70);
  Esplora.writeRGB(0, 0, 0);
}


void loop() {

  if (!Esplora.readButton(SWITCH_3)) {
    mode++;
    delay(100);
  }

  switch (mode) {

    case 1:
      //Esplora.writeRGB(0, 0, 255);
      if (mode != prevMode) {
        EsploraTFT.background(0, 0, 0);
        EsploraTFT.text("CUBE SLAM", 10, 10);
        EsploraTFT.text("play mode:", 10, 50);
        EsploraTFT.text("BUTTONS", 10, 70);
        prevMode = mode;
      }
      if ((!Esplora.readButton(SWITCH_1)) && (!Esplora.readButton(SWITCH_4)))  pressSpace();
      if (!Esplora.readButton(SWITCH_2)) Left_Arrow(delayButtons);
      if (!Esplora.readButton(SWITCH_4)) Right_Arrow(delayButtons);

      break;

    case 2:
      //Esplora.writeRGB(255, 255, 255);
      if (mode != prevMode) {
        EsploraTFT.background(0, 0, 255);
        EsploraTFT.text("CUBE SLAM", 10, 10);
        EsploraTFT.text("play mode:", 10, 50);
        EsploraTFT.text("ACCELEROMET.", 10, 70);
        prevMode = mode;
      }
      if ((!Esplora.readButton(SWITCH_1)) && (!Esplora.readButton(SWITCH_4)))  pressSpace();
      accelXValue = Esplora.readAccelerometer(X_AXIS);

      Serial.println(accelXValue);

      if (accelXValue > 20) {
        delayAccelerometer = map (accelXValue, 0, 200, 150, 10);
        Left_Arrow(delayAccelerometer);
      }

      if (accelXValue < -20) {
        delayAccelerometer = map (accelXValue, 0, -200, 150, 10);
        Right_Arrow(delayAccelerometer);
      }

      break;

    default:
      mode = 0;
      if (mode != prevMode) {
        EsploraTFT.background(255, 0, 0);
        EsploraTFT.text("CUBE SLAM", 10, 10);
        EsploraTFT.text("play mode:", 10, 50);
        EsploraTFT.text("JOYSTICK", 10, 70);
        prevMode = mode;
      }

      if ((!Esplora.readButton(SWITCH_1)) && (!Esplora.readButton(SWITCH_4)))  pressSpace();

      joystickXValue = Esplora.readJoystickX();
      if (joystickXValue > 500) {
        Left_Arrow(delayJoystick);
      }
      if (joystickXValue < -500) {
        Right_Arrow(delayJoystick);
      }
      break;
  }

}

// ******************************************************************

void pressSpace () {
  Keyboard.press(0x20);
  Esplora.writeRGB(0, 255, 0);
  delay(100);
  Keyboard.releaseAll();
  Esplora.writeRGB(0, 0, 0);
}

void Left_Arrow (int delayX) {
  Keyboard.press(0xD8);
  Esplora.tone(1000, 10);
  Esplora.writeRGB(0, 150, 0);
  if (mode != 2) digitalWrite(11, HIGH);
  delay(delayX);
  Esplora.writeRGB(0, 0, 0);
  Esplora.noTone();
  digitalWrite(11, LOW);
  Keyboard.releaseAll();
}

void Right_Arrow (int delayX) {
  Keyboard.press(0xD7);
  Esplora.tone(1000, 10);
  Esplora.writeRGB(0, 150, 0);
  if (mode != 2) digitalWrite(11, HIGH);
  delay(delayX);
  Esplora.writeRGB(0, 0, 0);
  Esplora.noTone();
  digitalWrite(11, LOW);
  Keyboard.releaseAll();
}
