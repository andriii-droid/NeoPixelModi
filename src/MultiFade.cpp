//Datei: MultiFade.cpp
//Implementation für die SubKlasse MultiFade
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <MultiFade.h>

MultiFade::MultiFade(int initNumLed, int& initGroups, int initNumGroups)
    :FrameFade{initNumLed}, groups{initGroups}, numGroups{initNumGroups}
{
}