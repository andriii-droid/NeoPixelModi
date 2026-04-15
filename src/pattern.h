#include <vector>
#include <OneFrame.h>
#include <FrameFade.h>
#include <PixelRun.h>
#include <FadeIn.h>
#include <MultiFade.h>
#include <MultiFrame.h>
#include <MultiFadeIn.h>
#include <Arduino.h>

#ifndef PATTERN_H_
#define PATTERN_H_
    class Pattern
    {
        public:
            explicit Pattern(int numLed, std::vector<int> cont);

            void nextMode();

            void previousMode();

            void setMode(int newMode);

            std::vector<int> getRGB(int index);
            
        
        private:
            void setParameters();

            int modi = 0;
            int modiLast = 0;
            int numPattern = 0;
            std::vector <NeoPixelModi *> patterns;
    };

#endif