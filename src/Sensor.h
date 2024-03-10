#ifndef SENSOR_H
#define SENSOR_H

#include <PulseSensorPlayground.h>
#include "SensorData.h"
#include <math.h>

// Made this class to represent a sensor
class Sensor {
public:
  int pin;
  Sensor(int pin) : pin(pin) {}
  virtual SensorData read() = 0; // Pure virtual function
};

// Subclasses of the Sensor class, 
// these are where the actual sensor readings are taken / processed 
// and returned as SensorData objects

// NOTE: Could still use some work, but it's functional
class HeartRateSensor : public Sensor {
public:
  PulseSensorPlayground pulseSensor;
  unsigned long lastHeartRateReadTime = 0;
  int lastHeartRate = 0;

  HeartRateSensor(int pin) : Sensor(pin) {
    pulseSensor.analogInput(pin);
    pulseSensor.blinkOnPulse(13);
    pulseSensor.setThreshold(750);
    pulseSensor.begin();
  }

  SensorData read() override {
    SensorData data;
    if (millis() - lastHeartRateReadTime >= 1000) {
      if (pulseSensor.sawStartOfBeat()) {
        lastHeartRate = pulseSensor.getBeatsPerMinute();
        lastHeartRateReadTime = millis();
      }
      data.heartRate = lastHeartRate;
    }
    return data;
  }
};

// NOTE: Not finished, still working on this 
class VibrationSensor : public Sensor {
public:
  VibrationSensor(int pin) : Sensor(pin) {}
  SensorData read() override {
    SensorData data;
    return data;
  }
};


// NOTE: Functional, but has to be tested with a reference sensor to calibrate
class TemperatureSensor : public Sensor {
public:
  TemperatureSensor(int pin) : Sensor(pin) {}
  SensorData read() override {
    SensorData data;
    int reading = analogRead(pin);
    float voltage = reading * 5.0 / 1024.0;
    data.temperature = (voltage - 0.5) * 100;
    return data;
  }
};

// NOTE: Functional, but have to test and analyze the readings to calibrate
// as well as to determine the calibration factor
class SoundLevelSensor : public Sensor {
public:
  SoundLevelSensor(int pin) : Sensor(pin) {}

  SensorData read() override {
    SensorData data;

    int average;
    int numReadings = 10;
    int sum = 0;
    for (int i = 0; i < numReadings; i++) {
      sum += analogRead(pin);
      delay(10); // Short delay between readings
    }
    int average = sum / numReadings;

    // This calculation is to Convert the average value to dB using the formula
    float dB = 20 * log10(average);
    float calibrationFactor = 1.0; // Still need to fine tune this
    data.soundLevel = dB * calibrationFactor;

    return data;
  }

};

#endif // SENSOR_H
