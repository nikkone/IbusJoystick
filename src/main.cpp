#include <Arduino.h>
#include <IBusBM.h>
#include <Joystick.h>

#define IBUS_CHANNEL_MIN 1000//0x3E8C       // 
#define IBUS_CHANNEL_MAX 2000//0x7D0C       // 
/*
  Translate iBUS signal to servo - ESP32 version

  Serial1 port RX/TX connected as follows:
  - RX connected to the iBUS servo pin 
  - TX can be left open as the iBUS protocol for servos is one way only

*/


IBusBM IBus;    // IBus object

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,   // hidReportId
  JOYSTICK_TYPE_JOYSTICK,     // joystickType
  3u,                            // buttonCount
  0u,                            // hatSwitchCount
  true,                         // includeXAxis
  true,                         // includeYAxis
  true,                         // includeZAxis
  true,                         // includeRxAxis
  true,                         // includeRyAxis
  true,                         // includeRzAxis
  false,                        // includeRudder
  false,                        // includeThrottle
  true,                        // includeAccelerator
  false,                        // includeBrake
  false                         // includeSteering
);

void setup() {
  //Serial.begin(115200);     // debug info
  Joystick.setXAxisRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  Joystick.setYAxisRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  Joystick.setZAxisRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  //Joystick.setRudderRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  //Joystick.setThrottleRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  Joystick.setAcceleratorRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  //Joystick.setSteeringRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  
  Joystick.setRxAxisRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  Joystick.setRyAxisRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  Joystick.setRzAxisRange(IBUS_CHANNEL_MIN, IBUS_CHANNEL_MAX);
  
  Joystick.begin(false);
  IBus.begin(Serial1,1);    // iBUS object connected to serial2 RX2 pin and use timer 1
}


void loop() {

  // Channel 1 is typically the elevator/pitch
  Joystick.setXAxis(IBus.readChannel(3));
  Joystick.setYAxis(IBus.readChannel(1));
  Joystick.setZAxis(IBus.readChannel(8));
  Joystick.setRxAxis(IBus.readChannel(0));
  Joystick.setRyAxis(IBus.readChannel(2));
  Joystick.setRzAxis(IBus.readChannel(9));
// Channel 3
 Joystick.setAccelerator(IBus.readChannel(4));
 //Joystick.setHatSwitch(0, IBus.readChannel(4));

  // Channel 4 
  switch(IBus.readChannel(5)) {
    case 1000u:
      Joystick.releaseButton(0);
      break;
    case 1500u:
      Joystick.pressButton(0);
      break;
    case 2000u:
      Joystick.pressButton(0);
      break;
    default:
      Joystick.releaseButton(0);
  };
// Channel 5
  switch(IBus.readChannel(6)) {
    case 1000u:
      Joystick.releaseButton(1);
      break;
    case 1500u:
      Joystick.pressButton(1);
      break;
    case 2000u:
      Joystick.pressButton(1);
      break;
    default:
      Joystick.releaseButton(1);
  };
// Channel 6
  switch(IBus.readChannel(7)) {
    case 1000u:
      Joystick.releaseButton(2);
      break;
    case 1500u:
      Joystick.pressButton(2);
      break;
    case 2000u:
      Joystick.pressButton(2);
      break;
    default:
      Joystick.releaseButton(2);
  };
  Joystick.sendState();
  delay(100);
}