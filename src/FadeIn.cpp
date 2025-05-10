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
    if (calculateSpeed(1000, 200))
    {
        switch (state)
        {
        case determine:
            if (red == 0)
            {
              state = greenBluePlus;
              count = green;               
            } else if (green == 0)
            {
                state = blueRedPlus;   
                count = blue;                       
            } else if (blue == 0)
            {
                state = redGreenPlus;  
                count = red;               
            } 
        
            setCanvas(red, green, blue);

            break;
    
        case redPlus:
            setCanvas(count, getGreen(0), getBlue(0));
            if (count == 255) { state = redMinus; }
    
            break;
        case redMinus:
            setCanvas(255 - count, getGreen(0), getBlue(0));
            if (count == 255) { state = randFadeState(redPlus); }

            break;
        case redGreenPlus:
            setCanvas(count, count, getBlue(0));
            if (count == 255) { state = redGreenMinus; }

            break;
        case redGreenMinus:
            setCanvas(255 - count, 255 - count, getBlue(0));
            if (count == 255) { state = randFadeState(redGreenPlus); }

            break;
        case greenPlus:
            setCanvas(getRed(0), count, getBlue(0));
            if (count == 255) { state = greenMinus; }
    
            break;
        case greenMinus:
            setCanvas(getRed(0), 255 - count, getBlue(0));
            if (count == 255) { state = randFadeState(greenPlus); }
    
            break;
        case greenBluePlus:
            setCanvas(getRed(0), count, count);
            if (count == 255) { state = greenBlueMinus; }

            break;
        case greenBlueMinus:
            setCanvas(getRed(0), 255 - count, 255 - count);
            if (count == 255) { state = randFadeState(greenBluePlus); }
        
            break;
        case bluePlus:
            setCanvas(getRed(0), getGreen(0), count);
            if (count == 255) { state = blueMinus; }
    
            break;
        case blueMinus:
            setCanvas(getRed(0), getGreen(0), 255 - count);
            if (count == 255) { state = randFadeState(bluePlus); }
    
            break;
        case blueRedPlus:
            setCanvas(count, getGreen(0), count);
            if (count == 255) { state = blueRedMinus; }

            break;
        case blueRedMinus:
            setCanvas(255 - count, getGreen(0), 255 - count);
            if (count == 255) { state = randFadeState(blueRedPlus); }
        
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

FadeIn::fadeState FadeIn::randFadeState(fadeState current)
{
    int random = (rand() % 6) + 1;

    random = random * 2 - 1;

    if (current == fadeState(random))
    {
        if (random == 11) { return fadeState(1); } 
        else { return fadeState(random + 2); }
    } else { return fadeState(random); }
}
