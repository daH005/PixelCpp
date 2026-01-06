#include "map.hpp"

int main()
{

    Font font;
    font.loadFromFile(Config::FONTS_PATH + "/pixel.ttf");

    Text fpsText;
    fpsText.setFont(font);
    fpsText.setFillColor(Color::White);
    fpsText.setPosition(10.f, window->getSize().y - 30.f);

    Clock clock;
    float fps = 0.0f;
    int frameCount = 0;
    float timer = 0.0f;

    LevelManager levelManager = LevelManager();
    levelManager.reset();
    levelManager.setLevel(9);
    Map map = Map(levelManager);
    map.reset();

    Color backgroundColor(0, 191, 255, 255);

    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window->close();
            }
        }


        float deltaTime = clock.restart().asSeconds();
        timer += deltaTime;
        frameCount++;

        if (timer >= 1.0f) {
            fps = frameCount / timer;
            frameCount = 0;
            timer = 0.0f;

            fpsText.setString(to_string((int)fps));
        }

        window->clear(backgroundColor);
        map.update();

        window->setView(window->getDefaultView());
        window->draw(fpsText);

        window->display();
    }

    delete window;
    return 0;
}