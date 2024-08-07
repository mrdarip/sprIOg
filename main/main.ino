//screen libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

//SD library
#include <SD.h>
//#include <SPI.h> shared with screen

Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);

File root;
void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(1);  // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("\nInitializing SD card...");
  SPI.setRX(_MISO);
  SPI.setTX(_MOSI);
  SPI.setSCK(_SCK);
  while(!sdInitialized = SD.begin(_CS)){
    delay(1000);
  }


  tft.initR(INITR_BLACKTAB); 
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("im alive!", ST77XX_WHITE);

}

void loop() {
  // put your main code here, to run repeatedly:

}
