//Datei: MultiFade.cpp
//Implementation für die SubKlasse MultiFade
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <MultiFade.h>

MultiFade::MultiFade(int initNumLed, const std::vector<int>& initGroups)
    :FrameFade{initNumLed}, groups{initGroups}
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

    SingleFades = new FrameFade*[groups.size()];

    for (size_t j = 0; j < groups.size(); j++)  //Creates Array with multiple FrameFade Objects, one for each Group
    {
        SingleFades[j] = new FrameFade{groups[j]};
        SingleFades[j]->setColor(rand() % 256, rand() % 256, rand() % 256); //TODO
    }
}

MultiFade::~MultiFade()
{
    if (SingleFades != nullptr) {
        for (size_t i = 0; i < groups.size(); ++i) {
            delete SingleFades[i]; // delete each FrameFade object
        }
        delete[] SingleFades; // delete the array of pointers
    }
}

void MultiFade::run()
{
    if (calculateSpeed(1))
    {
        int done = 0;

        for (size_t i = 0; i < groups.size(); i++)
        {
            SingleFades[i]->run();

            for (size_t j = done; j < done + groups[i]; j++)
            {
                setLed(j, SingleFades[i]->getRed(0), SingleFades[i]->getGreen(0), SingleFades[i]->getBlue(0));
            }

            done += groups[i];
        }
    }
}

void MultiFade::setColor(int newRed, int newGreen, int newBlue)
{
    
}