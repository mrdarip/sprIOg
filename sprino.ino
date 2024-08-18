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

  while(!Serial.available() && millis() < 5000){
    resetCursor();
    println("No serial :( Timeout in: " + String(millis()) + "ms");
    delay(100);
  } 
  
  println("Sprig is ready");

  setupScenes();
}

void loop()
{
  Serial.println("Looping");
  SceneController::runCurrentScene();
  delay(1000);
}

