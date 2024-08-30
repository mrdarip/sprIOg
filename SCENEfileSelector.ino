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
    printFilesInDir(currentDir, fileIndex, 13);
   });

  input.b('s').setOnClick([&]() {
    fileIndex++;

    resetCursor();
    printFilesInDir(currentDir, fileIndex,13);
  });

  input.b('l').setOnClick([&]() {
    currentDir = getNthFile(currentDir, fileIndex);
    Serial.println("Selected: " + String(currentDir.name()));
    fileIndex = 0;
    resetCursor();
    printFilesInDir(currentDir, fileIndex,13);

    fileSelected = !currentDir.isDirectory();
  });

  input.b('k').setOnClick([&]() {
    currentDir.close();
    fileIndex = 0;
    resetCursor();
    printFilesInDir(currentDir, fileIndex,13);
  });

  printFilesInDir(currentDir, fileIndex,13);

  while(!fileSelected) {
    input.updateState();
    delay(10);
  }

  SceneController::changeScene(sampleScene);
});