#include "Scene.h"
#include "SceneController.h"
#include "Button.h"
#include "Input.h"

// screen libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// SD library
#include <SD.h>
// SPI.h shared with screen

#include "Keyboard.h"
#include <functional>

#include<Scenes.h>

Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);

File root;
bool hasSdCard = false;

void setup()
{
  SPI.setRX(16);
  SPI.setTX(19);
  SPI.setSCK(18);
  
  hasSdCard = SD.begin(21);
  Serial.begin(9600);
  
  if(hasSdCard){
    root = SD.open("/");
  }

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(3);

  SceneController::init(sampleScene);
  
  testdrawtext("Sprig is ready", ST77XX_WHITE);
}

void loop()
{
  SceneController::runCurrentScene();
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}