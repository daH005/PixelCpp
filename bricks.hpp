#pragma once
#include "abstractGameObjects.hpp"
#include "imageManager.hpp"

class Bricks : public AbstractBlock {
public:
    Bricks(int x, int y) : AbstractBlock(x, y) {
        sprite.setTexture(imageManager.getBricks());
    }
};

class BackgroundBricks : public AbstractBackgroundBlock {
public:
    BackgroundBricks(int x, int y) : AbstractBackgroundBlock(x, y) {
        sprite.setTexture(imageManager.getBackgroundBricks());
    }
};
