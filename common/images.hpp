#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "config.hpp"

using namespace sf;
using namespace std;

vector<Texture> loadTexturesFromDirectory(string basePath) {
    vector<Texture> textures = vector<Texture>();

    string currentPath;
    int i = 0;
    while (true) {
        Texture currentTexture;
        currentPath = config::IMAGES_PATH + "/" + basePath + "/" + to_string(i) + ".png";
        if (!currentTexture.loadFromFile(currentPath)) {
            break;
        }

        textures.push_back(currentTexture);
        i++;
    }

    if (textures.size() == 0) {
        throw runtime_error("Textures " + basePath + " were not found!");
    }

    return textures;
}

Texture loadTexture(string basePath) {
    Texture texture;
    if (!texture.loadFromFile(config::IMAGES_PATH + "/" + basePath + ".png")) {
        throw runtime_error("Texture " + basePath + " was not found!");
    }
    return texture;
}

namespace images {

    const Texture mapBackground = loadTexture("backgrounds/map");
    const Texture sun = loadTexture("sun");
    const vector<Texture> clouds = loadTexturesFromDirectory("clouds");
    
    const vector<Texture> trees = loadTexturesFromDirectory("trees");
    const Texture web = loadTexture("web");

    const Texture dirt = loadTexture("dirt/default");
    const Texture leftDirt = loadTexture("dirt/left");
    const Texture rightDirt = loadTexture("dirt/right");
    const Texture backgroundDirt = loadTexture("dirt/background");
    const vector<Texture> grasses = loadTexturesFromDirectory("dirt/grass");

    const Texture bricks = loadTexture("bricks/default");
    const Texture backgroundBricks = loadTexture("bricks/background");

    const Texture ladder = loadTexture("ladder");

    const Texture deadHeart = loadTexture("heart/dead");
    const vector<Texture> heartHit = loadTexturesFromDirectory("heart/hit");
    const vector<Texture> heart = loadTexturesFromDirectory("heart/as_item");
    const vector<Texture> coin = loadTexturesFromDirectory("coin");
    const vector<Texture> shield = loadTexturesFromDirectory("shield");

    const Texture chestDefault = loadTexture("chest/default");
    const Texture chestOpened = loadTexture("chest/opened");

    const Texture water = loadTexture("water/default");
    const Texture topWater = loadTexture("water/top");

    const Texture finish = loadTexture("finish");

    const vector<Texture> playerStand = loadTexturesFromDirectory("player/default/stand");
    const vector<Texture> playerGo = loadTexturesFromDirectory("player/default/go");
    const vector<Texture> playerGoVertical = loadTexturesFromDirectory("player/default/go_vertical");
    const vector<Texture> stun = loadTexturesFromDirectory("stun");

    const vector<Texture> whitePlayerStand = loadTexturesFromDirectory("player/white_default/stand");
    const vector<Texture> whitePlayerGo = loadTexturesFromDirectory("player/white_default/go");
    const vector<Texture> whitePlayerGoVertical = loadTexturesFromDirectory("player/white_default/go_vertical");

    const Texture spike = loadTexture("spike");

    const vector<Texture> slugGo = loadTexturesFromDirectory("slug/go");
    const vector<Texture> slugDeath = loadTexturesFromDirectory("slug/death");

    const vector<Texture> batGo = loadTexturesFromDirectory("bat");

    const vector<Texture> skeletonGo = loadTexturesFromDirectory("skeleton/go");
    const vector<Texture> skeletonAttack = loadTexturesFromDirectory("skeleton/attack");

    const Texture spiderStand = loadTexture("spider/stand");
    const vector<Texture> spiderGo = loadTexturesFromDirectory("spider/go");

    const Texture cannonDefault = loadTexture("cannon/cannon/default");
    const vector<Texture> cannonShoot = loadTexturesFromDirectory("cannon/cannon/shoot");

    const Texture cannonballDefault = loadTexture("cannon/cannonball/default");
    const vector<Texture> cannonballDeath = loadTexturesFromDirectory("cannon/cannonball/death");

    const vector<Texture> dragonDefaultGo = loadTexturesFromDirectory("dragon/go/default");
    const vector<Texture> dragonGoWhenAttacks = loadTexturesFromDirectory("dragon/go/when_attacks");
    const vector<Texture> dragonFire = loadTexturesFromDirectory("dragon/fire");

    const Texture ghostDefault = loadTexture("ghost/default");
    const Texture ghostAttack = loadTexture("ghost/attack");

}
