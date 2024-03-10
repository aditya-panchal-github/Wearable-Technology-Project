#include <LiquidCrystal.h>
#include "SensorData.h"
#include "Display.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Custom Character for Sound Level Display View, note: move to .h file 
// at a later point
byte hollowBlock[8] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
  B00000
};

void setupDisplay() {
  lcd.begin(16, 2);

  // Initiate the custom character
  lcd.createChar(0, hollowBlock);
}

void displayData(const SensorData& data) {
  lcd.clear();

  // Initiate the Sound Level Display View
  lcd.setCursor(0, 0);
  int numBars = map(data.soundLevel, 30, 120, 0, 16);
  for (int i = 0; i < 16; i++) {
    if (i < numBars) {
      lcd.write(byte(255)); // Full block
    } else {
      lcd.write(byte(0)); // Hollow block
    }
  }

  // Display the sound level
  lcd.setCursor(0, 1);
  lcd.print("Sound|dB: ");
  lcd.print(data.soundLevel);
}

//The main summary display view for different metrics
/*
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(data.temperature);
  lcd.setCursor(0, 1);
  lcd.print("BPM: ");
  lcd.print(data.heartRate);
  lcd.setCursor(8, 0);
  lcd.print("dB: ");
  lcd.print(data.soundLevel);
  lcd.setCursor(8, 1);
  lcd.print("Vib: ");
  lcd.print(data.vibration);
*/
