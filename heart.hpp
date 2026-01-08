#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Heart : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const vector<Texture> textures = images::heart;
    FrameCounter anim = FrameCounter(textures.size(), 0.6);

    void _handleCollisionWithPlayer() override {
        if (player->addHP()) {
            toBeDeleted = true;
        }
    }

    void updateTexture() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
    }

public:
    Heart(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {}
};
