//Datei: FrameFade.cpp
//Implementation für die SubKlasse FrameFade
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <FrameFade.h>

FrameFade::FrameFade(int initNumLed) :
NeoPixelModi{initNumLed}
{
}