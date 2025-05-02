//Datei: MultiFrame.cpp
//Implementation für die SubKlasse MultiFrame
//Autor: Andri Andermatt, 27.04.202
#include <Arduino.h>
#include <MultiFrame.h>

MultiFrame::MultiFrame(int initNumLed, const std::vector<int>& initGroups)
    :OneFrame{initNumLed}, groups{initGroups}
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

    SingleFrames = new OneFrame*[groups.size()];

    for (size_t j = 0; j < groups.size(); j++)  //Creates Array with multiple FrameFade Objects, one for each Group
    {
        SingleFrames[j] = new OneFrame{groups[j]};
    }

    int rgb[3];
    createGoodRGB(rgb);
    setColor(rgb[0], rgb[1], rgb[2]); //Sets the Color of the first Group to a random Color
}

MultiFrame::~MultiFrame()
{
    if (SingleFrames != nullptr) {
        for (size_t i = 0; i < groups.size(); ++i) {
            delete SingleFrames[i]; // delete each FrameFade object
        }
        delete[] SingleFrames; // delete the array of pointers
    }
}

void MultiFrame::run()
{
 
    int done = 0;

    for (size_t i = 0; i < groups.size(); i++)
    {
        SingleFrames[i]->run();

        for (size_t j = done; j < done + groups[i]; j++)
        {
            setLed(j, SingleFrames[i]->getRed(0), SingleFrames[i]->getGreen(0), SingleFrames[i]->getBlue(0));
        }

        done += groups[i];
    }
}

void MultiFrame::setColor(int newRed, int newGreen, int newBlue)
{
    red = newRed;
    green = newGreen;
    blue = newBlue;  

    for (size_t i = 0; i < groups.size(); i++)
    {
        shiftValues(i, red, green, blue);
        SingleFrames[i]->setColor(red, green, blue);
    }
}

void MultiFrame::shiftValues(int index, int one, int two, int three)
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