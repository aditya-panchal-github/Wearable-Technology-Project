#ifndef SERIAL_DATA_SENDER_H
#define SERIAL_DATA_SENDER_H
#include "SensorData.h"

// A class to send sensor data to the serial port, 
//and make compatible with the serial monitor extension
class SerialDataSender {
public:
  SerialDataSender();
  void send(const SensorData& data);
  void setEnabled(bool enabled);
private:
  bool enabled;
};

#endif // SERIAL_DATA_SENDER_H
