//Datei: MultiFadeIn.cpp
//Implementation für die SubKlasse MultiFadeIn
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <MultiFadeIn.h>

MultiFadeIn::MultiFadeIn(int initNumLed, const std::vector<int>& initGroups)
    :FadeIn{initNumLed}, groups{initGroups}
{
    int countLed = 0;

    for (size_t i = 0; i < groups.size(); i++)  //Checks if Number of all Leds and Leds in Group are the same Size
    {
        countLed += groups[i];
    }

    int index = groups.size() - 1;

    while ((countLed != initNumLed) && index > 0)  //Corrects group Array if led Number not correct
    {
        if (groups[index] == 0) { --index; }
        
        groups[index] -= 1;
        countLed -= 1;
    }

    SingleFadeIns = new FadeIn*[groups.size()];

    for (size_t j = 0; j < groups.size(); j++)  //Creates Array with multiple FadeIn Objects, one for each Group
    {
        SingleFadeIns[j] = new FadeIn{groups[j]};
    }

    setSpeed(getSpeed()); //Sets for each Group a random subSpeed The Globalspeed is applied on Top

    int rgb[3];
    createGoodRGB(rgb);
    setColor(rgb[0], rgb[1], rgb[2]);
}

MultiFadeIn::~MultiFadeIn()
{
    if (SingleFadeIns != nullptr) {
        for (size_t i = 0; i < groups.size(); ++i) {
            delete SingleFadeIns[i]; // delete each FadeIn object
        }
        delete[] SingleFadeIns; // delete the array of pointers
    }
}

void MultiFadeIn::run()
{
    int done = 0;

    for (size_t i = 0; i < groups.size(); i++)
    {
        SingleFadeIns[i]->run();

        for (size_t j = done; j < done + groups[i]; j++)
        {
            setLed(j, SingleFadeIns[i]->getRed(0), SingleFadeIns[i]->getGreen(0), SingleFadeIns[i]->getBlue(0));
        }

        done += groups[i];
    }
}

void MultiFadeIn::setColor(int newRed, int newGreen, int newBlue)
{
    correctValues(newRed, newGreen, newBlue);
    
    red = newRed;
    green = newGreen;
    blue = newBlue;     

    for (size_t i = 0; i < groups.size(); i++)
    {
        shiftValues(i, red, green, blue);
        SingleFadeIns[i]->setColor(red, green, blue);
    }
}

void MultiFadeIn::shiftValues(int index, int one, int two, int three)
{
    switch (index)
    {
    case 1:
    case 2:
    case 4:
    case 5:
        red = three;
        green = one;
        blue = two;

        break;
    case 3:
        red = three;
        green = two;
        blue = one;

        break;
    }
}

void MultiFadeIn::setSpeed(int newSpeed)
{
    NeoPixelModi::setSpeed(newSpeed);
    for (size_t i = 0; i < groups.size(); i++)  
    {
        SingleFadeIns[i]->setSpeed(newSpeed);
    }
}