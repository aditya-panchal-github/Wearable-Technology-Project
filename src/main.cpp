/***********************************************************************************************
 * Project: Wearable Technology for Elderly Healthcare Monitoring
 * File: main.cpp
 * Description: This file contains the main code for the wearable technology project.
 * Version: 0.1.0
 * Date: March 9, 2024
 * Authors: Aditya, Juan, Conner
 * Course(s): Physics II, Engineering Design and Problem Solving, Technical Communication
 **********************************************************************************************/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <PulseSensorPlayground.h>
#include <math.h>
#include "SensorData.h"
#include "SerialDataSender.h"
#include <LiquidCrystal.h>
#include "Display.h"
#include "Sensor.h"
#include <FastLED.h>

#define USE_ARDUINO_INTERRUPTS true 
#define BUTTON_PIN 6
#define BUZZER_PIN 10
#define RGB_PIN_RED 8
#define RGB_PIN_GREEN 9 
#define RGB_PIN_BLUE 13

int colors[15][3] = {
  {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, // Red, Green, Blue
  {255, 255, 0}, {0, 255, 255}, {255, 0, 255}, // Yellow, Cyan, Magenta
  {255, 255, 255}, {128, 0, 0}, {0, 128, 0}, // White, Dark Red, Dark Green
  {0, 0, 128}, {128, 128, 0}, {0, 128, 128}, // Dark Blue, Olive, Teal
  {128, 0, 128}, {128, 128, 128}, {0, 0, 0} // Purple, Gray, Black
};
unsigned long lastSoundReadTime = 0;
unsigned long soundReadInterval = 10; // Read every 10 milliseconds
int displayMode = 1;

SerialDataSender dataSender;
CRGB color;
PulseSensorPlayground pulseSensor;
HeartRateSensor heartRateSensor(0);
TemperatureSensor temperatureSensor(4);
SoundLevelSensor soundLevelSensor(2);
VibrationSensor vibrationSensor(7);


void setup() {
  Serial.begin(115200);
  dataSender.setEnabled(true);
  setupDisplay();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RGB_PIN_RED, OUTPUT);
  pinMode(RGB_PIN_GREEN, OUTPUT);
  pinMode(RGB_PIN_BLUE, OUTPUT);

}



void loop() {

  if (digitalRead(BUTTON_PIN) == HIGH) {
    // Toggle display view
    if (displayMode == 1) {
      displayMode = 2;
    } else {
      displayMode = 1;
    }
  }

  SensorData data;
  data.heartRate = heartRateSensor.read().heartRate;
  data.temperature = temperatureSensor.read().temperature;
  data.soundLevel = soundLevelSensor.read().soundLevel;
  data.vibration = vibrationSensor.read().vibration;
  dataSender.send(data);
  displayData(data);

}

