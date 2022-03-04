/*  3-100-MKR1010_RGB_LED
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
 *  - Adafruit_BME280.h
 *  - U8g2lib.h
 *  - WiFiNINA.h
 *  - utility/wifi_drv.h
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

// U8g2 - Version: Latest
#include <U8g2lib.h>

// Adafruit BME280 Library - Version: Latest
#include <Adafruit_BME280.h>

// arduino-timer - Version: Latest
#include <arduino-timer.h>

#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

/*
  Sketch generated by the Arduino IoT Cloud Thing "MKR1010 with OLED v2"
  https://create.arduino.cc/cloud/things/1ddbc18f-5e83-43b5-ab77-2a33177b5da6

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float humidity;
  float pressure;
  float temperature;
  int led_pwd;
  int pot;
  CloudSchedule timer;
  bool button;
  bool led_on_off;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

auto sensor_timer = timer_create_default(); // create a timer with default settings

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

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
  pinMode(5,OUTPUT); // Set the LED pin as an output
  pinMode(0,INPUT_PULLUP);
  WiFiDrv::pinMode(25, OUTPUT); //define green pin
  WiFiDrv::pinMode(26, OUTPUT); //define red pin
  WiFiDrv::pinMode(27, OUTPUT); //define blue pin

  unsigned status;
  status = bme.begin(0x76);
  if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }

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

  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB18_tf);
  u8g2.drawStr(0, 30,"Starting...");
  u8g2.sendBuffer();

  sensor_timer.every(500, get_button_pot_state);
  sensor_timer.every(5000, get_sensor_readings);
}

void loop() {
  ArduinoCloud.update();
  // Your code here
  sensor_timer.tick(); // tick the timer

  if (timer.isActive()){
    WiFiDrv::analogWrite(25, 255); // turn on Green LED in RGB
    WiFiDrv::analogWrite(26, 0); // turn off Red LED in RGB
    WiFiDrv::analogWrite(27, 0); // turn off Blue LED in RGB
  } else
  {
    WiFiDrv::analogWrite(25, 0); // turn off Green LED in RGB
    WiFiDrv::analogWrite(26, 0); // turn off Red LED in RGB
    WiFiDrv::analogWrite(27, 255); // turn on Blue LED in RGB
  }

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
    Serial.print("Pot: ");
    Serial.println(pot);

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");
    temperature = bme.readTemperature(); // This will update the dashboard widget

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    pressure = bme.readPressure() / 100.0F; // This will update the dashboard widget

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    humidity = bme.readHumidity(); // This will update the dashboard widget


    Serial.println();
    update_oled();
}

/*
  Since Button is READ_WRITE variable, onButtonChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onButtonChange()  {
  // Add your code here to act upon Button change
}

/*
  Since LedPwd is READ_WRITE variable, onLedPwdChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedPwdChange()  {
  // Add your code here to act upon LedPwd change
  analogWrite(5, led_pwd);
  Serial.println(led_pwd);
}

/*
  Since Pot is READ_WRITE variable, onPotChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPotChange()  {
  // Add your code here to act upon Pot change
}

/*
  Since Humidity is READ_WRITE variable, onHumidityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHumidityChange()  {
  // Add your code here to act upon Humidity change
}

/*
  Since Pressure is READ_WRITE variable, onPressureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPressureChange()  {
  // Add your code here to act upon Pressure change
}

/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}

void update_oled()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_luRS10_tf);
  u8g2.setFontPosTop();

  u8g2.setCursor(1, 5);
  u8g2.print(String(temperature) + (char)176 + "C");

  u8g2.setCursor(85, 25);
  u8g2.print(String(humidity,1) + "%");  // Round humidity float to 1 decimal so it fits.

  u8g2.setCursor(1, 45);
  u8g2.print(pot);

  u8g2.setCursor(1, 25);
  u8g2.print(String(pressure) + "hPa");

  u8g2.setCursor(110, 5);
    if (button)
      u8g2.print("O");
    else
      u8g2.print("|");

  u8g2.setCursor(40, 45);
  u8g2.print(message_one);

  u8g2.sendBuffer();
}

/*
  Since Timer is READ_WRITE variable, onTimerChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTimerChange()  {
  // Add your code here to act upon Timer change
}