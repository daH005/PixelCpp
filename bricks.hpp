#pragma once
#include "abstractGameObjects.hpp"
#include "images.hpp"

class Bricks : public AbstractBlock {
public:
    Bricks(int x, int y) : AbstractBlock(x, y) {
        sprite.setTexture(images::bricks);
    }
};

class BackgroundBricks : public AbstractBackgroundBlock {
public:
    BackgroundBricks(int x, int y) : AbstractBackgroundBlock(x, y) {
        sprite.setTexture(images::backgroundBricks);
    }
};
