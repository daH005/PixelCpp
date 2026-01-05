#include "map.hpp"

int main()
{

    sf::Font font;
    if (!font.loadFromFile(Config::FONTS_PATH + "/pixel.ttf")) {
        // Обработка ошибки
        return -1;
    }

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    // Установка позиции: левый нижний угол (с учетом текста)
    fpsText.setPosition(10.f, window->getSize().y - 30.f); // чуть выше нижней границы

    sf::Clock clock;
    float fps = 0.0f;
    int frameCount = 0;
    float timer = 0.0f;


    LevelManager levelManager = LevelManager();
    levelManager.reset();
    levelManager.setLevel(0);
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


        // Время с последнего кадра
        float deltaTime = clock.restart().asSeconds();
        timer += deltaTime;
        frameCount++;

        // Обновлять FPS каждую секунду
        if (timer >= 1.0f) {
            fps = frameCount / timer;
            frameCount = 0;
            timer = 0.0f;

            // Обновляем текст
            std::stringstream ss;
            ss << "FPS: " << static_cast<int>(fps);
            fpsText.setString(ss.str());
        }

        window->clear(backgroundColor);


        map.update();


        // Рисуем FPS
        window->draw(fpsText);

        window->display();
    }

    delete window;
    return 0;
}