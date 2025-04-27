//Datei: PixelRun.cpp
//Implementation für die SubKlasse PixelRun
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <PixelRun.h>

PixelRun::PixelRun(int initNumLed) :
NeoPixelModi{initNumLed}
{
}