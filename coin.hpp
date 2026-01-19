#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Coin : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const vector<Texture> textures = images::coin;
    FrameIndexCyclicalCounter anim = FrameIndexCyclicalCounter(textures.size(), 0.3);

    void handleCollisionWithPlayerAction() override {
        toBeDeleted = true;
    }

    void draw() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
        AbstractInteractingWithPlayerGameObject::draw();
    }

public:
    Coin(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {}
};
