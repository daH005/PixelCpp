#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "config.hpp"

using namespace sf;
using namespace std;

int defineWindowW(int h) {
    VideoMode desktopMode = VideoMode::getDesktopMode();
    return h * ((double)desktopMode.width / desktopMode.height);
}

RenderWindow* createWindow(int h, string title, int maxFps) {
    RenderWindow* window = new RenderWindow(VideoMode(defineWindowW(h), h), title, Style::Default);
    window->setFramerateLimit(maxFps);
    return window;
}

RenderWindow* window = createWindow(config::WINDOW_HEIGHT, config::WINDOW_TITLE, config::MAX_FPS);
