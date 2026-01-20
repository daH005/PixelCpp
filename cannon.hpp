#pragma once
#include "AbstractEnemy.hpp"

class Cannonball : public AbstractEnemy {
protected:
    inline static const Texture defaultTexture = images::cannonballDefault;
    inline static const vector<Texture> deathTextures = images::cannonballDeath;
    FrameIndexFiniteCounter deathAnim = FrameIndexFiniteCounter(deathTextures.size(), 0.05);

    inline static const int PUSH_X = 50;
    int endX;
    float xvel;

    void handleCollisionWithPlayerAction() override {
        if (deathAnim.getIsEnded()) {
            deathAnim.restart();
        }
        player->hitWithStun();
        player->pushX(PUSH_X * sprite.getDirection());
    }

    void draw() override {
        if (!deathAnim.getIsEnded()) {
            sprite.setTexture(deathTextures[deathAnim.getCurrentIndex()]);

            deathAnim.next();
            if (deathAnim.getIsEnded()) {
                toBeDeleted = true;
            }
        }
        AbstractEnemy::draw();
    }

    void move() {
        if (deathAnim.getIsEnded()) {
            sprite.moveX(xvel);
        }
    }

public:
    Cannonball(int x, int y, Player* player, int endX) : AbstractEnemy(x, y, player, 11), endX(endX) {
        sprite.setTexture(defaultTexture);
        sprite.setCenterX(x);
        if (endX < x) {
            xvel = -speed;
            sprite.setDirection(Direction::LEFT);
        }
        else {
            xvel = speed;
        }
    }

    void update() override {
        move();
        if (((xvel < 0 && sprite.getLeft() <= endX) || (xvel > 0 && sprite.getRight() >= endX)) && deathAnim.getIsEnded()) {
            deathAnim.restart();
        }
        AbstractEnemy::update();
    }

};

class Cannon : public AbstractGameObject {
protected:
    inline static const Texture defaultTexture = images::cannonDefault;
    inline static const vector<Texture> shootTextures = images::cannonShoot;
    FrameIndexFiniteCounter shootAnim = FrameIndexFiniteCounter(shootTextures.size(), 0.2);
    FPSBasedTimer reloadTimer = FPSBasedTimer(0.5);

    inline static const int SHOOT_ANIM_INDEX_TO_SPAWN_BALL = 4;

    Player* player;
    int ballEndX;
    int ballStartX;
    int ballStartY;
    vector<Cannonball> balls;
    bool ballWasSpawned = false;

    void draw() override {
        if (!shootAnim.getIsEnded()) {
            sprite.setTexture(shootTextures[shootAnim.getCurrentIndex()]);
            shootAnim.next();
            if (shootAnim.getIsEnded()) {
                setReloadState();
            }
        }
        AbstractGameObject::draw();
    }

    void setReloadState() {
        sprite.setTexture(defaultTexture);
        reloadTimer.restart();
    }

    void updateBalls() {
        for (auto it = balls.begin(); it != balls.end(); ) {
            it->update();
            if (it->getToBeDeleted()) {
                it = balls.erase(it);
            }
            else {
                it++;
            }
        }
    }

public:
    Cannon(int x, int y, Player* player, int endX) : AbstractGameObject(x, y), player(player), ballEndX(endX), ballStartY(y + 12) {
        setReloadState();  // Перед flip нужно задать начальный rect.
        if (endX < x) {
            sprite.setDirection(Direction::LEFT);
            ballStartX = x;
        }
        else {
            ballStartX = x + sprite.getWidth();
        }
    }

    void update() override {
        if (reloadTimer.isWorking()) {
            reloadTimer.next();
            if (!reloadTimer.isWorking()) {
                shootAnim.restart();
            }
        }

        if (shootAnim.getCurrentIndex() == SHOOT_ANIM_INDEX_TO_SPAWN_BALL) {
            if (!ballWasSpawned) {
                balls.push_back(Cannonball(ballStartX, ballStartY, player, ballEndX));
                ballWasSpawned = true;
            }
        }
        else {
            ballWasSpawned = false;
        }

        updateBalls();
        AbstractGameObject::update();
    }

};
