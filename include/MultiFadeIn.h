//Datei: MultiFadeIn.h
//Headerdatei für die SubKlasse MultiFadeIn
//Autor: Andri Andermatt, 08.05.2025
#include <Arduino.h>
#include <FadeIn.h>
#include <vector>

#ifndef MULTIFADEIN_H_
#define MULTIFADEIN_H_
    class MultiFadeIn : public FadeIn
    {
        public:
        MultiFadeIn(int initNumLed, const std::vector<int>& initGroups);
        //Ctor

        ~MultiFadeIn();
        //Dtor

        void run() override;
        //Runs the MultiFadeIn algorythm to generate PixelColors

        void setColor(int newRed, int newGreen, int newBlue) override;
        //Sets the Color

        private:
        FadeIn** SingleFadeIns;

        std::vector<int> groups;

        int red = 0;
        int green = 0;
        int blue = 0;

        void shiftValues(int index, int one, int two, int three);
    };
#endif //MULTIFADEIN_H_
