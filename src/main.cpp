#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include <Servo.h>

int cnt = 0;

TFT_eSPI tft = TFT_eSPI();

Servo myservo; // create servo object to control a servo

// Reset Pin is used for I2C or SPI
#define CAP1188_RESET  9

// CS pin is used for software or hardware SPI
#define CAP1188_CS  26

// These are defined for software SPI, for hardware SPI, check your 
// board's SPI pins in the Arduino documentation
#define CAP1188_MOSI  32
#define CAP1188_MISO  33
#define CAP1188_CLK  25

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
// Adafruit_CAP1188 cap = Adafruit_CAP1188();

// Or...Use I2C, with reset pin
Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_RESET);

// Or... Hardware SPI, CS pin & reset pin 
// Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CS, CAP1188_RESET);

// Or.. Software SPI: clock, miso, mosi, cs, reset
// Adafruit_CAP1188 cap = Adafruit_CAP1188(CAP1188_CLK, CAP1188_MISO, CAP1188_MOSI, CAP1188_CS, CAP1188_RESET);

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
    tft.drawString("CAP1188 not found", 20, 50, 1);
    while (1);
  }
  tft.drawString("CAP1188 found", 20, 50, 1);


}

void loop() {
  uint8_t touched = cap.touched();
  cnt = 0;
  for(uint8_t i = 0; i < 8; i++) {
    if (touched & (1 << i)) {
      cnt += 1;
    }
  }
  tft.drawString("C" + String(cnt), 0, 0, 4);
  delay(1000);
}