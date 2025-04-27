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

    void run();
    //Runs the FrameFade algorythm to generate PixelColors

    private:
        /* data */
    };
#endif //FRAMEFADE_H_