#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "config.hpp";

using namespace sf;
using namespace std;

vector<Texture>* loadTexturesFromDirectory(string basePath, string extension = ".png") {
    vector<Texture>* textures = new vector<Texture>();

    string currentPath;
    int i = 0;
    while (true) {
        Texture currentTexture;
        currentPath = basePath + "/" + to_string(i) + extension;
        if (!currentTexture.loadFromFile(currentPath)) {
            break;
        }

        textures->push_back(currentTexture);
        i++;
    }

    return textures;
}

class ImageManager {
protected:
    Texture mapBackground;
    Texture bricks;
    Texture ladder;

    vector<Texture> coin;

    vector<Texture> playerStand;
    vector<Texture> playerGo;
    vector<Texture> playerGoVertical;

public:
    ImageManager() {
        mapBackground.loadFromFile(Config::IMAGES_PATH + "/backgrounds/map.png");
        bricks.loadFromFile(Config::IMAGES_PATH + "/bricks/default.png");
        ladder.loadFromFile(Config::IMAGES_PATH + "/ladder.png");

        coin = *loadTexturesFromDirectory(Config::IMAGES_PATH + "/coin");

        playerStand = *loadTexturesFromDirectory(Config::IMAGES_PATH + "/player/default/stand");
        playerGo = *loadTexturesFromDirectory(Config::IMAGES_PATH + "/player/default/go");
        playerGoVertical = *loadTexturesFromDirectory(Config::IMAGES_PATH + "/player/default/go_vertical");
    }

    Texture& getMapBackground() {
        return mapBackground;
    }

    Texture& getBricks() {
        return bricks;
    }

    Texture& getLadder() {
        return ladder;
    }

    vector<Texture>& getCoin() {
        return coin;
    }

    vector<Texture>& getPlayerStand() {
        return playerStand;
    }

    vector<Texture>& getPlayerGo() {
        return playerGo;
    }

    vector<Texture>& getPlayerGoVertical() {
        return playerGoVertical;
    }

};

ImageManager imageManager = ImageManager();
