#pragma once
#include "abstractBlock.hpp"
#include "abstractBackground.hpp"
#include "images.hpp"

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
