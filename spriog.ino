#include "Scene.h"
#include "SceneController.h"

// screen libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// SD library
#include <SD.h>
// #include <SPI.h> shared with screen

Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);

SceneController sceneController = SceneController(Scene(0, []() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print("Initial Scene");
}));
File root;
void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1); // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("\nInitializing SD card...");
  SPI.setRX(16);
  SPI.setTX(19);
  SPI.setSCK(18);
  while (!SD.begin(21))
  {
    delay(1000);
  }

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("im alive!", ST77XX_WHITE);
}

void loop()
{
  sceneController.runCurrentScene();
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}