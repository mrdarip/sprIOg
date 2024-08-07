// screen libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// SD library
#include <SD.h>
// #include <SPI.h> shared with screen

Adafruit_ST7735 tft = Adafruit_ST7735(20, 22, 26);

File root;
void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1); // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("\nInitializing SD card...");
  SPI.setRX(_MISO);
  SPI.setTX(_MOSI);
  SPI.setSCK(_SCK);
  while (!sdInitialized = SD.begin(_CS))
  {
    delay(1000);
  }

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("im alive!", ST77XX_WHITE);

  Scene scene1 = Scene([]()
                       {
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext("scene1", ST77XX_WHITE); });
}

void loop()
{
  // put your main code here, to run repeatedly:
}

class Scene
{
private:
  auto loop();
  int id;

public:
  // Constructor
  Scene(int id,auto loop);

  // Destructor
  ~Scene();
};

// Constructor
Scene::Scene(int id,auto loop)
{
  this->loop = loop;
  this->id = id;
}

// Destructor
Scene::~Scene()
{
  // Do nothing
}

class SceneController
{
private:
  Scene currentScene;
  Scene[] scenes;

public:
  // Constructor
  SceneController(Scene initialScene);

  // Destructor
  ~SceneController();

  void changeScene(Scene newScene);
  void addScene(Scene newScene);
};

// Constructor
SceneController::SceneController(Scene initialScene)
{
  this->currentScene = initialScene;
}

// Destructor
SceneController::~SceneController()
{
  // Do nothing
}

void SceneController::changeScene(Scene newScene)
{
  this->currentScene = newScene;
}

void SceneController::addScene(Scene newScene)
{
  this->scenes.push(newScene);
}