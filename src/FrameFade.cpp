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
            setCanvas(count, getGreenVal(0), getBlueVal(0));
            if (count == 255) { state = greenPlus; }

            break;
    
        case redPlus:
            setCanvas(count, getGreenVal(0), getBlueVal(0));
            if (count == 255) { state = blueMinus; }
    
            break;
    
        case blueMinus:
            setCanvas(getRedVal(0), getGreenVal(0), 255 - count);
            if (count == 255) { state = greenPlus; }
    
            break;
    
        case greenPlus:
            setCanvas(getRedVal(0), count, getBlueVal(0));
            if (count == 255) { state = redMinus; }
    
            break;
    
        case redMinus:
            setCanvas(255 - count, getGreenVal(0), getBlueVal(0));
            if (count == 255) { state = bluePlus; }
    
            break;
    
        case bluePlus:
            setCanvas(getRedVal(0), getGreenVal(0), count);
            if (count == 255) { state = greenMinus; }
    
            break;
    
        case greenMinus:
            setCanvas(getRedVal(0), 255 -count, getBlueVal(0));
            if (count == 255) { state = redPlus; }
    
            break;
        }
        ++count;
    }
    
    if (count == 256) { count = 0; }
}
