#include <pattern.h>

Pattern::Pattern(int numLed, std::vector<int> frame)
{
    patterns.push_back(new OneFrame{numLed});
    patterns.push_back(new FrameFade{numLed});
    patterns.push_back(new PixelRun{numLed});
    patterns.push_back(new MultiFade{numLed, frame});
    patterns.push_back(new MultiFrame{numLed, frame});
    patterns.push_back(new FadeIn{numLed});
    patterns.push_back(new MultiFadeIn{numLed, frame});

    numPattern = patterns.size();

    patterns[modi]->setSpeed(255);
}

std::vector<int> Pattern::getRGB(int index) {
    std::vector<int> rgb;
    rgb.push_back(patterns[modi]->getR(index));
    rgb.push_back(patterns[modi]->getG(index));
    rgb.push_back(patterns[modi]->getB(index));
    return rgb;
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

void Pattern::setColor(int r, int g, int b) {
    int rgb[3] = {r, g, b};
    if ((r == 0) and (g == 0) and (b == 0)) {
        createGoodRGB(rgb);
        patterns[modi]->setColor(rgb[0], rgb[1], rgb[2]);
    }


}

void Pattern::createGoodRGB(int *rgb)
{
    std::array<int, 3> numbers = {0, 1, 2};

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

    rgb[numbers[0]] = 156 + rand() % 100;
    rgb[numbers[1]] = rand() % 157;
    rgb[numbers[2]] = 0;
}
