//Datei: PixelRun.h
//Headerdatei für die SubKlasse PixelRun
//Autor: Andri Andermatt, 27.04.2025
#include <Arduino.h>
#include <NeoPixelModi.h>


#ifndef PIXELRUN_H_
#define PIXELRUN_H_
    class PixelRun : public NeoPixelModi
    {
    public:
    PixelRun(int initNumLed);

    void run() override;

    void setColor(int newRed, int newGreen, int newBlue) override;
    //Sets the Color

    private:
        int red = 0;
        int green = 0;
        int blue = 0;
    };
#endif //PIXELRUN_H_