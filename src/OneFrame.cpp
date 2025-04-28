//Datei: OneFrame.cpp
//Implementation für die SubKlasse OneFrame
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <OneFrame.h>

OneFrame::OneFrame(int initNumLed) :
NeoPixelModi{initNumLed}
{
}

void OneFrame::run()
{
    setCanvas(red, green, blue);
}

void OneFrame::setColor(int newRed, int newGreen, int newBlue)
{
    red = newRed;
    green = newGreen;
    blue = newBlue;
}