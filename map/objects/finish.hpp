#pragma once
#include "abstract/abstractInteractingWithPlayerGameObject.hpp"

class Finish : public AbstractInteractingWithPlayerGameObject {
protected:

    void handleCollisionWithPlayerAction() override {
        player->finish();
    }

public:
    Finish(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {
        sprite.setTexture(images::finish);
    }
};
