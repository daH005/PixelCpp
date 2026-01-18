#pragma once
#include "abstractEnemies.hpp"

class Skeleton : public AbstractXPatrolEnemy {
protected:
    inline static const vector<Texture> goTextures = images::skeletonGo;
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.1);

    inline static const vector<Texture> attackTextures = images::skeletonAttack;
    FrameIndexFiniteCounter attackAnim = FrameIndexFiniteCounter(attackTextures.size(), 0.1);

    int attackAnimLeftXIndents[3] = { 0, 0, 72 };
    int attackAnimRightXIndents[3] = { 28, 28, 0 };
    int* attackIndents;

    inline static const int ATTACK_ANIM_INDEX_TO_HIT = 2;

    int backupX;
    int backupY;
    int backupBottomY;
    Direction backupDirection;

    void _handleCollisionWithPlayer() override {
        if (attackAnim.getIsEnded()) {
            attackAnim.restart();
            backupSpriteValuesBeforeAttack();
            flipSpriteToPlayerDirectionAndSetIndents();
        }
        else if (attackAnim.getCurrentIndex() == ATTACK_ANIM_INDEX_TO_HIT) {
            attack();
        }
    }

    void backupSpriteValuesBeforeAttack() {
        backupX = sprite.getGlobalBounds().left;
        backupY = sprite.getGlobalBounds().top;
        backupBottomY = backupY + sprite.getGlobalBounds().height;
        backupDirection = direction;
    }

    void flipSpriteToPlayerDirectionAndSetIndents() {
        if (player->getCenter() <= getCenter()) {
            flipSprite(Direction::LEFT);
            attackIndents = attackAnimLeftXIndents;
        }
        else {
            flipSprite(Direction::RIGHT);
            attackIndents = attackAnimRightXIndents;
        }
    }

    void attack() {
        player->hitWithStun();
        player->pushY(yPush);
        player->pushX(xPush * direction);
    }

    void move() override {
        if (attackAnim.getIsEnded()) {
            AbstractXPatrolEnemy::move();
        }
    }

    void updateTexture() override {
        if (!attackAnim.getIsEnded()) {
            setCurrentAttackTexture();
            attackAnim.next();
            if (attackAnim.getIsEnded()) {
                returnSpriteToStateBeforeAttack();
            }
        }
        else {
            sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
            goAnim.next();
        }
    }

    void setCurrentAttackTexture() {
        sprite.setTexture(attackTextures[attackAnim.getCurrentIndex()], true);
        updateOrigin();
        sprite.setPosition(
            backupX - attackIndents[attackAnim.getCurrentIndex()],
            backupBottomY - attackTextures[attackAnim.getCurrentIndex()].getSize().y
        );
    }

    void returnSpriteToStateBeforeAttack() {
        sprite.setTexture(goTextures[goAnim.getCurrentIndex()], true);
        updateOrigin();
        flipSprite(backupDirection);
        sprite.setPosition(backupX, backupY);
    }

public:
    Skeleton(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 1.2f, 35, 3) {}
};
