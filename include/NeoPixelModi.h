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

            explicit NeoPixelModi(int initNumLed);

            ~NeoPixelModi();

            int getRedVal(int numLed) const {return red[numLed]; }
            int getGreenVal(int numLed) const {return green[numLed]; }
            int getBlueVal(int numLed) const {return blue[numLed]; }

            int getRed(int numLed) const { return calculateBrightness(red[numLed]); }
            int getGreen(int numLed) const { return calculateBrightness(green[numLed]); }
            int getBlue(int numLed) const { return calculateBrightness(blue[numLed]); }

            void setCanvas(int newRed, int newGreen, int newBlue);

            static bool calculateSpeed(int amplifier);

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
            int numLed;
            int* red;
            int* green;
            int* blue;
    
            static int speed;   //Von 0-255 0 = langsam, 255 = schnell
            static int brightness;  //Von 0-255 0 = dunkel(aus), 255 = hell


            static int calculateBrightness(int pixel) { return map(pixel, 0, 255, 0, brightness); }

            void setLed(int numLed, int newRed, int newGreen, int newBlue)
            {   
                red[numLed] = newRed; 
                green[numLed] = newGreen;
                blue[numLed] = newBlue;
            }

            void frameFade();

            void pixelRun();

    };


#endif //NEOPIXELPOTI_H_