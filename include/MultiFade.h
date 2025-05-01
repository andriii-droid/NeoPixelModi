//Datei: MultiFrame.h
//Headerdatei für die SubKlasse MultiFade
//Autor: Andri Andermatt, 27.04.2025
#include <Arduino.h>
#include <FrameFade.h>
#include <NeoPixelModi.h>



#ifndef MULTIFADE_H_
#define MULTIFADE_H_
    class MultiFade : public FrameFade
    {
        public:
        MultiFade(int initNumLed, int* (&initGroups), int initNumGroups);
        //Ctor

        void run() override;
        //Runs the FrameFade algorythm to generate PixelColors

        void setColor(int newRed, int newGreen, int newBlue) override;
        //Sets the Color

        private:
        NeoPixelModi** SingleFades;

        int* &groups;
        int numGroups;
    };
#endif //MULTIFADE_H_