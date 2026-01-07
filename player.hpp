#pragma once
#include "abstractGameObjects.hpp"
#include "images.hpp"
#include "counters.hpp"
#include "direction.hpp"

class Player : public AbstractGameObject {
protected:
    float SPEED = 5;
    float GRAVITY = 1;
    float JUMP_POWER = -15;

    float xvel = 0;
    float yvel = 0;
    bool onGround = false;
    Direction direction = Direction::RIGHT;
    bool onLadder = false;

    vector<AbstractBlock>& blocks;

    vector<Texture> standTextures = images::playerStand;
    vector<Texture> goTextures = images::playerGo;
    vector<Texture> goVerticalTextures = images::playerGoVertical;

    FrameCounter standAnim = FrameCounter(standTextures.size(), 1);
    FrameCounter goAnim = FrameCounter(goTextures.size(), 0.2);
    FrameCounter goVerticalAnim = FrameCounter(goVerticalTextures.size(), 0.2);

    void updateXvel() {
        xvel = 0;
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            xvel = SPEED;
            if (direction == Direction::LEFT) {
                flipSprite(1);
            }
            direction = Direction::RIGHT;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            xvel = -SPEED;
            if (direction == Direction::RIGHT) {
                flipSprite(-1);
            }
            direction = Direction::LEFT;
        }
    }

    void flipSprite(int sign) {
        sprite.setPosition(sprite.getPosition().x - sign * sprite.getGlobalBounds().width, sprite.getPosition().y);
        sprite.setScale(sign * 1.f, 1.f);
    }

    void updateYvel() {
        if (Keyboard::isKeyPressed(Keyboard::Space) && onGround) {
            yvel = JUMP_POWER;
        }
        onGround = false;

        if (!onLadder) {
            yvel += GRAVITY;
        }
        else if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Space)) {
            yvel = -SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::S)) {
            yvel = SPEED;
        }
        else {
            yvel = 0;
        }
    }

    void updateRectXY() {
        sprite.move(xvel, 0);
        handleCollisionWithBlocks(xvel, 0);
        sprite.move(0, yvel);
        handleCollisionWithBlocks(0, yvel);
    }

    void handleCollisionWithBlocks(int _xvel, int _yvel) {
        FloatRect rect;
        for (AbstractBlock& block : blocks) {
            rect = block.getSprite().getGlobalBounds();
            handleCollisionWithRect(_xvel, _yvel, rect);
        }
    }

    void handleCollisionWithRect(int _xvel, int _yvel, FloatRect& blockRect) {
        if (!blockRect.intersects(sprite.getGlobalBounds())) {
            return;
        }

        Vector2f pos = sprite.getPosition();
        if (_xvel > 0) {
            pos.x = blockRect.left - sprite.getGlobalBounds().width;
            xvel = 0;
        }
        else if (_xvel < 0) {
            // Необходимо прибавить ширину игрока, поскольку реальная Х координата изменена из-за преобразования с setScale.
            pos.x = blockRect.left + blockRect.width + sprite.getGlobalBounds().width;
            xvel = 0;
        }
        else if (_yvel > 0) {
            pos.y = blockRect.top - sprite.getGlobalBounds().height;
            yvel = 0;
            onGround = true;
        }
        else if (_yvel < 0) {
            pos.y = blockRect.top + blockRect.height;
            yvel = 0;
        }
        sprite.setPosition(pos);
    }

    void updateTexture() override {
        if (onLadder) {
            sprite.setTexture(goVerticalTextures[goVerticalAnim.getCurrentIndex()]);
        }
        else if (xvel > 0) {
            sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
        }
        else if (xvel < 0) {
            sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
        }
        else {
            sprite.setTexture(standTextures[standAnim.getCurrentIndex()]);
        }

        if (yvel != 0 && onLadder) {
            goVerticalAnim.next();
        }
        else if (xvel != 0) {
            goAnim.next();
        }
        else {
            standAnim.next();
        }
    }

public:
    Player(vector<AbstractBlock>& blocks) : AbstractGameObject(0, 0), blocks(blocks) {}

    void reset(int x, int y) {
        sprite.setPosition(x, y);
    }

    void update() {
        updateXvel();
        updateYvel();
        updateRectXY();
        AbstractGameObject::update();

        onLadder = false;
    }

    void setAsOnLadder() {
        onLadder = true;
    }

};
