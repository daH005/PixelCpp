#pragma once
#include "config.hpp"

float convertSecondsToFrameCount(float seconds) {
    return seconds * config::MAX_FPS;
}

class FPSBasedTimer {
protected:
    float duration;
    int maxCount;
    int currentCount = 0;

public:
    FPSBasedTimer(float duration = 0) : duration(duration) {
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

class FrameIndexCyclicalCounter {
protected:
    int count;
    float delay;
    int currentIndex = 0;
    FPSBasedTimer timer;

public:
    FrameIndexCyclicalCounter(int count, float delay) : count(count), delay(delay) {
        timer = FPSBasedTimer(delay);
        timer.restart();
    }

    int getCurrentIndex() const {
        return currentIndex;
    }

    void next() {
        timer.next();
        if (timer.isWorking()) {
            return;
        }

        timer.restart();
        currentIndex++;

        if (currentIndex > count - 1) {
            currentIndex = 0;
        }
    }

};

class FrameIndexFiniteCounter : public FrameIndexCyclicalCounter {
protected:
    bool isEnded = true;

public:
    FrameIndexFiniteCounter(int count, float delay) : FrameIndexCyclicalCounter(count, delay) {}

    void restart() {
        isEnded = false;
        currentIndex = 0;
    }

    bool getIsEnded() {
        return isEnded;
    }

    void next() {
        if (isEnded) {
            return;
        }

        bool previousIndexWasLast = currentIndex == count - 1;
        FrameIndexCyclicalCounter::next();
        if (previousIndexWasLast && currentIndex == 0) {
            isEnded = true;
        }
    }

};
