#include <Arduino.h>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <Adafruit_NeoPixel.h>

constexpr int numLeds = 5;
Adafruit_NeoPixel strip(numLeds, 8, NEO_GRB + NEO_KHZ800);
int constexpr maxModi = 3;

int modi = 2;
NeoPixelModi* Mode[maxModi];


void setup() 
{
  Serial.begin(9600);
  strip.begin();
  strip.clear();

  Mode[0] = new OneFrame{5};
  Mode[1] = new FrameFade{5};
  Mode[2] = new PixelRun{5};

  Mode[modi]->setSpeed(5);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  Mode[modi]->setColor(255, 0, 255);
  Mode[modi]->run();

  for (size_t i = 0; i < numLeds; i++)
  {
    strip.setPixelColor(i, strip.Color(Mode[modi]->getR(i), Mode[modi]->getG(i), Mode[modi]->getB(i)));
  }

  strip.show();
}