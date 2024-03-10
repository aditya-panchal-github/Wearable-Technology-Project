#include "SensorData.h"
#include "Sensor.h"

// Declare sensor objects as extern so they can be used in other files
extern HeartRateSensor heartRateSensor;
extern TemperatureSensor temperatureSensor;
extern SoundLevelSensor soundLevelSensor;
extern VibrationSensor vibrationSensor;

//Function to read sensor data and return it
SensorData readSensors() {
  SensorData data;
  data.timestamp = millis();
  data.heartRate = heartRateSensor.read().heartRate; // Read from heart rate sensor
  data.temperature = temperatureSensor.read().temperature; // Read from temperature sensor
  data.soundLevel = soundLevelSensor.read().soundLevel; // Read from sound level sensor
  data.vibration = vibrationSensor.read().vibration; // Read from vibration sensor
  return data;
}


