#pragma once
#include <random>

#include "abstractGameObjects.hpp"
#include "images.hpp"
#include "counters.hpp"

random_device rd;
mt19937 gen(rd());

class Cloud : public AbstractGameObject {
protected:
    static int currentImageIndex;

    uniform_int_distribution<> xRandomizer = uniform_int_distribution<>(0, window->getSize().x);
    uniform_int_distribution<> yRandomizer = uniform_int_distribution<>(0, 300);
    uniform_real_distribution<> speedRandomizer = uniform_real_distribution<>(0.01f, 0.05f);
    float xVel = speedRandomizer(gen);

    bool toDelete = false;
    int xToDelete = window->getSize().x;

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
            x = -sprite.getGlobalBounds().width;
        }
        else {
            x = xRandomizer(gen);
        }
        sprite.setPosition(x, yRandomizer(gen));
    }

    void update() {
        sprite.move(xVel, 0);
        if (sprite.getGlobalBounds().left > xToDelete) {
            toDelete = true;
        }
        AbstractGameObject::update();
    }

    bool getToDelete() {
        return toDelete;
    }
};
int Cloud::currentImageIndex = 0;

class CloudManager {
protected:
    const int INITIAL_CLOUD_COUNT = 50;

    TimeCounter spawnTimeCounter = TimeCounter(20);
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
        spawnTimeCounter.next();
        if (!spawnTimeCounter.isWorking()) {
            createCloud();
            spawnTimeCounter.restart();
        }
    }

    void updateClouds() {
        for (auto it = clouds.begin(); it != clouds.end(); ) {
            it->update();
            if (it->getToDelete()) {
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
