#pragma once
#include "abstract/abstractInteractingWithPlayerGameObject.hpp"

class Shield : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const vector<Texture> textures = images::shield;
    FrameIndexCyclicalCounter anim = FrameIndexCyclicalCounter(textures.size(), 0.2);

    void handleCollisionWithPlayerAction() override {
        if (player->addShield()) {
            toBeDeleted = true;
        }
    }

    void draw() override {
        sprite.setTexture(textures[anim.getCurrentIndex()]);
        anim.next();
        AbstractInteractingWithPlayerGameObject::draw();
    }

public:
    Shield(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {}
};
