#pragma once
#include "abstractEnemies.hpp"

class Slug : public AbstractXPatrolEnemy {
protected:
    inline static const float PLAYER_Y_VEL_FOR_DEATH = 8.f;
    inline static const vector<Texture> goTextures = images::slugGo;
    inline static const vector<Texture> deathTextures = images::slugDeath;

    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.1);
    FrameIndexFiniteCounter deathAnim = FrameIndexFiniteCounter(deathTextures.size(), 0.2);

    void _handleCollisionWithPlayer() override {
        float playerYvel = player->getYvel();
        if (playerYvel >= PLAYER_Y_VEL_FOR_DEATH && !player->isInGodMode() && deathAnim.getIsEnded()) {
            die();
            player->jump(-playerYvel);
        }
        else if (deathAnim.getIsEnded()) {
            AbstractXPatrolEnemy::_handleCollisionWithPlayer();
        }
    }

    void die() {
        deathAnim.restart();
        prepareRectForDeathAnim();
    }

    void prepareRectForDeathAnim() {
        int newX = getCenter() - deathTextures[0].getSize().x / 2;
        sprite.setTexture(deathTextures[0], true);
        sprite.setPosition(newX, sprite.getPosition().y);
    }

    void move() override {
        if (deathAnim.getIsEnded()) {
            AbstractXPatrolEnemy::move();
        }
    }

    void updateTexture() override {
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
    }

public:
    Slug(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 0.5f, 25, 13) {}
};
