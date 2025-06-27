#include <Arduino.h>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <FadeIn.h>
#include <MultiFade.h>
#include <MultiFrame.h>
#include <MultiFadeIn.h>
#include <Button.h>
#include <NeoPixelBus.h>
#include <vector>

constexpr uint16_t numLeds = 5;
constexpr uint8_t dataPin = 4;
NeoPixelBus<NeoGrbFeature, NeoEsp32Rmt0800KbpsMethod> strip(numLeds, dataPin);

int constexpr maxModi = 7;
std::vector<int> cont = {2 ,1 ,2};

int modi = 0;
int modiLast = 0;
NeoPixelModi* Mode[maxModi];

Button b1{15};
Button b2{14};

void setup() 
{
  Serial.begin(115200);
  strip.Begin();
  strip.Show();

  Mode[0] = new OneFrame{5};
  Mode[1] = new FrameFade{5};
  Mode[2] = new PixelRun{5};
  Mode[3] = new MultiFade{5, cont};
  Mode[4] = new MultiFrame{5, cont};
  Mode[5] = new FadeIn{5};
  Mode[6] = new MultiFadeIn{5, cont};

  Mode[modi]->setSpeed(255);

  delay(1000);
}

void loop() 
{ 
  Serial.println("loop");
    b1.updateButton();
    b2.updateButton();
  
    if (b2.getState(b2.click))
    {
      int rgb[3];
      Mode[modi]->createGoodRGB(rgb);
      Mode[modi]->setColor(rgb[0], rgb[1], rgb[2]);
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
   
    for(size_t i = 0; i < numLeds; i++)
    {
      strip.SetPixelColor(i, RgbColor(Mode[modi]->getR(i), Mode[modi]->getG(i), Mode[modi]->getB(i)));
    }

  strip.Show();
}
