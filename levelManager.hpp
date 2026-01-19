#pragma once
#include <fstream>
#include <sstream>

#include "direction.hpp"
#include "json.hpp"
#include "config.hpp"

using json = nlohmann::json;

class LevelObjectArgs {
protected:
    json data;

public:
    LevelObjectArgs(json data) : data(data) {}

    int getX() const {
        return data["x"];
    }

    int getY() const {
        return data["y"];
    }

    Direction getDirection() const {
        Direction direction;
        if (data["direction"].is_null()) {
            direction = Direction::NO;
        }
        else {
            direction = data["direction"];
        }
        return direction;
    }

    bool getGrassEnabled() const {
        return data["grass_enabled"];
    }

    int getImageIndex() const {
        return data["image_index"];
    }

    bool getIsTop() const {
        return data["is_top"];
    }

    int getStartX() const {
        return data["start_x"];
    }

    int getEndX() const {
        return data["end_x"];
    }

    int getEndY() const {
        return data["end_y"];
    }

};

class LevelObject {
protected:
    json data;
    LevelObjectArgs args;
    
public:
    LevelObject(json data) : data(data), args(data["args"]) {}

    string getType() {
        return data["type"];
    }

    LevelObjectArgs& getArgs() {
        return args;
    }

};

class Level {
protected:
    json data;
    vector<LevelObject> objects;

public:
    Level() {}

    void loadFromFile(string path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw runtime_error("The file is not found!");
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();

        data = json::parse(content);
        for (json& ob : data["objects"]) {
            objects.push_back(LevelObject(ob));
        }
    }

    int getW() const {
        return data["w"];
    }

    int getH() const {
        return data["h"];
    }

    vector<LevelObject>& getObjects() {
        return objects;
    }

};

class LevelManager {
protected:
    int currentLevelIndex = 0;
    vector<Level> levels;

public:
    LevelManager() {}

    void reset() {
        currentLevelIndex = 0;
        levels.clear();

        int i = 0;
        string currentPath;
        while (true) {
            currentPath = config::LEVELS_PATH + "/" + to_string(i) + ".json";
            try {
                Level level;
                level.loadFromFile(currentPath);
                levels.push_back(level);
            }
            catch (const std::runtime_error& e) {
                break;
            }
            i++;
        }
    }

    int getLevelCount() const {
        return levels.size();
    }

    int setLevel(int index) {
        if (index < 0 || index > getLevelCount() - 1) {
            throw "The index is not in the range of levels!";
        }
        currentLevelIndex = index;
    }

    int nextLevel() {
        if (currentLevelIndex < getLevelCount() - 1) {
            currentLevelIndex += 1;
        }
    }

    Level& getCurrentLevel() {
        return levels[currentLevelIndex];
    }

};
