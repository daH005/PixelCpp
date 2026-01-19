#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Heart : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const vector<Texture> textures = images::heart;
    FrameIndexCyclicalCounter anim = FrameIndexCyclicalCounter(textures.size(), 0.6);

    void handleCollisionWithPlayerAction() override {
        if (player->addHP()) {
            toBeDeleted = true;
        }
    }

    void draw() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
        AbstractInteractingWithPlayerGameObject::draw();
    }

public:
    Heart(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {}
};
