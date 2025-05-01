//Datei: MultiFade.cpp
//Implementation für die SubKlasse MultiFade
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <MultiFade.h>

MultiFade::MultiFade(int initNumLed, int* (&initGroups), int initNumGroups)
    :FrameFade{initNumLed}, groups{initGroups}, numGroups{initNumGroups}
{
    int countLed = 0;

    for (size_t i = 0; i < numGroups; i++)  //Checks if Number of all Leds and Leds in Group are the same Size
    {
        countLed += groups[i];
    }

    int index = numGroups - 1;

    while ((countLed != initNumLed) && index != 0)  //Corrects group Array if led Number not correct
    {
        if (groups[index] == 0) { --index; }
        
        groups[index] -= 1;
        countLed -= 1;
    }

    for (size_t j = 0; j < numGroups; j++)  //Creates Array with multiple FrameFade Objects, one for each Group
    {
        SingleFades[j] = new FrameFade{groups[j]};
    }
}