#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Water : public AbstractInteractingWithPlayerGameObject {
protected:

    inline static const float PLAYER_Y_VEL_TO_TREMBLE = 2;
    inline static const float TREMBLING_SPEED_DOWN = 1.5;  // Должно быть кратно TREMBLING_SPEED_UP.
    inline static const float TREMBLING_SPEED_UP = -0.1;
    inline static const float TREMBLING_DEVIATION = 3;

    int startTremblingY;
    int endTremblingY;
    bool isTrembling = false;

    void _handleCollisionWithPlayer() override {
        player->setAsInWater();
        if (player->getYvel() > PLAYER_Y_VEL_TO_TREMBLE) {
            isTrembling = true;
        }
    }

    void updateTrembling() {
        if (isTrembling) {
            if (sprite.getGlobalBounds().top < endTremblingY) {
                sprite.move(0, TREMBLING_SPEED_DOWN);
            }
            else {
                isTrembling = false;
            }
        }
        else if (sprite.getGlobalBounds().top > startTremblingY) {
            sprite.move(0, TREMBLING_SPEED_UP);

            if (sprite.getGlobalBounds().top < startTremblingY) {
                sprite.setPosition(sprite.getGlobalBounds().left, startTremblingY);
            }
        }
    }

public:
    Water(int x, int y, Player* player, bool isTop = false) : AbstractInteractingWithPlayerGameObject(x, y, player, ZIndex::OVERLAY), startTremblingY(y) {
        endTremblingY = startTremblingY + TREMBLING_DEVIATION;
        if (isTop) {
            sprite.setTexture(images::topWater);
        }
        else {
            sprite.setTexture(images::water);
        }
    }

    void update() override {
        updateTrembling();
        AbstractInteractingWithPlayerGameObject::update();
    }

};
