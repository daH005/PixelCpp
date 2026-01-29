#pragma once
#include "abstract/abstractXPatrolEnemy.hpp"

class Ghost : public AbstractXPatrolEnemy {
protected:
    inline static const Texture defaultTexture = images::ghostDefault;
    inline static const Texture attackTexture = images::ghostAttack;

    inline static const float ATTACK_SPEED = 3;
    inline static const int Y_DEVIATION = 3;
    inline static const float Y_DEVIATION_SPEED = 0.2;

    int startDeviationY;
    int endDeviationY = startDeviationY + Y_DEVIATION * 2;
    float deviationYvel = Y_DEVIATION_SPEED;

    bool isAttacking = false;
    Direction directionBackup;
    FloatRect reactionRect = FloatRect(0, 0, 350, images::ghostDefault.getSize().y);

    void handleCollisionReactionRectWithPlayer() {
        updateReactionRectPosition();
        if (player->getSprite().intersects(reactionRect)) {
            if (!isAttacking) {
                setSpriteToAttackState();
            }
            isAttacking = true;
        } else {
            if (isAttacking) {
                returnSpriteToDefaultState();
            }
            isAttacking = false;
        }
    }

    void updateReactionRectPosition() {
        reactionRect.left = sprite.getCenterX() - reactionRect.width / 2;
        reactionRect.top = sprite.getTop();
    }

    void setSpriteToAttackState() {
        directionBackup = sprite.getDirection();
        sprite.setTexture(attackTexture);
    }

    void returnSpriteToDefaultState() {
        sprite.setDirection(directionBackup);
        sprite.setTexture(defaultTexture);
    }

    void move() override {
        deviateY();
        if (isAttacking) {
            moveToPlayer();
        } else {
            AbstractXPatrolEnemy::move();
        }
    }

    void deviateY() {
        sprite.moveY(deviationYvel);
        if (sprite.getTop() < startDeviationY) {
            deviationYvel = Y_DEVIATION_SPEED;
        } else if (sprite.getTop() > endDeviationY) {
            deviationYvel = -Y_DEVIATION_SPEED;
        }
    }

    void moveToPlayer() {
        Direction xDirection = defineDirection(player->getSprite().getCenterX() - sprite.getCenterX());
        sprite.setDirection(xDirection);
        sprite.moveX(ATTACK_SPEED * xDirection);
    }

public:
    Ghost(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 1, 15, 0), startDeviationY(y - Y_DEVIATION) {
        sprite.setTexture(defaultTexture);
    }

    void update() override {
        handleCollisionReactionRectWithPlayer();
        AbstractXPatrolEnemy::update();
    }

};
