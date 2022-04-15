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