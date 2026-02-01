#pragma once
#include "../common/images.hpp"

#include "objects/abstract/abstractGameObject.hpp"
#include "objects/player.hpp"
#include "objects/dirt.hpp"
#include "objects/tree.hpp"
#include "objects/web.hpp"
#include "objects/bricks.hpp"
#include "objects/overlay.hpp"
#include "objects/ladder.hpp"
#include "objects/water.hpp"
#include "objects/finish.hpp"
#include "objects/coin.hpp"
#include "objects/heart.hpp"
#include "objects/shield.hpp"
#include "objects/chest.hpp"
#include "objects/spike.hpp"
#include "objects/slug.hpp"
#include "objects/bat.hpp"
#include "objects/skeleton.hpp"
#include "objects/spider.hpp"
#include "objects/cannon.hpp"
#include "objects/dragon.hpp"
#include "objects/ghost.hpp"

#include "levelManager.hpp"
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

    const string OVERLAY = "Overlay";
    
    const string COIN = "Coin";
    const string HEART = "Heart";
    const string SHIELD = "Shield";
    const string CHEST = "Chest";

    const string LADDER = "Ladder";
    const string WATER = "Water";
    const string FINISH = "Finish";

    const string SPIKE = "Spike";
    const string SLUG = "Slug";
    const string BAT = "Bat";
    const string SKELETON = "Skeleton";
    const string SPIDER = "Spider";
    const string CANNON = "Cannon";
    const string DRAGON = "Dragon";
    const string GHOST = "Ghost";

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
    FrameIndexFiniteCounter heartHitCounter = FrameIndexFiniteCounter(heartHitTextures.size(), 0.07);

    vector<SpriteWrapper> hpSprites;
    vector<SpriteWrapper> deadHpSprites;
    SpriteWrapper hittedHeart;
    SpriteWrapper shieldSprite;

    void initSprites() {
        short i;
        for (i = 0; i < player.getMaxHP(); ++i) {
            createHpSpriteAndAddToVector(images::heart[0], i, hpSprites);
            createHpSpriteAndAddToVector(images::deadHeart, i, deadHpSprites);
        }

        shieldSprite.setTexture(images::shield[2]);
        shieldSprite.setLeft(i * heartW);
    }

    void createHpSpriteAndAddToVector(const Texture& texture, short i, vector<SpriteWrapper>& sprites) {
        SpriteWrapper sprite;
        sprite.setTexture(texture);
        sprite.setLeft(i * heartW);
        sprites.push_back(sprite);
    }

    void startHeartHitAnim() {
        hittedHeart.setLeft(player.getHP() * heartW);
        heartHitCounter.restart();
    }

    void drawHeartHitAnim() {
        hittedHeart.setTexture(heartHitTextures[heartHitCounter.getCurrentIndex()]);
        hittedHeart.draw();
        heartHitCounter.next();
    }

public:
    PlayerHP_HUD(Player& player) : player(player) {
        initSprites();
    }

    void update() {
        short actualPlayerHP = player.getHP();
        for (short i = 0; i < actualPlayerHP; ++i) {
            hpSprites[i].draw();
        }
        for (short i = actualPlayerHP; i < player.getMaxHP(); ++i) {
            deadHpSprites[i].draw();
        }

        if (actualPlayerHP < playerHpBackup) {
            startHeartHitAnim();
        }

        if (!heartHitCounter.getIsEnded()) {
            drawHeartHitAnim();
        }

        if (player.getHasShield()) {
            shieldSprite.draw();
        }

        playerHpBackup = actualPlayerHP;
    }
};

class Map {
protected:
    LevelManager& levelManager;

    // Создавать объекты в куче и хранить указатели на них здесь нужно для динамического полиморфизма с методом update.
    vector<AbstractGameObject*> objects;
    Player player = Player();

    int w;
    int h;

    Camera camera = Camera(player);
    MapBackground background = MapBackground(camera);
    CloudManager cloudManager = CloudManager();
    Sun sun = Sun();

