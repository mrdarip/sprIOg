Scene fileReader = Scene(9, []() {
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
    printFilesInDir(currentDir, fileIndex,13);
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

  int readLine = 0;
  bool wantToExit = false;

  printFileLines(currentDir, readLine);


  input.b('w').setOnClick([&]() {
    readLine--;
    if(readLine < 0) {
      readLine = 0;
    }

    printFileLines(currentDir, readLine);
  });

  input.b('s').setOnClick([&]() {
    readLine++;
    printFileLines(currentDir, readLine);
  });

  input.b('l').setOnClick([&]() {
    wantToExit = true;
  });

  input.b('k').setOnClick([&]() {
  });


  // read from the file until there's nothing else in it:
  while(!wantToExit) {
    input.updateState();
    delay(10);
  }

  currentDir.close();
});



void printFileLines(File file, int line) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.print(readFileLines(file, line));
}

String readFileLines(File file, int line) {
  String content = "";
  int pageWidth = 26;
  int pageHeight = 13;
  int pageSize = pageWidth * pageHeight;
  
  
  //a page can be as short as pageHeight chars if every line is \n
  //a page can be as long as pageSize if every char is not \n

  file.seek(line * pageWidth);

  for(int i = 0; i < pageSize; i++) {
    char c = file.read();
    content += c;
  }

  return content;
}