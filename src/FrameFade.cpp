//Datei: FrameFade.cpp
//Implementation für die SubKlasse FrameFade
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <FrameFade.h>

FrameFade::FrameFade(int initNumLed) :
NeoPixelModi{initNumLed}
{
    int rgb[3];
    createGoodRGB(rgb);
    setColor(rgb[0], rgb[1], rgb[2]); //Sets the Color of the first Group to a random Color
}

void FrameFade::run()
{   
    if (calculateSpeed(1000, 200))
    {
        switch (state)
        {
        case determine:
            if (red == 255)
            {
                if (green == 0) { state = blueMinus; }
                else { state = greenPlus; }
            } else if (green == 255)
            {
                if (blue == 0) { state = redMinus; }
                else { state = bluePlus; }            
            } else if (blue == 255)
            {
                if (red == 0) { state = greenMinus; }
                else { state = redPlus; }            
            } 
        
            setLed(0, red, green, blue);
            count = 0;

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
    if (!((newRed == 255 || newGreen == 255 || newBlue == 255) && 
        (newRed == 0 || newGreen == 0 || newBlue == 0)))
    {
        correctValues(newRed, newGreen, newBlue);
    }

    red = newRed;
    green = newGreen;
    blue = newBlue;     

    state = determine;
}

void FrameFade::correctValues(int& wRed, int& wGreen, int& wBlue) 
{
    // Find and set the smallest
    if (wRed <= wGreen && wRed <= wBlue) { wRed = 0; }
    else if (wGreen <= wRed && wGreen <= wBlue) { wGreen = 0; }
    else { wBlue = 0; }

    // Find and set the largest
    if (wRed >= wGreen && wRed >= wBlue) { wRed = 255; }
    else if (wGreen >= wRed && wGreen >= wBlue) { wGreen = 255; }
    else { wBlue = 255; }
}