#pragma once
#include "abstractEnemy.hpp"

class SpiderWeb {
protected:
    inline static const int WIDTH = 2;
    RectangleShape shape;

public:
    SpiderWeb(int x, int y) {
        shape.setPosition(x, y);
        shape.setFillColor(Color::White);
    }

    void setHeight(int height) {
        shape.setSize(Vector2f(WIDTH, height));
    }

    void draw() {
        window->draw(shape);
    }

};

class Spider : public AbstractEnemy {
protected:
    inline static const Texture standTexture = images::spiderStand;
    inline static const vector<Texture> goTextures = images::spiderGo;
    FrameIndexCyclicalCounter goAnim = FrameIndexCyclicalCounter(goTextures.size(), 0.05);
    
    inline static const int Y_PUSH_TO_CATCH_PLAYER = -3;
    inline static const int WEB_WIDTH = 2;

    int startY;
    int endY;

    FloatRect reactionRect;
    float yvel;
    SpiderWeb web;

    void handleCollisionWithPlayerAction() override {
        player->pushY(Y_PUSH_TO_CATCH_PLAYER);
        AbstractEnemy::handleCollisionWithPlayerAction();
    }

    void handleCollisionReactionRectWithPlayer() {
        if (player->getSprite().intersects(reactionRect) && isAbovePlayer()) {
            yvel = speed;
        }
        else if (sprite.getTop() > startY) {
            yvel = -speed;
        }
        else {
            yvel = 0;
        }

        if (yvel != 0) {
            web.setHeight(sprite.getTop() - startY);
        }
    }

    bool isAbovePlayer() {
        return sprite.getBottom() < player->getSprite().getTop();
    }

    void move() {
        sprite.moveY(yvel);
    }

    void draw() override {
        web.draw();

        if (yvel != 0) {
            sprite.setTexture(goTextures[goAnim.getCurrentIndex()]);
            goAnim.next();
        }
        else {
            sprite.setTexture(standTexture);
        }
        AbstractEnemy::draw();
    }

public:
    Spider(int x, int y, Player* player, int endY) : AbstractEnemy(x, y, player, 2.5), startY(y), endY(endY), web(x + standTexture.getSize().x / 2 - WEB_WIDTH / 2, y) {
        reactionRect = FloatRect(x, y, standTexture.getSize().x, endY - y);
    }

    void update() override {
        handleCollisionReactionRectWithPlayer();
        move();
        AbstractEnemy::update();
    }

};