    PlayerHP_HUD hpHUD = PlayerHP_HUD(player);

    void resetObjects(const Level& level) {
        clearObjects();
        player.reset(level.getW());

        Dirt::resetGrass();
        string t;
        int x, y;
        for (const LevelObject& ob : level.getObjects()) {
            t = ob.getType();
            const LevelObjectArgs& args = ob.getArgs();
            x = args.getX();
            y = args.getY();

            if (t == map_object_types::PLAYER) {
                player.setPosition(x, y);

            }
            else if (t == map_object_types::DIRT) {
                objects.push_back(new Dirt(x, y, &player, args.getDirection(), args.getGrassEnabled()));
                
            } else if (t == map_object_types::BACKGROUND_DIRT) {
                objects.push_back(new BackgroundDirt(x, y));

            }
            else if (t == map_object_types::BRICKS) {
                objects.push_back(new Bricks(x, y, &player));

            }
            else if (t == map_object_types::BACKGROUND_BRICKS) {
                objects.push_back(new BackgroundBricks(x, y));

            } else if (t == map_object_types::OVERLAY) {
                objects.push_back(new Overlay(x, y, args.getW(), args.getH()));

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
            else if (t == map_object_types::CHEST) {
                objects.push_back(new Chest(x, y, &player));
            }
            else if (t == map_object_types::WATER) {
                if (args.getIsTop()) {
                    objects.push_back(new TopWater(x, y, &player));
                }
                else {
                    objects.push_back(new Water(x, y, &player));
                }

            }
            else if (t == map_object_types::TREE) {
                objects.push_back(new Tree(x, y, args.getImageIndex()));

            }
            else if (t == map_object_types::WEB) {
                objects.push_back(new Web(x, y, args.getDirection()));

            }
            else if (t == map_object_types::FINISH) {
                objects.push_back(new Finish(x, y, &player));
            }
            else if (t == map_object_types::SPIKE) {
                objects.push_back(new Spike(x, y, &player));

            }
            else if (t == map_object_types::SLUG) {
                objects.push_back(new Slug(x, y, &player, args.getStartX(), args.getEndX()));

            }
            else if (t == map_object_types::BAT) {
                objects.push_back(new Bat(x, y, &player, args.getStartX(), args.getEndX()));

            }
            else if (t == map_object_types::SKELETON) {
                objects.push_back(new Skeleton(x, y, &player, args.getStartX(), args.getEndX()));

            }
            else if (t == map_object_types::SPIDER) {
                objects.push_back(new Spider(x, y, &player, args.getEndY()));

            }
            else if (t == map_object_types::CANNON) {
                objects.push_back(new Cannon(x, y, &player, args.getEndX()));

            }
            else if (t == map_object_types::DRAGON) {
                objects.push_back(new Dragon(x, y, &player, args.getStartX(), args.getEndX()));

            } else if (t == map_object_types::GHOST) {
                objects.push_back(new Ghost(x, y, &player, args.getStartX(), args.getEndX()));
                
            }

        }

        sortObjectsByZIndex();
    }

    void clearObjects() {
        for (auto ptr : objects) {
            if (ptr == &player) {  // Игрок не являтся объектом кучи, его нельзя удалять так, поэтому фильтруем.
                continue;
            }
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
                delete *it;
                it = objects.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void switchToNextLevel() {
        levelManager.nextLevel();
        reset();
    }

public:
    Map(LevelManager& levelManager) : levelManager(levelManager) {}

    void reset() {
        const Level& level = levelManager.getCurrentLevel();
        resetObjects(level);

        w = level.getW();
        h = level.getH();

        camera.reset(w, h, level.getCameraBoundingHorizontalLines());
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

        if (player.getIsFinished()) {
            switchToNextLevel();
        }

        // Не забыть убрать). Сделано, чтобы игра не крашилась.
        if (player.getHP() <= 0) {
            reset();
        }
    }
};
