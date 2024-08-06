## How to make it work

1. Install arduino IDE (Exe file) from the official website.
2. Install the RP2040 board package (by arduino) from the board manager.
3. Check if the board is detected by the computer.
4. Run Blink.ino file, try editing LED_BUILTIN to just the pin 4 (led_r).
5. Done.

## How to make it work (Advanced)

1. Install Adafruit ST7735 library from the library manager and its dependencies.
2. open the example file "graphictest.ino" from the library and run it.
3. change the line 64 to `Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);` and run it.
4. Done.
