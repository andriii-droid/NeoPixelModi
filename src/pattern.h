#ifndef PATTERN_H_
#define PATTERN_H_
    class Pattern
    {
        public:
            explicit Pattern();

            void nextMode();

            void previousMode();

            void setMode(int newMode);
            
        
        private:
            int modi;
            int modiLast;
    };

#endif