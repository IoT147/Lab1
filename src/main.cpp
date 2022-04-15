#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include <Servo.h>
int cnt; 

TFT_eSPI tft = TFT_eSPI();

//const int ADC = 26;
 //const int SDA = 21;
 //const int SCL = 22;



Servo myservo; // create servo object to control a servo


// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// CS pin is used for software or hardware SPI
#define CAP1188_CS  10

// These are defined for software SPI, for hardware SPI, check your 
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  11
#define CAP1188_MISO  12
#define CAP1188_CLK  13

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
Adafruit_CAP1188 cap = Adafruit_CAP1188();

// Or...Use I2C, with reset pin
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin 
// Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
//Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);

void setup() {
  //pinMode(SDA, INPUT);
  //pinMode(SCL, INPUT);
  Serial.begin(9600);
  Serial.println("CAP1188 test!");

  // Display init
  tft.init();
  tft.fillScreen(TFT_BLACK);

  // Initialize the sensor, if using i2c you can pass in the i2c address
  // if (!cap.begin(0x28)) {
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  tft.drawString("CAP1188", 20, 50, 4);


}

void loop() {
  uint8_t touched = cap.touched();

  if (touched == 0) {
    
    return;
  }
  
  for (uint8_t i = 0; i < 8; i++) {
    if (touched & (1 << i)) {
      cnt += 1;
      
    }
  }
  tft.drawString("C" + String(cnt), 20, 50, 4);
  delay(1000);
}


// 
//
//
/*
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();
int i = 1;

void setup()
{
    tft.init();
    tft.fillScreen(TFT_BLACK);
}

void loop()
{
  // haha
  // testing this feature
  tft.drawString(String(i), 50, 100, 6);
  sleep(1);
  i++;
}
*/