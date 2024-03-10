#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H
#include <Arduino.h>

// Made this struct to store the sensor data
struct SensorData {
  unsigned long timestamp;
  int heartRate;
  float temperature;
  int soundLevel;
  int vibration;
  int rawHeartRateSignal; // Added this line just in case it's needed
};


#endif // SENSOR_DATA_H
