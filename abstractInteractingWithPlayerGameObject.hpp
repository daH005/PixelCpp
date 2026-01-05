#pragma once
#include "player.hpp"

class AbstractInteractingWithPlayerGameObject : public AbstractGameObject {
protected:
    Player& player;

    void handleCollisionWithPlayer() {
        if (!sprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
            return;
        }

        _handleCollisionWithPlayer();
    }

    virtual void _handleCollisionWithPlayer() {

    }

public:
    AbstractInteractingWithPlayerGameObject(int x, int y, Player& player) : AbstractGameObject(x, y), player(player) {}

    void update() {
        handleCollisionWithPlayer();
        AbstractGameObject::update();
    }
};
