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

    virtual ~FrameFade() {}

    void run() override;
    //Runs the FrameFade algorythm to generate PixelColors

    void setColor(int newRed, int newGreen, int newBlue) override;
    //Sets the Color

    void correctValues(int& wRed, int& wGreen, int& wBlue);
    //Sets the lowest Value to 0, the highest to 255

    private:
        enum fadeState {determine, init, redPlus, greenPlus, bluePlus, redMinus, greenMinus, blueMinus};
        fadeState state = determine;
        int count = 0;  

        int red = 0;
        int green = 0;
        int blue = 0;
    };
#endif //FRAMEFADE_H_