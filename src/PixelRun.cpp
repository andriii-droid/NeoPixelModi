//Datei: PixelRun.cpp
//Implementation für die SubKlasse PixelRun
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <PixelRun.h>

PixelRun::PixelRun(int initNumLed) :
NeoPixelModi{initNumLed}
{
    int rgb[3];
    createGoodRGB(rgb);
    setColor(rgb[0], rgb[1], rgb[2]); //Sets the Color of the first Group to a random Color
}

void PixelRun::run()
{
    if (calculateSpeed(1500, 1000))
    {
        static int count = 0;

        if (count == getNumLed())
        {
            count = 0;
        }

        setLed(count, red, green, blue);

        if (count == 0)
        {
            setLed(getNumLed() - 1, 0, 0, 0);
        } else
        {
            setLed(count - 1, 0, 0, 0);
        }
        ++count;
    }
}

void PixelRun::setColor(int newRed, int newGreen, int newBlue)
{
    red = newRed;
    green = newGreen;
    blue = newBlue;
}