#pragma once
#include "abstract/abstractInteractingWithPlayerGameObject.hpp"

class Coin : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const vector<Texture> textures = images::coin;
    FrameIndexCyclicalCounter anim = FrameIndexCyclicalCounter(textures.size(), 0.3);

    inline static const float GRAVITY = 0.5;
    inline static const float JUMP_POWER = -10;
    float yvel;
    bool isCollected = false;
    int endY;

    void handleCollisionWithPlayerAction() override {
        if (!isCollected) {
            yvel = JUMP_POWER;
        }
        isCollected = true;
    }

    void draw() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
        AbstractInteractingWithPlayerGameObject::draw();
    }

public:
    Coin(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player), endY(y) {}

    void update() override {
        if (isCollected) {
            sprite.moveY(yvel);
            yvel += GRAVITY;
            if (sprite.getTop() >= endY) {
                toBeDeleted = true;
            }
        }
        AbstractInteractingWithPlayerGameObject::update();
    }

};
