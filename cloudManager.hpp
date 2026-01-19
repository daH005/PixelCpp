#pragma once
#include <random>

#include "abstractGameObject.hpp"
#include "images.hpp"
#include "counters.hpp"

random_device rd;
mt19937 gen(rd());

class Cloud : public AbstractGameObject {
protected:
    inline static int currentImageIndex = 0;

    uniform_int_distribution<> xRandomizer = uniform_int_distribution<>(0, window->getSize().x);
    uniform_int_distribution<> yRandomizer = uniform_int_distribution<>(0, 300);
    uniform_real_distribution<> speedRandomizer = uniform_real_distribution<>(0.01, 0.05);
    float xvel = speedRandomizer(gen);
    int xToBeDeleted = window->getSize().x;

    void initImage() {
        sprite.setTexture(images::clouds[currentImageIndex]);
        currentImageIndex++;
        if (currentImageIndex > images::clouds.size() - 1) {
            currentImageIndex = 0;
        }
    }

public:
    Cloud(bool behindLeftEdge = true) : AbstractGameObject(0, 0) {
        initImage();

        int x;
        if (behindLeftEdge) {
            x = -sprite.getWidth();
        }
        else {
            x = xRandomizer(gen);
        }
        sprite.setPosition(x, yRandomizer(gen));
    }

    void update() override {
        sprite.moveX(xvel);
        if (sprite.getLeft() > xToBeDeleted) {
            toBeDeleted = true;
        }
        AbstractGameObject::update();
    }
};

class CloudManager {
protected:
    const int INITIAL_CLOUD_COUNT = 50;

    FPSBasedTimer spawnFPSBasedTimer = FPSBasedTimer(20);
    vector<Cloud> clouds;

    void createInitialClouds() {
        for (int i = 0; i < INITIAL_CLOUD_COUNT; i++) {
            createCloud(false);
        }
    }

    void createCloud(bool behindLeftEdge = true) {
        clouds.push_back(Cloud(behindLeftEdge));
    }

    void spawnCloudOncePerTime() {
        spawnFPSBasedTimer.next();
        if (!spawnFPSBasedTimer.isWorking()) {
            createCloud();
            spawnFPSBasedTimer.restart();
        }
    }

    void updateClouds() {
        for (auto it = clouds.begin(); it != clouds.end(); ) {
            it->update();
            if (it->getToBeDeleted()) {
                it = clouds.erase(it);
            }
            else {
                it++;
            }
        }
    }

public:
    CloudManager() {}

    void reset() {
        clouds.clear();
        createInitialClouds();
    }

    void update() {
        spawnCloudOncePerTime();
        updateClouds();
    }
};
