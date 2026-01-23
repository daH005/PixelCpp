#pragma once
#include "abstractXPatrolEnemy.hpp"

class Dragon : public AbstractXPatrolEnemy {
protected:
    inline static const vector<Texture> goTextures = images::dragonDefaultGo;
    inline static const vector<Texture> goWhenAttacksTextures = images::dragonGoWhenAttacks;
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.2);

    SpriteWrapper fireSprite;
    inline static const vector<Texture> fireTextures = images::dragonFire;
    FrameIndexFiniteCounter fireAnim = FrameIndexFiniteCounter(fireTextures.size(), 0.1);
    FPSBasedTimer fireReloadTimer = FPSBasedTimer(0.5);

    inline static const int TOP_FIRE_INDENT = 120;
    inline static const int SIDE_FIRE_INDENT = 40;

    FloatRect reactionRect = FloatRect(0, 0, 100, 200);

    void handleCollisionReactionRectWithPlayer() {
        updateReactionRectPosition();
        if (player->getSprite().intersects(reactionRect) && fireAnim.getIsEnded() && !fireReloadTimer.isWorking()) {
            fireAnim.restart();
        }
    }

    void updateReactionRectPosition() {
        reactionRect.top = sprite.getTop() + TOP_FIRE_INDENT;
        if (sprite.getDirection() == Direction::LEFT) {
            reactionRect.left = sprite.getLeft() - reactionRect.width + SIDE_FIRE_INDENT;
        }
        else {
            reactionRect.left = sprite.getRight() - SIDE_FIRE_INDENT;
        }
    }

    void handleCollisionFireWithPlayer() {
        if (player->getSprite().intersects(fireSprite) && !fireAnim.getIsEnded()) {
            player->hit();
            player->pushY(yPush);
            player->pushX(xPush, fireSprite.getCenterX());
        }
    }

    void move() override {
        if (fireAnim.getIsEnded()) {
            AbstractXPatrolEnemy::move();
        }
    }

    void draw() override {
        if (!fireAnim.getIsEnded()) {
            sprite.setTexture(goWhenAttacksTextures[goAnim.getCurrentIndex()]);

            fireSprite.setDirection(sprite.getDirection());
            fireSprite.setTextureWithRectUpdating(fireTextures[fireAnim.getCurrentIndex()]);

            fireSprite.setTop(sprite.getTop() + TOP_FIRE_INDENT);
            if (fireSprite.getDirection() == Direction::LEFT) {
                fireSprite.setRight(sprite.getLeft() + SIDE_FIRE_INDENT);
            }
            else {
                fireSprite.setLeft(sprite.getRight() - SIDE_FIRE_INDENT);
            }
            fireSprite.draw();

            fireAnim.next();
            if (fireAnim.getIsEnded()) {
                fireReloadTimer.restart();
                // Вернуть малые размеры спрайту огня, чтобы при новой атаке он не зарегистрировал урон 
                // игроку из-за большого размера, оставшегося с прошлой анимации.
                fireSprite.setTextureWithRectUpdating(fireTextures[0]);
            }
        }
        else {
            sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
        }
        goAnim.next();
        AbstractXPatrolEnemy::draw();
    }

public:
    Dragon(int x, int y, Player* player, int startX, int endX) : AbstractXPatrolEnemy(x, y, player, startX, endX, 1, 50, 100, ZIndex::DRAGON) {}

    void update() override {
        handleCollisionReactionRectWithPlayer();
        handleCollisionFireWithPlayer();
        AbstractXPatrolEnemy::update();
        fireReloadTimer.next();
    }

};
