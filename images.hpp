#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "config.hpp";

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

    const vector<Texture> heartHit = loadTexturesFromDirectory("heart/hit");
    const vector<Texture> heart = loadTexturesFromDirectory("heart/as_item");
    const vector<Texture> coin = loadTexturesFromDirectory("coin");
    const vector<Texture> shield = loadTexturesFromDirectory("shield");

    const Texture spike = loadTexture("spike");

    const Texture water = loadTexture("water/default");
    const Texture topWater = loadTexture("water/top");

    const vector<Texture> playerStand = loadTexturesFromDirectory("player/default/stand");
    const vector<Texture> playerGo = loadTexturesFromDirectory("player/default/go");
    const vector<Texture> playerGoVertical = loadTexturesFromDirectory("player/default/go_vertical");

    const vector<Texture> whitePlayerStand = loadTexturesFromDirectory("player/white_default/stand");
    const vector<Texture> whitePlayerGo = loadTexturesFromDirectory("player/white_default/go");
    const vector<Texture> whitePlayerGoVertical = loadTexturesFromDirectory("player/white_default/go_vertical");

}
