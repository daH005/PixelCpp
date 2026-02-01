#pragma once
#include "../player.hpp"
#include "abstractGameObject.hpp"

class AbstractInteractingWithPlayerGameObject : public AbstractGameObject {
protected:
    // Указатель вместо ссылки позволяет удалять объект через vector::erase.
    // Это связано с тем, что при ссылке удаляется operator= у этого типа, что не даёт произвести удаление,
    // поскольку при удалении из вектора, все элементы правее удаляемого КОПИРУЮТСЯ через этот удалённый оператор ВЛЕВО.
    Player* player;

    void handleCollisionWithPlayer() {
        if (!sprite.intersects(player->getSprite())) {
            return;
        }

        handleCollisionWithPlayerAction();
    }

    virtual void handleCollisionWithPlayerAction() {}

public:
    AbstractInteractingWithPlayerGameObject(int x, int y, Player* player, int zIndex = 0) : AbstractGameObject(x, y, zIndex), player(player) {}

    virtual void update() override {
        handleCollisionWithPlayer();
        AbstractGameObject::update();
    }
};
