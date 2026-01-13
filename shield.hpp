#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Shield : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const vector<Texture> textures = images::shield;
    FrameIndexCyclicalCounter anim = FrameIndexCyclicalCounter(textures.size(), 0.2);

    void _handleCollisionWithPlayer() override {
        if (player->addShield()) {
            toBeDeleted = true;
        }
    }

    void updateTexture() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
    }

public:
    Shield(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {}
};
