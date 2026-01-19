#pragma once
#include "window.hpp"
#include "direction.hpp"

class SpriteWrapper {
protected:
    Sprite sprite;
    Direction direction = Direction::RIGHT;

    void updateOrigin() {
        sprite.setOrigin(sprite.getLocalBounds().width * (direction == Direction::LEFT ? 1.f : 0), 0);
    }

public:
    SpriteWrapper() {}

    Sprite& getSprite() {  // Удалить!
        return sprite;
    }

    int getLeft() const {
        return sprite.getGlobalBounds().left;
    }

    int getRight() const {
        return getLeft() + sprite.getGlobalBounds().width;
    }

    int getTop() const {
        return sprite.getGlobalBounds().top;
    }

    int getBottom() const {
        return getTop() + sprite.getGlobalBounds().height;
    }

    int getWidth() const {
        return sprite.getGlobalBounds().width;
    }

    int getHeight() const {
        return sprite.getGlobalBounds().height;
    }

    int getCenterX() const {
        return getLeft() + getWidth() / 2;
    }

    int getCenterY() const {
        return getTop() + getHeight() / 2;
    }

    bool intersects(const SpriteWrapper& another) const {
        return intersects(another.getRect());
    }

    bool intersects(const FloatRect& anotherRect) const {
        return anotherRect.intersects(getRect());
    }

    FloatRect getRect() const {
        return sprite.getGlobalBounds();
    }

    Direction getDirection() const {
        return direction;
    }

    void setLeft(int value) {
        sprite.setPosition(value, getTop());
    }

    void setRight(int value) {
        sprite.setPosition(value - getWidth(), getTop());
    }

    void setTop(int value) {
        sprite.setPosition(getLeft(), value);
    }

    void setBottom(int value) {
        sprite.setPosition(getLeft(), value - getHeight());
    }

    void setPosition(int x, int y) {
        sprite.setPosition(x, y);
    }

    void moveX(float value) {
        sprite.move(value, 0);
    }

    void moveY(float value) {
        sprite.move(0, value);
    }

    void move(float x, float y) {
        sprite.move(x, y);
    }

    void setTexture(const Texture& texture) {
        sprite.setTexture(texture);
    }

    void setTextureWithRectUpdating(const Texture& texture) {
        sprite.setTexture(texture, true);
        updateOrigin();
    }

    void setDirection(Direction _direction) {
        if (_direction == direction) {
            return;
        }
        sprite.setScale(_direction * 1.f, 1.f);
        direction = _direction;
        updateOrigin();
    }

    void flipDirectionX() {
        setDirection(flipDirection(direction));
    }

    void draw() {
        window->draw(sprite);
    }

};
