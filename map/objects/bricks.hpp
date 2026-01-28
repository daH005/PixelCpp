#pragma once
#include "../../common/images.hpp"
#include "abstract/abstractBlock.hpp"
#include "abstract/abstractBackground.hpp"

class Bricks : public AbstractBlock {
public:
    Bricks(int x, int y, Player* player) : AbstractBlock(x, y, player) {
        sprite.setTexture(images::bricks);
    }

};

class BackgroundBricks : public AbstractBackground {
public:
    BackgroundBricks(int x, int y) : AbstractBackground(x, y) {
        sprite.setTexture(images::backgroundBricks);
    }
};
