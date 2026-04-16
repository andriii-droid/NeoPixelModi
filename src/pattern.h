#include <vector>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <FadeIn.h>
#include <MultiFade.h>
#include <MultiFrame.h>
#include <MultiFadeIn.h>
#include <Arduino.h>
#include <chrono> // for seed
#include <random> // for random engine
#include <NeoPixelBus.h>

#ifndef PATTERN_H_
#define PATTERN_H_
    class Pattern
    {
        public:
            explicit Pattern(int numLed, std::vector<int> frame);

            void nextMode();

            void previousMode();

            void setMode(int newMode);

            RgbColor getRGB(int index);

            void setColor(int r = 0, int g = 0, int b = 0);

        private:
            void setParameters();

            void createGoodRGB(int *rgb);
            // Creates a pregnant rgb color

            int modi = 0;
            int modiLast = 0;
            int numPattern = 0;
            std::vector <NeoPixelModi *> patterns;
    };

#endif