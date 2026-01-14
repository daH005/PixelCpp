#pragma once
#include "abstractEnemies.hpp"

class Bat : public AbstractXPatrolEnemy {
protected:
    inline static const vector<Texture> goTextures = images::batGo;
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.05);

    void updateTexture() override {
        sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
        goAnim.next();
    }

public:
    Bat(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 1.5f, 35, -13) {}
};
