//Datei: FadeIn.h
//Headerdatei für die SubKlasse FadeIn
//Autor: Andri Andermatt, 02.05.2025
#include <Arduino.h>
#include <NeoPixelModi.h>

#ifndef FADEIN_H_
#define FADEIN_H_
    class FadeIn : public NeoPixelModi
    {
    public:
    FadeIn(int initNumLed);
    //Ctor

    virtual ~FadeIn() {}

    void run() override;
    //Runs the FrameFade algorythm to generate PixelColors

    void setColor(int newRed, int newGreen, int newBlue) override;
    //Sets the Color

    void correctValues(int& wRed, int& wGreen, int& wBlue);
    //Sets the lowest Value to 0, the highest to 255

    private:
        enum fadeState {determine, redPlus, redMinus, greenPlus, greenMinus, bluePlus, blueMinus, 
            redGreenPlus, redGreenMinus, greenBluePlus, greenBlueMinus, blueRedPlus, blueRedMinus};
        fadeState state = determine;
        int count = 0;  

        int red = 0;
        int green = 0;
        int blue = 0;

        fadeState randFadeState(fadeState current);
    };

#endif //FADEIN_H_