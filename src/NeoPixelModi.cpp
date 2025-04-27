//Datei: NeoPixelModi.cpp
//Implementationsdatei für die Klasse NeoPixelModi
//Autor: Andri Andermatt, 28.03.2025
#include <Arduino.h>
#include <NeoPixelModi.h>

int NeoPixelModi::speed = 255;
int NeoPixelModi::brightness = 0;

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
    //TODO save current Color config somewhere to initialise the new object with those values
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

void NeoPixelModi::setLed(int numLed, int newRed, int newGreen, int newBlue)
{   
    red[numLed] = newRed; 
    green[numLed] = newGreen;
    blue[numLed] = newBlue;
}




