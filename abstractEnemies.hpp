#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class AbstractXPatrolEnemy : public AbstractInteractingWithPlayerGameObject, public GameObjectWithDirectionMixin {
protected:
    int startX;
    int endX;
    float speed;

    float xPush;
    float yPush;

    float xvel = speed;

    virtual void _handleCollisionWithPlayer() override {
        player->hit(xPush, yPush, getCenter());
    }

    virtual void move() {
        FloatRect rect = sprite.getGlobalBounds();
        if (rect.left <= startX || rect.left + rect.width >= endX) {
            xvel *= -1;
            flipSprite((Direction)((int)direction * -1));
        }
        sprite.move(xvel, 0);
    }

public:
    AbstractXPatrolEnemy(int x, int y, Player* player, 
                         int startX, int endX, float speed,
                         float xPush, float yPush
    ) : AbstractInteractingWithPlayerGameObject(x, y, player), GameObjectWithDirectionMixin(AbstractXPatrolEnemy::sprite),
        startX(startX), endX(endX), speed(speed),
        xPush(xPush), yPush(yPush) {}

    void update() override {
        move();
        AbstractInteractingWithPlayerGameObject::update();
    }

};
