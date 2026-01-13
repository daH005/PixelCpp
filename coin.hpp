#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Coin : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const vector<Texture> textures = images::coin;
    FrameIndexCyclicalCounter anim = FrameIndexCyclicalCounter(textures.size(), 0.3);

    void _handleCollisionWithPlayer() override {
        toBeDeleted = true;
    }

    void updateTexture() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
    }

public:
    Coin(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {}
};
