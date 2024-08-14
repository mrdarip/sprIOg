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

Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);

File root;

void setup()
{
  SPI.setRX(16);
  SPI.setTX(19);
  SPI.setSCK(18);
  
  SD.begin(21);
  Serial.begin(9600);
  
  //root = SD.open("/");

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(3);
  testdrawtext("im alive!", ST77XX_WHITE);

  sceneController.addScene(sceneSelection);
  sceneController.changeScene(sceneSelection);
}

void loop()
{
  sceneController.runCurrentScene();
  delay(1000); // this should be removed
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}