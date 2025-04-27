#include <Arduino.h>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <Adafruit_NeoPixel.h>

constexpr int numLeds = 5;
Adafruit_NeoPixel strip(numLeds, 8, NEO_GRB + NEO_KHZ800);

PixelRun PixelMode{numLeds};

void setup() 
{
  Serial.begin(9600);
  strip.begin();
  strip.clear();
  PixelMode.setSpeed(20);
  NeoPixelModi::setBrightness(255);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  PixelMode.run(100,25,255);

  for (size_t i = 0; i < numLeds; i++)
  {
    strip.setPixelColor(i, strip.Color(PixelMode.getRed(i), PixelMode.getGreen(i), PixelMode.getBlue(i)));
  }

  // Serial.print("Red: ");
  // Serial.println(PixelMode.getRed(0));
  // Serial.print("Green: ");
  // Serial.println(PixelMode.getGreen(0));
  // Serial.print("Blue: ");
  // Serial.println(PixelMode.getBlue(0));


  strip.show();
}