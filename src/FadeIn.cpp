//Datei: FadeIn.cpp
//Implementation für die SubKlasse FadeIn
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <FadeIn.h>

FadeIn::FadeIn(int initNumLed) :
NeoPixelModi{initNumLed}
{
    int rgb[3];
    createGoodRGB(rgb);
    setColor(rgb[0], rgb[1], rgb[2]); //Sets the Color of the first Group to a random Color
}

void FadeIn::run()
{   
    if (calculateSpeed(1))
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
            if (count == 255) { state = redMinus; }
    
            break;
        case redMinus:
            setCanvas(255 - count, getGreen(0), getBlue(0));
            if (count == 255) { state = redGreenPlus; }

            break;
        case redGreenPlus:
            setCanvas(count, count, getBlue(0));
            if (count == 255) { state = redGreenMinus; }

            break;
        case redGreenMinus:
            setCanvas(255 - count, 255 - count, getBlue(0));
            if (count == 255) { state = greenPlus; }

            break;
        case greenPlus:
            setCanvas(getRed(0), count, getBlue(0));
            if (count == 255) { state = greenMinus; }
    
            break;
        case greenMinus:
            setCanvas(getRed(0), 255 -count, getBlue(0));
            if (count == 255) { state = greenBluePlus; }
    
            break;
        case greenBluePlus:
            setCanvas(getRed(0), count, count);
            if (count == 255) { state = greenBlueMinus; }

            break;
        case greenBlueMinus:
            setCanvas(getRed(0), 255 - count, 255 - count);
            if (count == 255) { state = bluePlus; }
        
            break;
        case bluePlus:
            setCanvas(getRed(0), getGreen(0), count);
            if (count == 255) { state = blueMinus; }
    
            break;
        case blueMinus:
            setCanvas(getRed(0), getGreen(0), 255 - count);
            if (count == 255) { state = blueRedPlus; }
    
            break;
        case blueRedPlus:
            setCanvas(count, getGreen(0), count);
            if (count == 255) { state = blueRedMinus; }

            break;
        case blueRedMinus:
            setCanvas(255 - count, getGreen(0), 255 - count);
            if (count == 255) { state = redPlus; }
        
            break;
        }
        ++count;
    }
    
    if (count == 256) { count = 0; }
}

void FadeIn::setColor(int newRed, int newGreen, int newBlue)
{
    correctValues(newRed, newGreen, newBlue);
    
    red = newRed;
    green = newGreen;
    blue = newBlue;     

    state = determine;
}

void FadeIn::correctValues(int& wRed, int& wGreen, int& wBlue) 
{ 
    //Find and set the smallest
    if (wRed <= wGreen && wRed <= wBlue) 
    {
        wRed = 0; 
        if (wBlue >= wGreen)
        {
            wBlue = wGreen;
        } else
        {
            wGreen = wBlue;
        }
    } else if (wGreen <= wRed && wGreen <= wBlue) 
    { 
        wGreen = 0; 
        if (wBlue >= wRed)
        {
            wBlue = wRed;
        } else
        {
            wRed = wBlue;
        }
    } else 
    { 
        wBlue = 0; 
        if (wGreen >= wRed)
        {
            wGreen = wRed;
        } else
        {
            wRed = wGreen;
        }
    }
}