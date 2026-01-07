#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Coin : public AbstractInteractingWithPlayerGameObject {
protected:

    vector<Texture> textures = images::coin;
    FrameCounter anim = FrameCounter(textures.size(), 0.3);

    void _handleCollisionWithPlayer() override {

    }

    void updateTexture() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
    }

public:
    Coin(int x, int y, Player& player) : AbstractInteractingWithPlayerGameObject(x, y, player) {}
};
