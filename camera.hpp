#pragma once
#include <SFML/Graphics.hpp>

#include "player.hpp"

using namespace sf;

class Camera {
protected:
    const float X_SMOOTH = 0.05f;
    const float Y_SMOOTH = 0.01f;
    
    Vector2u size = window->getSize();
    int w = size.x;
    int h = size.y;
    int halfW = w / 2;
    int halfH = h / 2;
    View view = View(FloatRect(0, 0, w, h));

    Player& player;
    int mapW;
    int mapH;

    int xToMove;
    int yToMove;

    void updateXYtoMove() {
        FloatRect playerRect = player.getSprite().getGlobalBounds();
        xToMove = getCenterXofRect(playerRect);
        yToMove = getCenterYofRect(playerRect);
        considerMapEdges();
    }

    int getCenterXofRect(FloatRect& rect) const {
        return rect.left + rect.width / 2;
    }

    int getCenterYofRect(FloatRect& rect) const {
        return rect.top + rect.height / 2;
    }

    void considerMapEdges() {
        xToMove = max(halfW, xToMove);
        int rightMapEdgeX = mapW - halfW;
        xToMove = min(rightMapEdgeX, xToMove);

        yToMove = max(halfH, yToMove);
        int bottomMapEdgeX = mapH - halfH;
        yToMove = min(bottomMapEdgeX, yToMove);
    }

    void updateXY() {
        Vector2f viewCenter = view.getCenter();
        float xVel = (xToMove - viewCenter.x) * X_SMOOTH;
        float yVel = (yToMove - viewCenter.y) * Y_SMOOTH;
        view.move(xVel, yVel);
    }

    void quickUpdateXY() {
        view.setCenter(xToMove, yToMove);
    }

public:
    Camera(Player& player) : player(player) {}

    void reset(int _mapW, int _mapH) {
        mapW = _mapW;
        mapH = _mapH;
    }

    void update() {
        updateXYtoMove();
        updateXY();
    }

    void quickMove() {
        updateXYtoMove();
        quickUpdateXY();
    }

    const View& getView() const {
        return view;
    }
};
