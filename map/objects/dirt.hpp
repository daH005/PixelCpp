#pragma once
#include "../../common/images.hpp"
#include "../../common/direction.hpp"
#include "abstract/abstractBlock.hpp"
#include "abstract/abstractBackground.hpp"

class Dirt : public AbstractBlock {
protected:
    inline static int currentGrassIndex = 0;
    SpriteWrapper grassSprite;

    Direction direction;
    bool withGrass;

    void draw() override {
        AbstractBlock::draw();
        grassSprite.draw();
    }

    void initImage() {
        if (direction == Direction::LEFT) {
            sprite.setTexture(images::leftDirt);
        }
        else if (direction == Direction::RIGHT) {
            sprite.setTexture(images::rightDirt);
        }
        else {
            sprite.setTexture(images::dirt);
        }

        if (withGrass) {
            grassSprite.setTexture(images::grasses[currentGrassIndex]);
            currentGrassIndex++;
            if (currentGrassIndex > images::grasses.size() - 1) {
                currentGrassIndex = 0;
            }
        }
    }

public:
    Dirt(int x, int y, Player* player, Direction direction = Direction::NO, bool withGrass = false) : AbstractBlock(x, y, player), direction(direction), withGrass(withGrass) {
        initImage();
        grassSprite.setPosition(x, y);
    }

    static void resetGrass() {
        currentGrassIndex = 0;
    }
};

class BackgroundDirt : public AbstractBackground {
public:
    BackgroundDirt(int x, int y) : AbstractBackground(x, y) {
        sprite.setTexture(images::backgroundDirt);
    }
};
