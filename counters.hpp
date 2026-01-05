#pragma once
#include "config.hpp";

class TimeCounter {
protected:
    float duration;
    int maxCount;
    int currentCount = 0;

public:
    TimeCounter(float duration = 0) : duration(duration) {
        maxCount = duration * Config::MAX_FPS;
    }

    void restart() {
        currentCount = maxCount;
    }

    void stop() {
        currentCount = 0;
    }

    float delta() {
        return maxCount - currentCount;
    }

    void next() {
        if (currentCount > 0) {
            currentCount--;
        }
    }

    bool isWorking() {
        return currentCount > 0;
    }

};

class FrameCounter {
protected:
    int count;
    float delay;
    int currentIndex = 0;
    TimeCounter timeCounter;

public:
    FrameCounter(int count, float delay) : count(count), delay(delay) {
        timeCounter = TimeCounter(delay);
    }

    int getCurrentIndex() {
        return currentIndex;
    }

    void next() {
        timeCounter.next();
        if (timeCounter.isWorking()) {
            return;
        }

        timeCounter.restart();
        currentIndex++;

        if (currentIndex > count - 1) {
            currentIndex = 0;
        }
    }

};
