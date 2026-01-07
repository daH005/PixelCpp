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
        currentPath = Config::IMAGES_PATH + "/" + basePath + "/" + to_string(i) + ".png";
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
    if (!texture.loadFromFile(Config::IMAGES_PATH + "/" + basePath + ".png")) {
        throw runtime_error("Texture " + basePath + " was not found!");
    }
    return texture;
}

namespace images {

    const Texture mapBackground = loadTexture("backgrounds/map");
    const Texture sun = loadTexture("sun");
    const vector<Texture> clouds = loadTexturesFromDirectory("clouds");

    const Texture dirt = loadTexture("dirt/default");
    const Texture leftDirt = loadTexture("dirt/left");
    const Texture rightDirt = loadTexture("dirt/right");
    const Texture backgroundDirt = loadTexture("dirt/background");
    const vector<Texture> grasses = loadTexturesFromDirectory("dirt/grass");

    const Texture bricks = loadTexture("bricks/default");
    const Texture backgroundBricks = loadTexture("bricks/background");

    const Texture ladder = loadTexture("ladder");

    const vector<Texture> coin = loadTexturesFromDirectory("coin");

    const vector<Texture> playerStand = loadTexturesFromDirectory("player/default/stand");
    const vector<Texture> playerGo = loadTexturesFromDirectory("player/default/go");
    const vector<Texture> playerGoVertical = loadTexturesFromDirectory("player/default/go_vertical");

}
