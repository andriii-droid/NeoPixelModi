//Datei: PixelRun.cpp
//Implementation für die SubKlasse PixelRun
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <PixelRun.h>

PixelRun::PixelRun(int initNumLed) :
NeoPixelModi{initNumLed}
{
}

void PixelRun::run(int red, int green, int blue)
{
    if (calculateSpeed(6))
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