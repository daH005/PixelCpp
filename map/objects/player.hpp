#pragma once
#include "../../common/images.hpp"
#include "../../common/counters.hpp"
#include "../../common/direction.hpp"
#include "abstract/abstractGameObject.hpp"

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
    float currentXpush = 0;
    bool onGround = false;
    bool onLadder = false;
    bool inWater = false;
    bool hasShield = false;
    int mapW;
    int mapH;
    bool isFinished = false;

    vector<FloatRect> blockRects;

    const vector<Texture>* standTextures = &images::playerStand;
    const vector<Texture>* goTextures = &images::playerGo;
    const vector<Texture>* goVerticalTextures = &images::playerGoVertical;

    FrameIndexCyclicalCounter standAnim = FrameIndexCyclicalCounter(standTextures->size(), 1);
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures->size(), 0.2);
    FrameIndexCyclicalCounter goVerticalAnim = FrameIndexCyclicalCounter(goVerticalTextures->size(), 0.2);

    FPSBasedTimer godModeTimer = FPSBasedTimer(1.2);
    FPSBasedTimer flashTimer = FPSBasedTimer(0.1);
    int beWhiteFrameCount = convertSecondsToFrameCount(0.5);
    bool isInvisible = false;

    inline static const int STUN_SPRITE_Y_INDENT = 20;
    inline static const vector<Texture> stunTextures = images::stun;
    FrameIndexCyclicalCounter stunAnim = FrameIndexCyclicalCounter(stunTextures.size(), 0.1);
    SpriteWrapper stunSprite;
    bool isStunned = false;

    void updateXvel() {
        if (currentXpush != 0) {
            xvel = currentXpush;
            decreaseXpush();
            return;
        }

        xvel = 0;
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            xvel = SPEED;
            sprite.setDirection(Direction::RIGHT);
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            xvel = -SPEED;
            sprite.setDirection(Direction::LEFT);
        }

        if (isStunned) {
            xvel = 0;
        }
    }

    void decreaseXpush() {
        if (abs(currentXpush) <= SPEED) {
            currentXpush = 0;
        }
        else {
            if (currentXpush > 0) {
                currentXpush -= SPEED;
            }
            else {
                currentXpush += SPEED;
            }
        }
    }

    void updateYvel() {
        if (Keyboard::isKeyPressed(Keyboard::Space) && onGround && !isStunned) {
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

        if (onLadder || inWater && !isStunned) {
            if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Space)) {
                yvel = -SPEED;
            }
            else if (Keyboard::isKeyPressed(Keyboard::S)) {
                yvel = SPEED;
            }
        }
    }

    void updateRectXY() {
        sprite.moveX(xvel);
        handleCollisionWithBlocks(xvel, 0);
        handleMapEdges();
        sprite.moveY(yvel);
        handleCollisionWithBlocks(0, yvel);
    }

    void handleMapEdges() {
        if (sprite.getLeft() < 0 || sprite.getRight() > mapW) {
            sprite.moveX(-xvel);
        }
        if (sprite.getTop() > mapH) {
            hp = 0;
        }
    }

    void handleCollisionWithBlocks(int _xvel, int _yvel) {
        for (FloatRect& blockRect : blockRects) {
            handleCollisionWithRect(_xvel, _yvel, blockRect);
        }
    }

    void handleCollisionWithRect(int _xvel, int _yvel, FloatRect& blockRect) {
        if (!sprite.intersects(blockRect)) {
            return;
        }

        int newX = sprite.getLeft();
        int newY = sprite.getTop();
        if (_xvel > 0) {
            newX = blockRect.left - sprite.getWidth();
            xvel = 0;
        }
        else if (_xvel < 0) {
            newX = blockRect.left + blockRect.width;
            xvel = 0;
        }
        else if (_yvel > 0) {
            newY = blockRect.top - sprite.getHeight();
            yvel = 0;
            onGround = true;
        }
        else if (_yvel < 0) {
            newY = blockRect.top + blockRect.height;
            yvel = 0;
        }
        sprite.setPosition(newX, newY);
    }

    void draw() override {
        if (isInvisibleForFlashing()) {
            return;
        }

        if (godModeTimer.delta() <= beWhiteFrameCount) {
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

        AbstractGameObject::draw();
        drawStun();
    }

    bool isInvisibleForFlashing() {
        if (godModeTimer.isWorking()) {
            if (!flashTimer.isWorking()) {
                isInvisible = !isInvisible;
                flashTimer.restart();
            }
            flashTimer.next();

            if (!isInvisible) {
                return false;
            }
        }
        else {
            return false;
        }
        
        return true;
    }

    void drawStun() {
        if (isStunned) {
            stunSprite.setPosition(sprite.getLeft(), sprite.getTop() - STUN_SPRITE_Y_INDENT);
            stunSprite.setTexture(stunTextures[stunAnim.getCurrentIndex()]);
            stunAnim.next();
            stunSprite.draw();
        }
    }

public:
    Player() : AbstractGameObject(0, 0, ZIndex::MOVING_OBJECT) {}

    void reset(int _mapW, int _mapH) {
        hp = MAX_HP;
        blockRects.clear();
        mapW = _mapW;
        mapH = _mapH;
        isFinished = false;
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
        godModeTimer.next();
        if (!godModeTimer.isWorking()) {
            isStunned = false;
        }
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

    bool isInGodMode() const {
        return godModeTimer.isWorking();
    }

    bool getIsFinished() const {
        return isFinished;
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

    void hit() {
        if (!godModeTimer.isWorking()) {
            if (hasShield) {
                hasShield = false;
            }
            else {
                hp--;
            }
            godModeTimer.restart();
        }
    }

    void hitWithStun() {
        isStunned = true;
        hit();
    }

    void pushY(float value) {
        yvel = value;
    }

    void pushX(float value) {
        currentXpush = value;
    }

    void pushX(float absValue, int enemyCenter) {
        if (sprite.getCenterX() < enemyCenter) {
            pushX(-absValue);
        }
        else {
            pushX(absValue);
        }
    }

    void jump(float power) {
        yvel = power;
    }

    void finish() {
        isFinished = true;
    }

};
