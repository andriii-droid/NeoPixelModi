//Datei: MultiFrame.h
//Headerdatei für die SubKlasse MultiFade
//Autor: Andri Andermatt, 27.04.2025
#include <Arduino.h>
#include <FrameFade.h>
#include <NeoPixelModi.h>
#include <vector>



#ifndef MULTIFADE_H_
#define MULTIFADE_H_
    class MultiFade : public FrameFade
    {
        public:
        MultiFade(int initNumLed, const std::vector<int>& initGroups);
        //Ctor

        void run() override;
        //Runs the FrameFade algorythm to generate PixelColors

        void setColor(int newRed, int newGreen, int newBlue) override;
        //Sets the Color

        private:
        FrameFade** SingleFades;

        std::vector<int> groups;
    };
#endif //MULTIFADE_H_