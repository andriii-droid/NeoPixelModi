//Datei: MultiFrame.h
//Headerdatei für die SubKlasse MultiFrame
//Autor: Andri Andermatt, 27.04.2025
#include <Arduino.h>
#include <OneFrame.h>
#include <vector>

#ifndef MULTIFRAME_H_
#define MULTIFRAME_H_
    class MultiFrame : public OneFrame
    {
        public:
        MultiFrame(int initNumLed, const std::vector<int>& initGroups);
        //Ctor

        ~MultiFrame();
        //Dtor

        void run() override;
        //Runs the FrameFade algorythm to generate PixelColors

        void setColor(int newRed, int newGreen, int newBlue) override;
        //Sets the Color

        private:
        OneFrame** SingleFrames;

        std::vector<int> groups;

        int red = 0;
        int green = 0;
        int blue = 0;

        void shiftValues(int index, int one, int two, int three);
    };
#endif //MULTIFRAME_H_