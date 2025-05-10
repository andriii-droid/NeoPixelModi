//Datei: MultiFade.h
//Headerdatei für die SubKlasse MultiFade
//Autor: Andri Andermatt, 27.04.2025
#include <Arduino.h>
#include <FrameFade.h>
#include <vector>

#ifndef MULTIFADE_H_
#define MULTIFADE_H_
    class MultiFade : public FrameFade
    {
        public:
        MultiFade(int initNumLed, const std::vector<int>& initGroups);
        //Ctor

        ~MultiFade();
        //Dtor

        void run() override;
        //Runs the FrameFade algorythm to generate PixelColors

        void setColor(int newRed, int newGreen, int newBlue) override;
        //Sets the Color

        void setSpeed(int newSpeed) override;

        private:
        FrameFade** SingleFades;

        std::vector<int> groups;

        int red = 0;
        int green = 0;
        int blue = 0;

        void shiftValues(int index, int one, int two, int three);
    };

#endif //MULTIFADE_H_