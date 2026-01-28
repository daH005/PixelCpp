#pragma once
#include "abstract/abstractInteractingWithPlayerGameObject.hpp"

class Ladder : public AbstractInteractingWithPlayerGameObject {
protected:

    void handleCollisionWithPlayerAction() override {
        player->setAsOnLadder();
    }

public:
    Ladder(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {
        sprite.setTexture(images::ladder);
    }
};
