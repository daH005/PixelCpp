#pragma once
#include "levelManager.hpp"
#include "abstractGameObjects.hpp"

#include "player.hpp"
#include "dirt.hpp"
#include "tree.hpp"
#include "bricks.hpp"
#include "ladder.hpp"
#include "water.hpp"
#include "coin.hpp"
#include "heart.hpp"
#include "spike.hpp"

#include "camera.hpp"
#include "mapBackground.hpp"
#include "cloudManager.hpp"

namespace map_object_types {

    const string PLAYER = "Player";

    const string DIRT = "Dirt";
    const string BACKGROUND_DIRT = "BackgroundDirt";
    const string TREE = "Tree";

    const string BRICKS = "Bricks";
    const string BACKGROUND_BRICKS = "BackgroundBricks";
    
    const string COIN = "Coin";
    const string HEART = "Heart";

    const string LADDER = "Ladder";
    const string WATER = "Water";
    const string SPIKE = "Spike";

};

class Sun : public AbstractGameObject {
public:
    Sun() : AbstractGameObject(50, 50) {
        sprite.setTexture(images::sun);
    }
};

class PlayerHP_HUD {
protected:
    Player& player;

    vector<Sprite> hpSprites;

    void initSprites() {
        int heartW = images::heart[0].getSize().x;
        for (short i = 0; i < player.getMaxHP(); ++i) {
            Sprite hpSprite;
            hpSprite.setTexture(images::heart[0]);
            hpSprite.setPosition(i * heartW, 0);
            hpSprites.push_back(hpSprite);
        }
    }

public:
    PlayerHP_HUD(Player& player) : player(player) {
        initSprites();
    }

    void update() {
        for (short i = 0; i < player.getHP(); ++i) {
            window->draw(hpSprites[i]);
        }
    }
};

class Map {
protected:
    inline static const string BLOCK_TYPES[] = { map_object_types::DIRT, map_object_types::BRICKS };
    inline static const size_t BLOCK_TYPES_SIZE = sizeof(BLOCK_TYPES) / sizeof(BLOCK_TYPES[0]);
    inline static const string* BLOCK_TYPES_END = BLOCK_TYPES + BLOCK_TYPES_SIZE;
    inline static const int BLOCK_W = 40;

    LevelManager& levelManager;

    vector<AbstractGameObject*> objects;
    vector<FloatRect> blockRects;
    Player player = Player(blockRects);

    int w;
    int h;

    Camera camera = Camera(player);
    MapBackground background = MapBackground(camera);
    CloudManager cloudManager = CloudManager();
    Sun sun = Sun();

    PlayerHP_HUD hpHUD = PlayerHP_HUD(player);

    void createObjects(const json& level) {
        clearAllVectors();

        Dirt::resetGrass();
        string t;
        int x, y;
        for (const json& ob : level["objects"]) {
            t = ob["type"];
            json args = ob["args"];
            x = args["x"];
            y = args["y"];

            if (t == map_object_types::PLAYER) {
                player.reset(x, y);

            }
            else if (t == map_object_types::DIRT) {
                json& direction = args["direction"];
                if (direction.is_null()) {
                    direction = 0;
                }
                else {
                    direction = (int)direction;
                }
                Dirt* dirt = new Dirt(x, y, direction, args["grass_enabled"]);
                objects.push_back(dirt);

            }
            else if (t == map_object_types::BRICKS) {
                objects.push_back(new Bricks(x, y));

            }
            else if (t == map_object_types::BACKGROUND_BRICKS) {
                objects.push_back(new BackgroundBricks(x, y));

            }
            else if (t == map_object_types::LADDER) {
                objects.push_back(new Ladder(x, y, &player));

            }
            else if (t == map_object_types::COIN) {
                objects.push_back(new Coin(x, y, &player));

            }
            else if (t == map_object_types::HEART) {
                objects.push_back(new Heart(x, y, &player));

            }
            else if (t == map_object_types::SPIKE) {
                objects.push_back(new Spike(x, y, &player));

            }
            else if (t == map_object_types::WATER) {
                objects.push_back(new Water(x, y, &player, args["is_top"]));

            }
            else if (t == map_object_types::TREE) {
                objects.push_back(new Tree(x, y, args["image_index"]));

            }

            if (find(BLOCK_TYPES, BLOCK_TYPES_END, t) != BLOCK_TYPES_END) {
                blockRects.push_back(FloatRect(x, y, BLOCK_W, BLOCK_W));
            }
        }

        sortObjectsByZIndex();
    }

    void clearAllVectors() {
        for (auto ptr : objects) {
            delete ptr;
        }
        objects.clear();
        objects.push_back(&player);
        blockRects.clear();
    }

    void sortObjectsByZIndex() {
        sort(objects.begin(), objects.end(),
            [](const AbstractGameObject* a, const AbstractGameObject* b) {
                return a->getZIndex() < b->getZIndex();
            });
    }

    void updateObjects() {
        for (auto it = objects.begin(); it != objects.end(); ) {
            (*it)->update();
            if ((*it)->getToBeDeleted()) {
                it = objects.erase(it);
            }
            else {
                ++it;
            }
        }
    }

public:
    Map(LevelManager& levelManager) : levelManager(levelManager) {}

    void reset() {
        const json& level = levelManager.getCurrentLevelJson();
        createObjects(level);

        w = level["w"];
        h = level["h"];

        camera.reset(w, h);
        camera.quickMove();

        background.reset();
        cloudManager.reset();
    }

    void update() {
        camera.update();

        background.update();
        sun.update();
        cloudManager.update();

        window->setView(camera.getView());
        updateObjects();

        window->setView(window->getDefaultView());
        hpHUD.update();
    }
};
