#pragma once
#include "abstract/abstractXPatrolEnemy.hpp"

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

    void handleCollisionWithPlayerAction() override {
        if (attackAnim.getIsEnded()) {
            attackAnim.restart();
            prepareBeforeAttackAnim();
        }
        else if (attackAnim.getCurrentIndex() == ATTACK_ANIM_INDEX_TO_HIT) {
            attack();
        }
    }

    void prepareBeforeAttackAnim() {
        backupSpriteValuesBeforeAttack();
        if (player->getSprite().getCenterX() <= sprite.getCenterX()) {
            sprite.setDirection(Direction::LEFT);
            attackIndents = attackAnimLeftXIndents;
        }
        else {
            sprite.setDirection(Direction::RIGHT);
            attackIndents = attackAnimRightXIndents;
        }
    }

    void backupSpriteValuesBeforeAttack() {
        backupX = sprite.getLeft();
        backupY = sprite.getTop();
        backupBottomY = sprite.getBottom();
        backupDirection = sprite.getDirection();
    }

    void attack() {
        player->hitWithStun();
        player->pushY(yPush);
        player->pushX(xPush * sprite.getDirection());
    }

    void move() override {
        if (attackAnim.getIsEnded()) {
            AbstractXPatrolEnemy::move();
        }
    }

    void draw() override {
        if (!attackAnim.getIsEnded()) {
            setCurrentAttackTexture();
            attackAnim.next();
            if (attackAnim.getIsEnded()) {
                returnToStateBeforeAttackAnim();
            }
        }
        else {
            sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
            goAnim.next();
        }
        AbstractXPatrolEnemy::draw();
    }

    void setCurrentAttackTexture() {
        sprite.setTextureWithRectUpdating(attackTextures[attackAnim.getCurrentIndex()]);
        sprite.setPosition(
            backupX - attackIndents[attackAnim.getCurrentIndex()],
            backupBottomY - attackTextures[attackAnim.getCurrentIndex()].getSize().y
        );
    }

    void returnToStateBeforeAttackAnim() {
        sprite.setTextureWithRectUpdating(goTextures[goAnim.getCurrentIndex()]);
        sprite.setDirection(backupDirection);
        sprite.setPosition(backupX, backupY);
    }

public:
    Skeleton(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 1.2, 35, 3) {}
};
