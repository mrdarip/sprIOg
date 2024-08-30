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