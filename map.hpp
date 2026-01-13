#pragma once
#include "levelManager.hpp"
#include "abstractGameObject.hpp"
#include "images.hpp"

#include "player.hpp"
#include "dirt.hpp"
#include "tree.hpp"
#include "web.hpp"
#include "bricks.hpp"
#include "ladder.hpp"
#include "water.hpp"
#include "coin.hpp"
#include "heart.hpp"
#include "shield.hpp"
#include "spike.hpp"

#include "camera.hpp"
#include "mapBackground.hpp"
#include "cloudManager.hpp"

namespace map_object_types {

    const string PLAYER = "Player";

    const string DIRT = "Dirt";
    const string BACKGROUND_DIRT = "BackgroundDirt";
    const string TREE = "Tree";
    const string WEB = "Web";

    const string BRICKS = "Bricks";
    const string BACKGROUND_BRICKS = "BackgroundBricks";
    
    const string COIN = "Coin";
    const string HEART = "Heart";
    const string SHIELD = "Shield";

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
    inline static const int heartW = images::heart[0].getSize().x;
    inline static const vector<Texture> heartHitTextures = images::heartHit;

    Player& player;
    short playerHpBackup = player.getHP();
    FrameIndexFiniteCounter heartHitCounter = FrameIndexFiniteCounter(heartHitTextures.size(), 0.07f);

    vector<Sprite> hpSprites;
    vector<Sprite> deadHpSprites;
    Sprite hittedHeart;
    Sprite shieldSprite;

    void initSprites() {
        short i;
        for (i = 0; i < player.getMaxHP(); ++i) {
            createHpSpriteAndAddToVector(images::heart[0], i, hpSprites);
            createHpSpriteAndAddToVector(images::deadHeart, i, deadHpSprites);
        }

        shieldSprite.setTexture(images::shield[2]);
        shieldSprite.setPosition(i * heartW, 0);
    }

    void createHpSpriteAndAddToVector(const Texture& texture, short i, vector<Sprite>& sprites) {
        Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(i * heartW, 0);
        sprites.push_back(sprite);
    }

    void startHeartHitAnim() {
        hittedHeart.setPosition(player.getHP() * heartW, 0);
        heartHitCounter.restart();
    }

    void drawHeartHitAnim() {
        hittedHeart.setTexture(heartHitTextures[heartHitCounter.getCurrentIndex()]);
        window->draw(hittedHeart);
        heartHitCounter.next();
    }

public:
    PlayerHP_HUD(Player& player) : player(player) {
        initSprites();
    }

    void update() {
        short actualPlayerHP = player.getHP();
        for (short i = 0; i < actualPlayerHP; ++i) {
            window->draw(hpSprites[i]);
        }
        for (short i = actualPlayerHP; i < player.getMaxHP(); ++i) {
            window->draw(deadHpSprites[i]);
        }

        if (actualPlayerHP < playerHpBackup) {
            startHeartHitAnim();
        }

        if (!heartHitCounter.getIsEnded()) {
            drawHeartHitAnim();
        }

        if (player.getHasShield()) {
            window->draw(shieldSprite);
        }

        playerHpBackup = actualPlayerHP;
    }
};

class Map {
protected:
    LevelManager& levelManager;

    vector<AbstractGameObject*> objects;
    Player player = Player();

    int w;
    int h;

    Camera camera = Camera(player);
    MapBackground background = MapBackground(camera);
    CloudManager cloudManager = CloudManager();
    Sun sun = Sun();

    PlayerHP_HUD hpHUD = PlayerHP_HUD(player);

    void createObjects(const json& level) {
        clearObjects();
        player.reset();

        Dirt::resetGrass();
        string t;
        int x, y;
        for (const json& ob : level["objects"]) {
            t = ob["type"];
            json args = ob["args"];
            x = args["x"];
            y = args["y"];

            if (t == map_object_types::PLAYER) {
                player.setPosition(x, y);

            }
            else if (t == map_object_types::DIRT) {
                json& direction = args["direction"];
                if (direction.is_null()) {
                    direction = 0;
                }
                else {
                    direction = (int)direction;
                }
                objects.push_back(new Dirt(x, y, &player, direction, args["grass_enabled"]));

            }
            else if (t == map_object_types::BRICKS) {
                objects.push_back(new Bricks(x, y, &player));

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
            else if (t == map_object_types::SHIELD) {
                objects.push_back(new Shield(x, y, &player));
            }
            else if (t == map_object_types::SPIKE) {
                objects.push_back(new Spike(x, y, &player));

            }
            else if (t == map_object_types::WATER) {
                if ((bool)args["is_top"]) {
                    objects.push_back(new TopWater(x, y, &player));
                }
                else {
                    objects.push_back(new Water(x, y, &player));
                }

            }
            else if (t == map_object_types::TREE) {
                objects.push_back(new Tree(x, y, args["image_index"]));

            }
            else if (t == map_object_types::WEB) {
                objects.push_back(new Web(x, y, (Direction)args["direction"]));

            }

        }

        sortObjectsByZIndex();
    }

    void clearObjects() {
        for (auto ptr : objects) {
            delete ptr;
        }
        objects.clear();
        objects.push_back(&player);
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

        // Не забыть убрать). Сделано, чтобы игра не крашилась.
        if (player.getHP() <= 0) {
            player.addHP();
        }
    }
};
