#pragma once
#include "config.hpp";

float convertSecondsToFrameCount(float seconds) {
    return seconds * config::MAX_FPS;
}

class TimeCounter {
protected:
    float duration;
    int maxCount;
    int currentCount = 0;

public:
    TimeCounter(float duration = 0) : duration(duration) {
        maxCount = convertSecondsToFrameCount(duration);
    }

    void restart() {
        currentCount = maxCount;
    }

    void stop() {
        currentCount = 0;
    }

    float delta() const {
        return maxCount - currentCount;
    }

    void next() {
        if (currentCount > 0) {
            currentCount--;
        }
    }

    bool isWorking() const {
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

    int getCurrentIndex() const {
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
