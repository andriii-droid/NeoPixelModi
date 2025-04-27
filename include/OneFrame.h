//Datei: OneFrame.h
//Headerdatei für die SubKlasse OneFrame
//Autor: Andri Andermatt, 27.04.2025
#include <Arduino.h>
#include <NeoPixelModi.h>


#ifndef ONEFRAME_H_
#define ONEFRAME_H_
    class OneFrame : public NeoPixelModi
    {
    public:
        OneFrame(int initNumLed);
        //Ctor

        void run();
        //Runs the OneFrame algorythm to generate PixelColors

    private:
        /* data */
    };
#endif //ONEFRAME_H_