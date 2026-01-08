#pragma once
#include <fstream>
#include <sstream>

#include "json.hpp"
#include "config.hpp"

using json = nlohmann::json;

json readJsonFile(string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("The file is not found!");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    return json::parse(content);
}

class LevelManager {
protected:
    int currentLevelIndex = 0;
    vector<json> levels;

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
                levels.push_back(readJsonFile(currentPath));
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

    const json& getCurrentLevelJson() const {
        return levels[currentLevelIndex];
    }

};
