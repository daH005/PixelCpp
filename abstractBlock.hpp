#pragma once
#include "abstractGameObject.hpp"
#include "player.hpp"

class AbstractBlock : public AbstractGameObject {
public:
    AbstractBlock(int x, int y, Player* player, int w = 40, int h = 40) : AbstractGameObject(x, y, ZIndex::BLOCK) {
        player->addBlockRect(FloatRect(x, y, w, h));
    }
};
