//Datei: NeoPixelModi.h
//Headerdatei für die Klasse NeoPixelModi
//Autor: Andri Andermatt, 28.03.2025
#include <Arduino.h>

#ifndef NEOPIXELPOTI_H_
#define NEOPIXELPOTI_H_
    class NeoPixelModi
    {
        public:
            enum modi {oneFrame, fade, run};

            explicit NeoPixelModi(modi initMode, int initNumLed);

            ~NeoPixelModi();

            void calculateFrame();

            static void setColor(int newRed, int newGreen, int newBlue);

            int getRed(int numLed) const { return calculateBrightness(red[numLed]); }

            int getGreen(int numLed) const { return calculateBrightness(green[numLed]); }

            int getBlue(int numLed) const { return calculateBrightness(blue[numLed]); }

            static void setSpeed(int newSpeed) 
            { 
                if (newSpeed > 0 && newSpeed <= 255)
                {
                    speed = newSpeed; 
                }
            }

            static void setBrightness(int newBrightness)
            { 
                if (newBrightness > 0 && newBrightness <= 255)
                {
                    brightness = newBrightness; 
                }
            }

        private:
            modi mode;
            int numLed;
            int* red;
            int* green;
            int* blue;
            static int StRed;
            static int StGreen;
            static int StBlue;
            static int speed;   //Von 0-255 0 = langsam, 255 = schnell
            static int brightness;  //Von 0-255 0 = dunkel(aus), 255 = hell

            static bool calculateSpeed(int amplifier);

            static int calculateBrightness(int pixel) { return map(pixel, 0, 255, 0, brightness); }

            void setLed(int numLed, int newRed, int newGreen, int newBlue)
            {   
                red[numLed] = newRed; 
                green[numLed] = newGreen;
                blue[numLed] = newBlue;
            }

            void setCanvas(int newRed, int newGreen, int newBlue);

            void frameFade();

            void pixelRun();

    };


#endif //NEOPIXELPOTI_H_