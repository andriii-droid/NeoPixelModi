#include <Arduino.h>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <FadeIn.h>
#include <MultiFade.h>
#include <MultiFrame.h>
#include <MultiFadeIn.h>
#include <Button.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

constexpr int numLeds = 5;
Adafruit_NeoPixel strip(numLeds, 8, NEO_GRB + NEO_KHZ800);
int constexpr maxModi = 7;
std::vector<int> cont = {2 ,1 ,2};

int modi = 0;
int modiLast = 0;
NeoPixelModi* Mode[maxModi];

Button b1{15};
Button b2{14};

void vTaskNeoPixel(void *pvParameters);
void vTaskButton(void *pvParameters);

void setup() 
{
  Serial.begin(115200);
  strip.begin();
  strip.clear();

  Mode[0] = new OneFrame{5};
  Mode[1] = new FrameFade{5};
  Mode[2] = new PixelRun{5};
  Mode[3] = new MultiFade{5, cont};
  Mode[4] = new MultiFrame{5, cont};
  Mode[5] = new FadeIn{5};
  Mode[6] = new MultiFadeIn{5, cont};

  Mode[modi]->setSpeed(255);

  if (xTaskCreate(
    vTaskButton,
    "Button",
    512,
    NULL,
    1, 
    NULL
  ) != pdPASS)
  {
    Serial.println("Button Task failed to create");
  }

  if (xTaskCreate(
    vTaskNeoPixel,
    "NeoPixel",
    512,
    NULL,
    1, 
    NULL
  ) != pdPASS)
  {
    Serial.println("NeoPixel Task failed to create");
  }

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Serial.println("Setup complete");
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() 
{
  strip.show();
}

void vTaskButton(void *pvParameters)
{
  while (true)
  {
    b1.updateButton();
    b2.updateButton();
  
    int rgb[3];
  
    if (b2.getState(b2.click))
    {
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
  }
}

void vTaskNeoPixel(void *pvParameters)
{
  while (true)
  {
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
  }
}