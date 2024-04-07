#include "SerialDataSender.h"

SerialDataSender::SerialDataSender() : enabled(true) {}

// Send the sensor data to the serial port, and make compatible with the serial monitor extension
//teleplot syntax
void SerialDataSender::send(const SensorData& data) 
{
  if (enabled) 
  {

    Serial.print(">heartRate:");
    Serial.println(data.heartRate);

    Serial.print(">temperature:");
    Serial.println(data.temperature);

    Serial.print(">soundLevel:");
    Serial.println(data.soundLevel);

    Serial.print(">vibration:");
    Serial.println(data.vibration);
  }

}

// Option to enable or disable the serial data sender
void SerialDataSender::setEnabled(bool enabled) 
{
  this->enabled = enabled;
}