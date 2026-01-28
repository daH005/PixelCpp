#pragma once
#include "abstractGameObject.hpp"

class AbstractBackground : public AbstractGameObject {
public:
    AbstractBackground(int x, int y) : AbstractGameObject(x, y, ZIndex::BACKGROUND) {}
};

