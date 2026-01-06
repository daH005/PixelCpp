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

    return textures;
}

Texture loadTexture(string basePath) {
    Texture texture;
    texture.loadFromFile(Config::IMAGES_PATH + "/" + basePath + ".png");
    return texture;
}

class ImageManager {
protected:
    Texture mapBackground = loadTexture("backgrouns/map");

    Texture dirt = loadTexture("dirt/default");
    Texture leftDirt = loadTexture("dirt/left");
    Texture rightDirt = loadTexture("dirt/right");
    Texture backgroundDirt = loadTexture("dirt/background");
    vector<Texture> grasses = loadTexturesFromDirectory("dirt/grass");

    Texture bricks = loadTexture("bricks/default");
    Texture backgroundBricks = loadTexture("bricks/background");

    Texture ladder = loadTexture("ladder");

    vector<Texture> coin = loadTexturesFromDirectory("coin");

    vector<Texture> playerStand = loadTexturesFromDirectory("player/default/stand");
    vector<Texture> playerGo = loadTexturesFromDirectory("player/default/go");
    vector<Texture> playerGoVertical = loadTexturesFromDirectory("player/default/go_vertical");

public:
    ImageManager() {}

    const Texture& getMapBackground() const {
        return mapBackground;
    }

    const Texture& getDirt() const {
        return dirt;
    }

    const Texture& getLeftDirt() const {
        return leftDirt;
    }

    const Texture& getRightDirt() const {
        return rightDirt;
    }

    const Texture& getBackgroundDirt() const {
        return backgroundDirt;
    }

    const vector<Texture>& getGrasses() const {
        return grasses;
    }

    const Texture& getBricks() const {
        return bricks;
    }

    const Texture& getBackgroundBricks() const {
        return backgroundBricks;
    }

    const Texture& getLadder() const {
        return ladder;
    }

    const vector<Texture>& getCoin() const {
        return coin;
    }

    const vector<Texture>& getPlayerStand() const {
        return playerStand;
    }

    const vector<Texture>& getPlayerGo() const {
        return playerGo;
    }

    const vector<Texture>& getPlayerGoVertical() const {
        return playerGoVertical;
    }

};

const ImageManager imageManager = ImageManager();
