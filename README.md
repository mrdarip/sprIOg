![1724257618681](https://github.com/user-attachments/assets/a0ee6360-5001-41ef-be56-283fd26397da)


## How to make it work (LED)

1. Install arduino IDE (Exe file) from the official website.
2. Install the RP2040 board package (by arduino) from the board manager.
3. Check if the board is detected by the computer.
4. Run Blink.ino file, try editing LED_BUILTIN to just the pin 4 (led_r).
5. Done.

## How to make it work (screen)

1. Install Adafruit ST7735 library from the library manager and its dependencies.
2. open the example file "graphictest.ino" from the library and run it.
3. change the line 64 to `Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);` and run it.
4. Done.

## How to make it work (SD card)

1. Open the example file "cardinfo.ino" from the SD library (from the examples for rpi 2040).
2. set _MISO = 16; _MOSI = 19; _CS = 21; _SCK = 18;
3. Run the code with a micro SD and ensure it's working.
