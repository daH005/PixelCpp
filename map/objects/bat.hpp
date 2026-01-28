#pragma once
#include "abstract/abstractXPatrolEnemy.hpp"

class Bat : public AbstractXPatrolEnemy {
protected:
    inline static const vector<Texture> goTextures = images::batGo;
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.05);

    void draw() override {
        sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
        goAnim.next();
        AbstractXPatrolEnemy::draw();
    }

public:
    Bat(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 1.5, 35, -13) {}
};
