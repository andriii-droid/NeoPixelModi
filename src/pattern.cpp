#include <pattern.h>

Pattern::Pattern(int numLed, std::vector<int> cont)
{
    patterns.push_back(new OneFrame{numLed});
    patterns.push_back(new FrameFade{numLed});
    patterns.push_back(new PixelRun{numLed});
    patterns.push_back(new MultiFade{numLed, cont});
    patterns.push_back(new MultiFrame{numLed, cont});
    patterns.push_back(new FadeIn{numLed});
    patterns.push_back(new MultiFadeIn{numLed, cont});

    numPattern = patterns.size();

    patterns[modi]->setSpeed(255);
}

void Pattern::nextMode() {
    modiLast = modi;
    ++modi;

    if (modi == numPattern) {
        modi = 0;
    }
    setParameters();
}

void Pattern::previousMode() {
    modiLast = modi;
    --modi;

    if (modi == 0)
    {
        modi = numPattern - 1;
    }
    setParameters();
}

void Pattern::setMode(int newMode) {
    if (newMode <= numPattern) {
        modiLast = modi;
        modi = newMode;
        setParameters();
    }
}

void Pattern::setParameters() {
    patterns[modi]->setBrightness(patterns[modiLast]->getBrightness());
    patterns[modi]->setSpeed(patterns[modiLast]->getSpeed());
}
