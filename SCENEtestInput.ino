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