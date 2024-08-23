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

void printFilesInDir(File dir, int n) {
  for(int i = 0; i < n; i++) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    entry.close();
  }

  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    print(entry.name());
    if (entry.isDirectory()) {
      println("/");
    } else {
      println("");
    }
    entry.close();
  }
}

File getNthFile(File dir, int n) {
  int i = 0;
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    if (i == n) {
      return entry;
    }
    i++;
    entry.close();
  }
  return File();
}