//Datei: NeoPixelModi.h
//Headerdatei für die Klasse NeoPixelModi
//Autor: Andri Andermatt, 28.03.2025
#include <Arduino.h>

#ifndef NEOPIXELPOTI_H_
#define NEOPIXELPOTI_H_
    class NeoPixelModi
    {
        public:
            explicit NeoPixelModi(int initNumLed);
            //Constructor: Creates Color Arrays, depending on Number of Leds

            ~NeoPixelModi();
            //Desturctor: Destroys Color Arrays

            //getters
            int getNumLed() const { return numLed; }

            int getRed(int numLed) const {return red[numLed]; }
            int getGreen(int numLed) const {return green[numLed]; }
            int getBlue(int numLed) const {return blue[numLed]; }

            //getters / setters for change Colors
            int getRedChange() const {return redChange; }
            int getGreenChange() const {return greenChange; }
            int getBlueChange() const {return blueChange; }

            int setRedChange(int newRed) {redChange = newRed; }
            int setGreenChange(int newGreen) {greenChange = newGreen; }
            int setBlueChange(int newBlue) {blueChange = newBlue; }

            //getters to Read Color for Strip
            int getR(int numLed)  { return calculateBrightness(red[numLed]); }
            int getG(int numLed)  { return calculateBrightness(green[numLed]); }
            int getB(int numLed)  { return calculateBrightness(blue[numLed]); }

            bool calculateSpeed(int amplifier);
            //Calculates the Speed a Mode Class is run

            void setCanvas(int newRed, int newGreen, int newBlue);
            //Sets the all Leds to the specified Color

            void setLed(int numLed, int newRed, int newGreen, int newBlue);
            //Sets the specified Led to the specified Color

            void setSpeed(int newSpeed) 
            { 
                if (newSpeed > 0 && newSpeed <= 255)
                {
                    speed = newSpeed; 
                }
            }
            //Sets the New specified Speed

            void setBrightness(int newBrightness)
            { 
                if (newBrightness > 0 && newBrightness <= 255)
                {
                    brightness = newBrightness; 
                }
            }
            //Sets the New specified Brightness


        private:
            int numLed; //Number of Leds
            int* red; //red Array
            int* green; //green Array
            int* blue; //blue Array

            int redChange;
            int greenChange;
            int blueChange;
    
            int speed;   //Von 0-255 0 = langsam, 255 = schnell
            int brightness;  //Von 0-255 0 = dunkel(aus), 255 = hell

            int calculateBrightness(int pixel) 
            { return map(pixel, 0, 255, 0, brightness); }
            //Calculates the Brightness
    };


#endif //NEOPIXELPOTI_H_