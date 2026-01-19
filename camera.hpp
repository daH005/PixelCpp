#pragma once
#include "player.hpp"

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
        xToMove = player.getSprite().getCenterX();
        yToMove = player.getSprite().getCenterY();
        considerMapEdges();
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
