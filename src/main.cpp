/***
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
#define USE_ARDUINO_INTERRUPTS true 
#define BUTTON_PIN 6
#define BUZZER_PIN 10

SerialDataSender dataSender;

PulseSensorPlayground pulseSensor;
HeartRateSensor heartRateSensor(0);
TemperatureSensor temperatureSensor(4);
SoundLevelSensor soundLevelSensor(A2);
VibrationSensor vibrationSensor(7);


void setup() {
  Serial.begin(9600);
  dataSender.setEnabled(true);
  setupDisplay();
  pinMode(BUTTON_PIN, INPUT_PULLUP);

}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    tone(BUZZER_PIN, 4000); 
  } else {
    noTone(BUZZER_PIN); 
  }

  SensorData data;
  data.heartRate = heartRateSensor.read().heartRate;
  data.temperature = temperatureSensor.read().temperature;
  data.soundLevel = soundLevelSensor.read().soundLevel;
  data.vibration = vibrationSensor.read().vibration;
  dataSender.send(data);
  displayData(data);

  delay(10); 

}

