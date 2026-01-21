#pragma once
#include "abstractXPatrolEnemy.hpp"

class Dragon : public AbstractXPatrolEnemy {
protected:
    inline static const vector<Texture> goTextures = images::dragonGo;
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.2);

    inline static const vector<Texture> attackTextures = images::dragonAttack;
    FrameIndexFiniteCounter attackAnim = FrameIndexFiniteCounter(attackTextures.size(), 0.1);
    inline static const int LEFT_ATTACK_ANIM_INDENT = -24;

    FloatRect reactionRect = FloatRect(0, 0, images::dragonAttack[5].getSize().x, images::dragonAttack[5].getSize().y);

    void handleCollisionReactionRectWithPlayer() {
        reactionRect.left = sprite.getLeft();
        reactionRect.top = sprite.getTop();

        if (player->getSprite().intersects(reactionRect) && attackAnim.getIsEnded()) {
            attackAnim.restart();
            prepareBeforeAttackAnim();
        }
    }

    void prepareBeforeAttackAnim() {
        if (sprite.getDirection() == Direction::LEFT) {
            sprite.moveX(LEFT_ATTACK_ANIM_INDENT);
        }
    }

    void draw() override {
        if (!attackAnim.getIsEnded()) {
            sprite.setTextureWithRectUpdating(attackTextures[attackAnim.getCurrentIndex()]);

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

    void returnToStateBeforeAttackAnim() {
        sprite.setTextureWithRectUpdating(goTextures[0]);
        if (sprite.getDirection() == Direction::LEFT) {
            sprite.moveX(-LEFT_ATTACK_ANIM_INDENT);
        }
    }

public:
    Dragon(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 1, 0, 100) {}

    void update() override {
        handleCollisionReactionRectWithPlayer();
        AbstractXPatrolEnemy::update();
    }

};
