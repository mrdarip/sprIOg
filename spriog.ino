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

int cursorx = 0;
int cursory = 0;
void print(String text)
{
  tft.setCursor(cursorx, cursory);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(false);
  tft.print(text);
  int textWidth = text.length() * 6;
  cursorx += textWidth;
}

void println(String text)
{
  print(text);
  cursorx = 0;
  cursory += 10;
}

void resetCursor()
{
  cursorx = 0;
  cursory = 0;
  tft.fillScreen(ST77XX_BLACK);
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
});

SceneController sceneController = SceneController(
  sampleScene
);

Scene fileDisplayer = Scene(1, []() {
  printDirectory(root, 0);
});

Scene fileDisplayer2 = Scene(2, []() {
  printNdirs(root, 0, 5);
  delay(20000);
});

Scene fileDisplayer3 = Scene(3, []() {
  printNdirs(root, 0, 10);
});

Scene testInput = Scene(4, []() {
  Input input = Input();
  input.addButton('w',Button(5));
  input.addButton('s',Button(7));
  input.addButton('l',Button(15));

  input.b('w').setOnClick(
    [&]() {
      println("w clicked");
    }
  );
  
  input.b('s').setOnClick(
    [&]() {
      println("s clicked");
    }
  );


  while(input.b('l').IsUp()) {
    input.updateState();
    delay(100);
  }

  sceneController.changeScene(sampleScene);
});

Scene sampleGame = Scene(6, []() {
  Input input = Input();

  input.addButton('w',Button(5));
  input.addButton('a',Button(6));
  input.addButton('s',Button(7));
  input.addButton('d',Button(8));

  input.addButton('i',Button(12));
  input.addButton('j',Button(13));
  input.addButton('k',Button(14));
  input.addButton('l',Button(15));

  int life = 3;
  char keyToPress = 'l';

  while(life > 0) {
    resetCursor();
    
    println("life: " + String(life));
    println("press: " + String(keyToPress));

    delay(2000); 
    input.updateState();

    bool isSuccessful = false;
    for (auto &pair : input.getButtons())
    {
      if(pair.second.IsDown()) {
        isSuccessful = pair.first == keyToPress;
        break;
      }
    }

    if(isSuccessful) {
      int randomNum = random(0, 8);
      char keys[] = {'w', 'a', 's', 'd', 'i', 'j', 'k', 'l'};
      keyToPress = keys[randomNum];
    } else {
      life--;
    }
  }
  sceneController.changeScene(Scene(5, []() {
  println("Game Over");
  delay(5000);
  sceneController.changeScene(sampleGame);
}));
});

Scene testKeyboard = Scene(5, []() {
  Keyboard.begin();
  Input input = Input();

  input.addButton('w',Button(5));
  input.addButton('a',Button(6));
  input.addButton('s',Button(7));
  input.addButton('d',Button(8));

  input.addButton('i',Button(12));
  input.addButton('j',Button(13));
  input.addButton('k',Button(14));
  input.addButton('l',Button(15));

  input.b('w').setOnClick([]() {Keyboard.press('w');});
  input.b('w').setOnRelease([]() {Keyboard.release('w');});

  input.b('a').setOnClick([]() {Keyboard.press('a');});
  input.b('a').setOnRelease([]() {Keyboard.release('a');});

  input.b('s').setOnClick([]() {Keyboard.press('s');});
  input.b('s').setOnRelease([]() {Keyboard.release('s');});

  input.b('d').setOnClick([]() {Keyboard.press('d');});
  input.b('d').setOnRelease([]() {Keyboard.release('d');});

  input.b('i').setOnClick([]() {Keyboard.press('i');});
  input.b('i').setOnRelease([]() {Keyboard.release('i');});

  input.b('j').setOnClick([]() {Keyboard.press('j');});
  input.b('j').setOnRelease([]() {Keyboard.release('j');});

  input.b('k').setOnClick([]() {Keyboard.press('k');});
  input.b('k').setOnRelease([]() {Keyboard.release('k');});

  input.b('l').setOnClick([]() {Keyboard.press('l');});
  input.b('l').setOnRelease([]() {Keyboard.release('l');});

  while(true) {
    input.updateState();
    delay(10);
  }
});

Scene sceneSelection = Scene(7, []() {
  Scene scenes[] = {sampleScene, fileDisplayer, fileDisplayer2, fileDisplayer3, testInput, sampleGame, testKeyboard};
  String sceneNames[] = {"sampleScene", "fileDisplayer", "fileDisplayer2", "fileDisplayer3", "testInput", "sampleGame", "testKeyboard"};
  int selectedScene = 0;
  int numScenes = 7;

  Input input = Input();
  input.addButton('w',Button(5));
  input.addButton('a',Button(6));
  input.addButton('s',Button(7));
  input.addButton('d',Button(8));

  input.addButton('i',Button(12));
  input.addButton('j',Button(13));
  input.addButton('k',Button(14));
  input.addButton('l',Button(15));

  input.b('w').setOnClick([&]() {
    selectedScene--;
    if(selectedScene < 0) {
      selectedScene = numScenes - 1;
    }
  });

  input.b('s').setOnClick([&]() {
    selectedScene++;
    if(selectedScene >= numScenes) {
      selectedScene = 0;
    }
  });

  input.b('l').setOnClick([&]() {
    sceneController.changeScene(scenes[selectedScene]);
  });
  
  while(true) {
    input.updateState();
    resetCursor();
    println("Select Scene");
    for (int i = 0; i < numScenes; i++)
    {
      if(i == selectedScene) {
        print("> ");
      }
      println(sceneNames[i]);
    }
    
    delay(100);
  }
});

void setup()
{
  SPI.setRX(16);
  SPI.setTX(19);
  SPI.setSCK(18);
  while (!SD.begin(21))
  {
    delay(1000);
  }
  root = SD.open("/");

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