//Datei: NeoPixelModi.cpp
//Implementationsdatei für die Klasse NeoPixelModi
//Autor: Andri Andermatt, 28.03.2025
#include <Arduino.h>
#include <NeoPixelModi.h>

#include <algorithm> // for std::shuffle
#include <random>    // for random engine
#include <chrono>    // for seed

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

    ++count;

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

void NeoPixelModi::createGoodRGB(int* rgb)
{
    std::array<int, 3> numbers = {0, 1, 2};

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

    rgb[numbers[0]] = 156 + rand() % 100;
    rgb[numbers[1]] = rand() % 157;
    rgb[numbers[0]] = 0;  
}




