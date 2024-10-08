int cursorx = 0;
int cursory = 0;
void print(String text, bool wrap)
{
  tft.setCursor(cursorx, cursory);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(wrap);
  tft.print(text);
  int textWidth = text.length() * 6;
  cursorx += textWidth;
}

void println(String text)
{
  print(text,true);
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
      print("\t", false);
    }
    print(entry.name(), false);
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
      print("\t", false);
    }

    print(entry.name(), false);
    nDirs--;

    if (entry.isDirectory()) {
      println("/");
      nDirs -= printNdirs(entry, numTabs + 1, nDirs);
    }

    entry.close();
  }

  return hasToPrint - nDirs;
}

void printFilesInDir(File dir, int n, int limit) {
  for(int i = 0; i < n; i++) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    entry.close();
  }

  for(int i = 0; i < limit; i++) {
    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    print(entry.name(), false);
    if (entry.isDirectory()) {
      println("/");
    } else {
      println("");
    }
    entry.close();
  }
}

File getNthFile(File dir, int n)
{
  Serial.println("File: " + String(n) + " in " + String(dir.name()));
  int i = 0;
  while (true)
  {
    Serial.println("Getting file");
    Serial.println(i);
    File entry = dir.openNextFile();

    if (!entry)
    {
      Serial.println("No more files");
      // no more files
      break;
    }
    Serial.println("Got file" + String(entry.name()));
    if (i == n)
    {
      Serial.println("Returning file");
      Serial.println(entry.name());
      return entry;
    }
    i++;
    entry.close();
  }
  return File();
}