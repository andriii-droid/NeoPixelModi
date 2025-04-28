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

        void run() override;
        //Runs the OneFrame algorythm to generate PixelColors

        void setColor(int newRed, int newGreen, int newBlue) override;
        //Sets the Color

    private:
        int red = 0;
        int green = 0;
        int blue = 255;
    };
#endif //ONEFRAME_H_