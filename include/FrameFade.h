//Datei: FrameFade.h
//Headerdatei für die SubKlasse FrameFade
//Autor: Andri Andermatt, 27.04.2025
#include <Arduino.h>
#include <NeoPixelModi.h>


#ifndef FRAMEFADE_H_
#define FRAMEFADE_H_
    class FrameFade : public NeoPixelModi
    {
    public:
    FrameFade(int initNumLed);
    //Ctor

    void run() override;
    //Runs the FrameFade algorythm to generate PixelColors

    void setColor(int newRed, int newGreen, int newBlue) override;
    //Sets the Color

    private:
        int red;
        int green;
        int blue;
    };
#endif //FRAMEFADE_H_