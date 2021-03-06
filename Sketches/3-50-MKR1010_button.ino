/*  3-50-MKR1010_button
 *
 *
 *
 * Components
 * ----------
 *  - MKR1010
 *  - 1.3" OLED I2C SH1106
 *  - BME280 I2C
 *  - Button
 *  - Potentiometer
 *  - LED
 *
 *  Libraries
 *  ---------
 *  - arduino-timer.h
 *
 * Connections
 * -----------
 *
 * See https://github.com/futureshocked/arduino_iot_cloud/blob/main/Wiring%20Schematics/Arduino%20MKR1010%20experiment.png
 *
 *
 *
 *  Created on March 4 2022 by Peter Dalmaris
 *
 */

// arduino-timer - Version: Latest
#include <arduino-timer.h>

/*
  Sketch generated by the Arduino IoT Cloud Thing "MKR1010 with OLED v2"
  https://create.arduino.cc/cloud/things/1ddbc18f-5e83-43b5-ab77-2a33177b5da6

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  bool button;
  bool led_on_off;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"

auto sensor_timer = timer_create_default(); // create a timer with default settings

bool get_button_pot_state(void *) {
  pot = analogRead(6);
  button = digitalRead(0);
  printValues();
  return true; // repeat? true
}

bool get_sensor_readings(void *) {
  printValues();
  return true; // repeat? true
}

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  pinMode(6,OUTPUT); // Set the LED pin as an output
  pinMode(0,INPUT_PULLUP);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  sensor_timer.every(500, get_button_pot_state);
  sensor_timer.every(5000, get_sensor_readings);
}

void loop() {
  ArduinoCloud.update();
  // Your code here
  sensor_timer.tick(); // tick the timer

}

/*
  Since LedOnOff is READ_WRITE variable, onLedOnOffChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedOnOffChange()  {
  // Add your code here to act upon LedOnOff change
  if (led_on_off){
    digitalWrite(6, HIGH);
    Serial.println("Button ON");
  } else
  {
    digitalWrite(6, LOW);
    Serial.println("Button OFF");
  }
}

void printValues() {
    Serial.print("Button: ");
    Serial.println(button);

    Serial.println();
}

/*
  Since Button is READ_WRITE variable, onButtonChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onButtonChange()  {
  // Add your code here to act upon Button change
}
