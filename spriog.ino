#include "Scene.h"
#include "SceneController.h"
#include "Button.h"
#include "Input.h"

// screen libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// SD library
#include <SD.h>
// #include <SPI.h> shared with screen

#include <functional>

Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);



File root;

int cursorx = 0;
int cursory = 0;
void print(const char *text)
{
  tft.setCursor(cursorx, cursory);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(false);
  tft.print(text);
  int textWidth = strlen(text) * 6;
  cursorx += textWidth;
}

void println(const char *text)
{
  tft.setCursor(cursorx, cursory);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(false);
  print(text);
  cursorx = 0;
  cursory += 10;
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      print("\t");
    }
    print(entry.name());
    if (entry.isDirectory()) {
      println("/");
      printDirectory(entry, numTabs + 1);
    } else {

    }
    entry.close();
  }
}

int printNdirs(File dir, int numTabs, int nDirs) {//returns the number of directories printed
  int hasToPrint = nDirs;
  while (nDirs > 0) {
    File entry = dir.openNextFile();

    if (!entry) {
      // no more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      print("\t");
    }

    print(entry.name());
    nDirs--;

    if (entry.isDirectory()) {
      println("/");
      nDirs -= printNdirs(entry, numTabs + 1, nDirs);
    }

    entry.close();
  }

  return hasToPrint - nDirs;
}

Scene sampleScene = Scene(0, []() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print("Initial Scene");
  Serial.println("Initial Scene");
});

SceneController sceneController = SceneController(
  sampleScene
);

Scene fileDisplayer = Scene(1, []() {
  Serial.println("File Displayer Scene");
  printDirectory(root, 0);
});

Scene fileDisplayer2 = Scene(2, []() {
  Serial.println("File Displayer Scene 2");
  printNdirs(root, 0, 5);
  delay(20000);
});

Scene fileDisplayer3 = Scene(3, []() {
  Serial.println("File Displayer Scene 3");
  printNdirs(root, 0, 10);
});

void sayHello() {
  Serial.println("Hello");
}

Scene testInput = Scene(4, []() {
  Serial.println("Test Input Scene");
  Input input = Input();
  input.addButton('w',Button(5));
  input.addButton('s',Button(7));
  input.addButton('l',Button(15));

  //input.b('w').onClick = sayHello;
  while(!input.b('l').IsClicked()) {
    input.updateState();
    delay(100);
  }

  sceneController.changeScene(sampleScene);
});

Scene teststdfunction = Scene(5, []() {
  Serial.println("Test std function Scene");
  std::function<void()> f = []() {
    Serial.println("Hello from std function");
  };
  f();
  
  f = []() {
    Serial.println("Hello from std function 2");
  };
  f();
  sceneController.changeScene(sampleScene);
});



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
    Serial.print("sd waiting...");
  }
  root = SD.open("/");

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("im alive!", ST77XX_WHITE);

  sceneController.addScene(teststdfunction);
  sceneController.changeScene(teststdfunction);
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