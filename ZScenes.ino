void updateUI(int numScenes, int selectedScene, String sceneNames[]) {
  resetCursor();
  println("Select Scene");
  for (int i = 0; i < numScenes; i++)
  {
    if(i == selectedScene) {
      print("> ",false);
    }
    println(sceneNames[i]);
  }
}

Scene sceneSelection = Scene(7, []() {
  Scene scenes[] = {sampleScene, fileDisplayer, fileDisplayer2, fileDisplayer3, testInput, sampleGame, testKeyboard, fileSelector, fileReader};
  String sceneNames[] = {"sampleScene", "fileDisplayer", "fileDisplayer2", "fileDisplayer3", "testInput", "sampleGame", "testKeyboard", "fileSelector", "fileReader"};
  int selectedScene = 0;
  int numScenes = 9;

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
  SceneController::addScene(fileReader);
}