#pragma once
#include <iostream>

#include "abstractGameObjects.hpp"
#include "imageManager.hpp"
#include "direction.hpp"

int currentGrassIndex = 0;

class Dirt : public AbstractBlock {
protected:
    Sprite grassSprite;

    Direction direction;
    bool withGrass;

    void initImage() {
        if (direction == Direction::LEFT) {
            sprite.setTexture(imageManager.getLeftDirt());
        }
        else if (direction == Direction::RIGHT) {
            sprite.setTexture(imageManager.getRightDirt());
        }
        else {
            sprite.setTexture(imageManager.getDirt());
        }

        if (withGrass) {
            grassSprite.setTexture(imageManager.getGrasses()[currentGrassIndex]);
            currentGrassIndex++;
            if (currentGrassIndex > imageManager.getGrasses().size() - 1) {
                currentGrassIndex = 0;
            }
        }
    }

public:
    Dirt(int x, int y, Direction direction = Direction::NO, bool withGrass = false) : AbstractBlock(x, y), direction(direction), withGrass(withGrass) {
        initImage();
        grassSprite.setPosition(x, y);
    }

    void update() {
        AbstractBlock::update();
        window->draw(grassSprite);
    }
};

class BackgroundDirt : public AbstractBackgroundBlock {
public:
    BackgroundDirt(int x, int y) : AbstractBackgroundBlock(x, y) {
        sprite.setTexture(imageManager.getBackgroundDirt());
    }
};
