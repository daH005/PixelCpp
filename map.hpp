#pragma once
#include "levelManager.hpp"
#include "abstractGameObjects.hpp"
#include "player.hpp"
#include "dirt.hpp"
#include "bricks.hpp"
#include "ladder.hpp"
#include "coin.hpp"
#include "camera.hpp"
#include "mapBackground.hpp"
#include "cloudManager.hpp"

class Map {
protected:
    LevelManager& levelManager;

    Player player = Player(blocks);
    vector<AbstractBlock> blocks;
    vector<Dirt> dirts;
    vector<AbstractBackgroundBlock> backgroundBlocks;
    vector<Ladder> ladders;
    vector<Coin> coins;

    int w;
    int h;

    Camera camera = Camera(player);
    MapBackground background = MapBackground(camera);
    CloudManager cloudManager = CloudManager();
    
    class Sun : public AbstractGameObject {
    public:
        Sun() : AbstractGameObject(50, 50) {
            sprite.setTexture(imageManager.getSun());
        }
    };
    Sun sun = Sun();

    void clearAllVectors() {
        blocks.clear();
        dirts.clear();
        backgroundBlocks.clear();
        ladders.clear();
        coins.clear();
    }

public:
    Map(LevelManager& levelManager) : levelManager(levelManager) {}

    void reset() {
        clearAllVectors();
        Dirt::resetGrass();

        const json& level = levelManager.getCurrentLevelJson();
        string t;
        int x, y;
        for (const json& ob : level["objects"]) {
            t = ob["type"];
            json args = ob["args"];
            x = args["x"];
            y = args["y"];

            if (t == "Player") {
                player.reset(x, y);

            }
            else if (t == "Dirt") {
                json& direction = args["direction"];
                if (direction.is_null()) {
                    direction = 0;
                }
                else {
                    direction = (int)direction;
                }
                Dirt dirt = Dirt(x, y, direction, args["grass_enabled"]);
                dirts.push_back(dirt);
                blocks.push_back(dirt);

            }
            else if (t == "Bricks") {
                blocks.push_back(Bricks(x, y));

            }
            else if (t == "BackgroundBricks") {
                backgroundBlocks.push_back(BackgroundBricks(x, y));

            }
            else if (t == "Ladder") {
                ladders.push_back(Ladder(x, y, player));

            }
            else if (t == "Coin") {
                coins.push_back(Coin(x, y, player));

            }
        }
        
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

        for (AbstractBackgroundBlock& backgroundBlock : backgroundBlocks) {
            backgroundBlock.update();
        }

        for (Ladder& ladder : ladders) {
            ladder.update();
        }

        for (Coin& coin : coins) {
            coin.update();
        }

        player.update();
        for (AbstractBlock& block : blocks) {
            block.update();
        }
        for (Dirt& dirt : dirts) {
            dirt.update();
        }

        window->setView(window->getDefaultView());
    }
};
