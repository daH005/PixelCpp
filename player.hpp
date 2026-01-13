#pragma once
#include "abstractGameObject.hpp"
#include "images.hpp"
#include "counters.hpp"
#include "direction.hpp"

class Player : public AbstractGameObject {
protected:
    inline static const float SPEED = 5;
    inline static const float GRAVITY = 1;
    inline static const float GRAVITY_IN_WATER = GRAVITY;  // Если меньше 1, то некорректно работает коллизия с блоками, пока игрок внутри воды.
    inline static const float JUMP_POWER = -15;
    inline static const short MAX_HP = 3;

    short hp = MAX_HP;
    float xvel = 0;
    float yvel = 0;
    bool onGround = false;
    Direction direction = Direction::RIGHT;
    bool onLadder = false;
    bool inWater = false;
    bool hasShield = false;

    vector<FloatRect> blockRects;

    const vector<Texture>* standTextures = &images::playerStand;
    const vector<Texture>* goTextures = &images::playerGo;
    const vector<Texture>* goVerticalTextures = &images::playerGoVertical;

    FrameIndexCyclicalCounter standAnim = FrameIndexCyclicalCounter(standTextures->size(), 1);
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures->size(), 0.2);
    FrameIndexCyclicalCounter goVerticalAnim = FrameIndexCyclicalCounter(goVerticalTextures->size(), 0.2);

    FPSBasedTimer godModeFPSBasedTimer = FPSBasedTimer(1.2);
    FPSBasedTimer flashFPSBasedTimer = FPSBasedTimer(0.1);
    int beWhiteFrameCount = convertSecondsToFrameCount(0.5);
    bool isInvisible = false;

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

        if (!onLadder && !inWater) {
            yvel += GRAVITY;
        }
        else if (inWater) {
            yvel = GRAVITY_IN_WATER;
        }
        else {
            yvel = 0;
        }

        if (onLadder || inWater) {
            if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Space)) {
                yvel = -SPEED;
            }
            else if (Keyboard::isKeyPressed(Keyboard::S)) {
                yvel = SPEED;
            }
        }
    }

    void updateRectXY() {
        sprite.move(xvel, 0);
        handleCollisionWithBlocks(xvel, 0);
        sprite.move(0, yvel);
        handleCollisionWithBlocks(0, yvel);
    }

    void handleCollisionWithBlocks(int _xvel, int _yvel) {
        for (FloatRect& blockRect : blockRects) {
            handleCollisionWithRect(_xvel, _yvel, blockRect);
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
        if (godModeFPSBasedTimer.delta() <= beWhiteFrameCount) {
            goTextures = &images::whitePlayerGo;
            standTextures = &images::whitePlayerStand;
            goVerticalTextures = &images::whitePlayerGoVertical;
        }
        else {
            goTextures = &images::playerGo;
            standTextures = &images::playerStand;
            goVerticalTextures = &images::playerGoVertical;
        }

        if (onLadder) {
            sprite.setTexture(goVerticalTextures->at(goVerticalAnim.getCurrentIndex()));
        }
        else if (xvel > 0) {
            sprite.setTexture(goTextures->at(goAnim.getCurrentIndex()));
        }
        else if (xvel < 0) {
            sprite.setTexture(goTextures->at(goAnim.getCurrentIndex()));
        }
        else {
            sprite.setTexture(standTextures->at(standAnim.getCurrentIndex()));
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

    void draw() override {
        if (godModeFPSBasedTimer.isWorking()) {
            if (!flashFPSBasedTimer.isWorking()) {
                isInvisible = !isInvisible;
                flashFPSBasedTimer.restart();
            }
            flashFPSBasedTimer.next();

            if (!isInvisible) {
                AbstractGameObject::draw();
            }
        }
        else {
            AbstractGameObject::draw();
        }
    }

public:
    Player() : AbstractGameObject(0, 0, ZIndex::MOVING_OBJECT) {}

    void reset() {
        hp = MAX_HP;
        blockRects.clear();
    }

    void setPosition(int x, int y) {
        sprite.setPosition(x, y);
    }

    void addBlockRect(const FloatRect& rect) {
        blockRects.push_back(rect);
    }

    void update() override {
        updateXvel();
        updateYvel();
        updateRectXY();
        AbstractGameObject::update();

        onLadder = false;
        inWater = false;
        godModeFPSBasedTimer.next();
    }

    void setAsOnLadder() {
        onLadder = true;
    }

    void setAsInWater() {
        inWater = true;
    }

    float getXvel() const {
        return xvel;
    }

    float getYvel() const {
        return yvel;
    }

    short getMaxHP() const {
        return MAX_HP;
    }

    short getHP() const {
        return hp;
    }

    bool getHasShield() const {
        return hasShield;
    }

    bool addHP() {
        if (hp < MAX_HP) {
            hp++;
            return true;
        }
        return false;
    }

    bool addShield() {
        if (!hasShield) {
            hasShield = true;
            return true;
        }
        return false;
    }
    
    void hit(float xPush = 0, float yPush = 0, int enemyCenter = NULL) {
        if (!godModeFPSBasedTimer.isWorking()) {
        if (hasShield) {
            hasShield = false;
        }
        else {
            hp--;
        }
            godModeFPSBasedTimer.restart();
        }

        if (yPush > 0) {
            yvel = -yPush;
        }

        if (xPush > 0 && enemyCenter != NULL) {
            int thisCenter = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2;
            if (thisCenter < enemyCenter) {
                xvel = -xPush;
            }
            else if (thisCenter > enemyCenter) {
                xvel = xPush;
            }
        }
    }

};
