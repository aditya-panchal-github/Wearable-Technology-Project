#ifndef DISPLAY_H
#define DISPLAY_H
#include <LiquidCrystal.h>
#include "SensorData.h"

extern LiquidCrystal lcd;

void setupDisplay();
void displayData(const SensorData& data);

#endif // DISPLAY_H
