#pragma once
#include "player.hpp"

class AbstractInteractingWithPlayerGameObject : public AbstractGameObject {
protected:
    // ”казатель вместо ссылки позвол€ет удал€ть объект через vector::erase.
    // Ёто св€зано с тем, что при ссылке удал€етс€ operator= у этого типа, что не даЄт произвести удаление,
    // поскольку при удалении из вектора, все элементы правее удал€емого  ќѕ»–”ё“—я через этот удалЄнный оператор ¬Ћ≈¬ќ.
    Player* player;

    void handleCollisionWithPlayer() {
        if (!sprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
            return;
        }

        _handleCollisionWithPlayer();
    }

    virtual void _handleCollisionWithPlayer() {

    }

public:
    AbstractInteractingWithPlayerGameObject(int x, int y, Player* player, int zIndex = 0) : AbstractGameObject(x, y, zIndex), player(player) {}

    virtual void update() override {
        handleCollisionWithPlayer();
        AbstractGameObject::update();
    }
};
