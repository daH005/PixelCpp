#pragma once
#include "abstractXPatrolEnemy.hpp"

class Slug : public AbstractXPatrolEnemy {
protected:
    inline static const float PLAYER_Y_VEL_FOR_DEATH = 8;
    inline static const vector<Texture> goTextures = images::slugGo;
    inline static const vector<Texture> deathTextures = images::slugDeath;

    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.1);
    FrameIndexFiniteCounter deathAnim = FrameIndexFiniteCounter(deathTextures.size(), 0.15);

    void handleCollisionWithPlayerAction() override {
        float playerYvel = player->getYvel();
        if (playerYvel >= PLAYER_Y_VEL_FOR_DEATH && !player->isInGodMode() && deathAnim.getIsEnded()) {
            die();
            player->jump(-playerYvel);
        }
        else if (deathAnim.getIsEnded()) {
            AbstractXPatrolEnemy::handleCollisionWithPlayerAction();
        }
    }

    void die() {
        deathAnim.restart();
        prepareBeforeDeathAnim();
    }

    void prepareBeforeDeathAnim() {
        sprite.setDirection(Direction::RIGHT);  // Ќужно вернуть спрайт в изначальное положение дл€ корректного отображени€ текстур смерти.
        int newX = sprite.getCenterX() - deathTextures[0].getSize().x / 2;
        sprite.setTextureWithRectUpdating(deathTextures[0]);
        sprite.setLeft(newX);
    }

    void move() override {
        if (deathAnim.getIsEnded()) {
            AbstractXPatrolEnemy::move();
        }
    }

    void draw() override {
        if (deathAnim.getIsEnded()) {
            sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
            goAnim.next();
        }
        else {
            sprite.setTexture(deathTextures[deathAnim.getCurrentIndex()]);

            deathAnim.next();
            if (deathAnim.getIsEnded()) {
                toBeDeleted = true;
            }
        }
        AbstractXPatrolEnemy::draw();
    }

public:
    Slug(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 0.5f, 25, 13) {}
};
