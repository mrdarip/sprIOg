Scene sampleScene = Scene(0, []() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print("Initial Scene");
});

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

  SceneController::changeScene(sampleScene);
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
  SceneController::changeScene(Scene(5, []() {
  println("Game Over");
  delay(5000);
  SceneController::changeScene(sampleGame);
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

Scene fileSelector = Scene(8, []() {
  Input input = Input();
  input.addButton('w',Button(5));
  input.addButton('a',Button(6));
  input.addButton('s',Button(7));
  input.addButton('d',Button(8));

  input.addButton('i',Button(12));
  input.addButton('j',Button(13));
  input.addButton('k',Button(14));
  input.addButton('l',Button(15));

  int fileIndex = 0;
  File currentDir = root;
  bool fileSelected = false;

  input.b('w').setOnClick([&]() {
    
    if(fileIndex > 0) {
      fileIndex--;
    }

    resetCursor();
    printFilesInDir(currentDir, fileIndex);
   });

  input.b('s').setOnClick([&]() {
    fileIndex++;

    resetCursor();
    printFilesInDir(currentDir, fileIndex);
  });

  input.b('l').setOnClick([&]() {
    File currentDir = getNthFile(currentDir, fileIndex);
    
      fileIndex = 0;
      resetCursor();
      printFilesInDir(currentDir, fileIndex);

      //fileSelected = !currentDir.isDirectory();
  });

  printFilesInDir(currentDir, fileIndex);

  while(!fileSelected) {
    input.updateState();
    delay(10);
  }

  SceneController::changeScene(sampleScene);
});

void updateUI(int numScenes, int selectedScene, String sceneNames[]) {
  resetCursor();
  println("Select Scene");
  for (int i = 0; i < numScenes; i++)
  {
    if(i == selectedScene) {
      print("> ");
    }
    println(sceneNames[i]);
  }
}

Scene sceneSelection = Scene(7, []() {
  Scene scenes[] = {sampleScene, fileDisplayer, fileDisplayer2, fileDisplayer3, testInput, sampleGame, testKeyboard, fileSelector};
  String sceneNames[] = {"sampleScene", "fileDisplayer", "fileDisplayer2", "fileDisplayer3", "testInput", "sampleGame", "testKeyboard", "fileSelector"};
  int selectedScene = 0;
  int numScenes = 8;

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

    updateUI(numScenes, selectedScene, sceneNames);
  });

  input.b('s').setOnClick([&]() {
    selectedScene++;
    if(selectedScene >= numScenes) {
      selectedScene = 0;
    }

    updateUI(numScenes, selectedScene, sceneNames);
  });

  input.b('l').setOnClick([&]() {
    println("changing scene to " + sceneNames[selectedScene]);
    SceneController::changeScene(scenes[selectedScene]);
  });

  updateUI(numScenes, selectedScene, sceneNames);
  
  while(SceneController::getCurrentScene().getId() == 7) {
    input.updateState();
    delay(10);
  }

  resetCursor();
});



void setupScenes() {
  SceneController::addScene(sceneSelection);
  SceneController::addScene(sampleScene);
  SceneController::addScene(fileDisplayer);
  SceneController::addScene(fileDisplayer2);
  SceneController::addScene(fileDisplayer3);
  SceneController::addScene(testInput);
  SceneController::addScene(sampleGame);
  SceneController::addScene(testKeyboard);
  SceneController::addScene(fileSelector);
}