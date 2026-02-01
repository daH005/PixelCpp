#pragma once
#include <fstream>
#include <sstream>

#include "../common/direction.hpp"
#include "../common/json.hpp"
#include "../common/config.hpp"

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

    int getW() const {
        return data["w"];
    }

    int getH() const {
        return data["h"];
    }

};

class LevelObject {
protected:
    json data;
    LevelObjectArgs args;
    
public:
    LevelObject(json data) : data(data), args(data["args"]) {}

    string getType() const {
        return data["type"];
    }

    const LevelObjectArgs& getArgs() const {
        return args;
    }

};

struct CameraBoundingHorizontalLine {
    int startX;
    int endX;
    int y;
};

class Level {
protected:
    json data;
    vector<LevelObject> objects;
    vector<CameraBoundingHorizontalLine> cameraBoundingHorizontalLines;

    void initCameraBoundingHorizontalLines() {
        for (const auto& line : data["camera_bounding_horizontal_lines"]) {
            cameraBoundingHorizontalLines.push_back({
                line[0], line[1], line[2]
            });
        }
    }

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

        initCameraBoundingHorizontalLines();
    }

    int getW() const {
        return data["w"];
    }

    int getH() const {
        return data["h"];
    }

    const vector<LevelObject>& getObjects() const {
        return objects;
    }

    const vector<CameraBoundingHorizontalLine>& getCameraBoundingHorizontalLines() const {
        return cameraBoundingHorizontalLines;
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

    void setLevel(int index) {
        if (index < 0 || index > getLevelCount() - 1) {
            throw "The index is not in the range of levels!";
        }
        currentLevelIndex = index;
    }

    void nextLevel() {
        if (currentLevelIndex < getLevelCount() - 1) {
            currentLevelIndex += 1;
        }
    }

    const Level& getCurrentLevel() const {
        return levels[currentLevelIndex];
    }

};
