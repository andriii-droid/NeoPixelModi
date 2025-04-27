//Datei: OneFrame.cpp
//Implementation für die SubKlasse OneFrame
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <OneFrame.h>

OneFrame::OneFrame(int initNumLed) :
NeoPixelModi{initNumLed}
{
}

void OneFrame::run(int red, int green, int blue)
{
    setCanvas(red, green, blue);
}