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
    
    if (calculateSpeed(1))
    {
        switch (state)
        {
        case init:  //TODO decide how to count up, and where to start the fading(state)
            setCanvas(red, green, blue);
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
    }
    
    if (count == 256) { count = 0; }
}

void FrameFade::setColor(int newRed, int newGreen, int newBlue)
{
    if (((newRed || newGreen || newBlue) == 255) && 
        ((newRed || newGreen || newBlue) == 0))
    {
        red = newRed;
        green = newGreen;
        blue = newBlue;   
    } else
    {
        correctValues(red, green, blue);
    }

    state = init;
}

void FrameFade::correctValues(int a, int b, int c) //TODO
{

}
