#include <Arduino.h>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <MultiFade.h>
#include <Button.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

constexpr int numLeds = 5;
Adafruit_NeoPixel strip(numLeds, 8, NEO_GRB + NEO_KHZ800);
int constexpr maxModi = 4;
std::vector<int> cont = {2};


int modi = 0;
int modiLast = 0;
NeoPixelModi* Mode[maxModi];

Button b1{15};

void setup() 
{
  Serial.begin(9600);
  strip.begin();
  strip.clear();

  Mode[0] = new OneFrame{5};
  Mode[1] = new FrameFade{5};
  Mode[2] = new PixelRun{5};
  Mode[3] = new MultiFade{5, cont};



  Mode[modi]->setSpeed(5);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  b1.updateButton();

  if (b1.getState(b1.time))
  {
    Mode[modi]->setColor(rand() % 256, rand() % 256, rand() % 256);
  }
  

 if (b1.getState(b1.click))
 {
    ++modi;
    if (modi == maxModi)
    {
      modi = 0;
    }
 }

 if (modi != modiLast)
 {
    Mode[modi]->setBrightness(Mode[modiLast]->getBrightness());
    Mode[modi]->setSpeed(Mode[modiLast]->getSpeed());

    modiLast = modi;
 }
 
  Mode[modi]->run();

  for (size_t i = 0; i < numLeds; i++)
  {
    strip.setPixelColor(i, strip.Color(Mode[modi]->getR(i), Mode[modi]->getG(i), Mode[modi]->getB(i)));
  }

  strip.show();
}