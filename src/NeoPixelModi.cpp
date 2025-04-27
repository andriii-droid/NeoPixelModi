//Datei: NeoPixelModi.cpp
//Implementationsdatei für die Klasse NeoPixelModi
//Autor: Andri Andermatt, 28.03.2025
#include <Arduino.h>
#include <NeoPixelModi.h>

int NeoPixelModi::speed = 255;
int NeoPixelModi::brightness = 0;
int NeoPixelModi::StRed = 0;
int NeoPixelModi::StGreen = 0;
int NeoPixelModi::StBlue = 0;

NeoPixelModi::NeoPixelModi(int initNumLed) //Ctor
    : numLed{initNumLed}
{
    red = new int[numLed];
    green = new int[numLed];
    blue = new int[numLed];

    setCanvas(0, 0, 0);
} 

NeoPixelModi::~NeoPixelModi() //Dtor
{
    delete[] red;
    delete[] green;
    delete[] blue;
}

void NeoPixelModi::setColor(int newRed, int newGreen, int newBlue)
{
    StRed = newRed;
    StGreen = newGreen;
    StBlue = newBlue;
}

void NeoPixelModi::frameFade()
{
    static int count = 0;
    enum fadeState {init, redPlus, greenPlus, bluePlus, redMinus, greenMinus, blueMinus};
    static fadeState state = init;

    if (calculateSpeed(1))
    {
        switch (state)
        {
        case init:
            setCanvas(count, green[0], blue[0]);
            if (count == 255) { state = greenPlus; }

            break;

        case redPlus:
            setCanvas(count, green[0], blue[0]);
            if (count == 255) { state = blueMinus; }

            break;

        case blueMinus:
            setCanvas(red[0], green[0], 255 - count);
            if (count == 255) { state = greenPlus; }

            break;

        case greenPlus:
            setCanvas(red[0], count, blue[0]);
            if (count == 255) { state = redMinus; }

            break;

        case redMinus:
            setCanvas(255 - count, green[0], blue[0]);
            if (count == 255) { state = bluePlus; }

            break;

        case bluePlus:
            setCanvas(red[0], green[0], count);
            if (count == 255) { state = greenMinus; }

            break;

        case greenMinus:
            setCanvas(red[0], 255 -count, blue[0]);
            if (count == 255) { state = redPlus; }

            break;
        }
        ++count;
    }

    if (count == 256) { count = 0; }
}

void NeoPixelModi::pixelRun()
{
    if (calculateSpeed(6))
    {
        static int count = 0;

        if (count == numLed)
        {
            count = 0;
        }

        setLed(count, StRed, StGreen, StBlue);

        if (count == 0)
        {
            setLed(numLed - 1, 0, 0, 0);
        } else
        {
            setLed(count - 1, 0, 0, 0);
        }
        ++count;
    }
    
}


bool NeoPixelModi::calculateSpeed(int amplifier)
{
    int speedDiv = map(speed, 0, 255, amplifier*100, 1);

    static int count = 1;
    ++count;

    static int countLast = 0;

    int countDiv = count / speedDiv;

    if (countDiv != countLast)
    {
        countLast = countDiv;
        return true;
    } else
    {
        return false;
    }
}

void NeoPixelModi::setCanvas(int newRed, int newGreen, int newBlue)
{
    for (size_t i = 0; i < numLed; i++)
    {
        setLed(i, newRed, newGreen, newBlue);
    }
    
}




