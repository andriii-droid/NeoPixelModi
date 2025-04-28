#include <Arduino.h>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <Adafruit_NeoPixel.h>

constexpr int numLeds = 5;
Adafruit_NeoPixel strip(numLeds, 8, NEO_GRB + NEO_KHZ800);

PixelRun Run{numLeds};

void setup() 
{
  Serial.begin(9600);
  strip.begin();
  strip.clear();


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  Run.run();

  for (size_t i = 0; i < numLeds; i++)
  {
    strip.setPixelColor(i, strip.Color(Run.getR(i), Run.getG(i), Run.getB(i)));
  }

  strip.show();
}