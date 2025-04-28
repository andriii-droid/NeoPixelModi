//Datei: FrameFade.cpp
//Implementation für die SubKlasse FrameFade
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <FrameFade.h>

FrameFade::FrameFade(int initNumLed) :
NeoPixelModi{initNumLed}
{

}

void FrameFade::run()
{  
    static int count = 0;
    enum fadeState {init, redPlus, greenPlus, bluePlus, redMinus, greenMinus, blueMinus};
    static fadeState state = init;
    
    if (calculateSpeed(1))
    {
        switch (state)
        {
        case init:
            setCanvas(count, getGreen(0), getBlue(0));
            if (count == 255) { state = greenPlus; }

            break;
    
        case redPlus:
            setCanvas(count, getGreen(0), getBlue(0));
            if (count == 255) { state = blueMinus; }
    
            break;
    
        case blueMinus:
            setCanvas(getRed(0), getGreen(0), 255 - count);
            if (count == 255) { state = greenPlus; }
    
            break;
    
        case greenPlus:
            setCanvas(getRed(0), count, getBlue(0));
            if (count == 255) { state = redMinus; }
    
            break;
    
        case redMinus:
            setCanvas(255 - count, getGreen(0), getBlue(0));
            if (count == 255) { state = bluePlus; }
    
            break;
    
        case bluePlus:
            setCanvas(getRed(0), getGreen(0), count);
            if (count == 255) { state = greenMinus; }
    
            break;
    
        case greenMinus:
            setCanvas(getRed(0), 255 -count, getBlue(0));
            if (count == 255) { state = redPlus; }
    
            break;
        }
        ++count;
        setRedChange(getRed(0));
        setGreenChange(getGreen(0));
        setBlueChange(getBlue(0));
    }
    
    if (count == 256) { count = 0; }
}
