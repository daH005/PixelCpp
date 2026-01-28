#pragma once
#include "../../common/updateAndDeleteObjects.hpp"
#include "abstract/abstractInteractingWithPlayerGameObject.hpp"
#include "coin.hpp"

class TakenCoin : public Coin {
public:
    TakenCoin(int x, int y, Player* player) : Coin(x, y, player) {
        handleCollisionWithPlayerAction();
    }
};

class Chest : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const Texture defaultTexture = images::chestDefault;
    inline static const Texture openedTexture = images::chestOpened;

    vector<TakenCoin> coins;
    bool isOpened = false;
    int maxCoinCount;
    int spawnedCoinCount = 0;
    FPSBasedTimer spawnDelayTimer = FPSBasedTimer(0.2);

    void handleCollisionWithPlayerAction() override {
        isOpened = true;
        sprite.setTexture(openedTexture);
    }

    void updateCoins() {
        updateAndDeleteObjects(coins);
    }

public:
    Chest(int x, int y, Player* player, int maxCoinCount = 10) : AbstractInteractingWithPlayerGameObject(x, y, player), maxCoinCount(maxCoinCount) {
        sprite.setTexture(defaultTexture);
    }

    void update() override {
        if (isOpened && spawnedCoinCount < maxCoinCount) {
            spawnDelayTimer.next();
            if (!spawnDelayTimer.isWorking()) {
                coins.push_back(TakenCoin(sprite.getLeft(), sprite.getTop(), player));
                ++spawnedCoinCount;
                spawnDelayTimer.restart();
            }
        }
        updateCoins();
        AbstractInteractingWithPlayerGameObject::update();
    }

};
