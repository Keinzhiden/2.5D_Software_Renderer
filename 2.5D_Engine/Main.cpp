#include "2.5D_Engine.h"

int main() {

    const unsigned int xWidth = 1500;
    const unsigned int yHeight = 1000;
    sf::RenderWindow window(sf::VideoMode(xWidth, yHeight), "My 2.5D Engine / SFML");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    sf::CircleShape player;
    player.setRadius(10);
    player.setFillColor(sf::Color::Blue);


    Engine engine(window);

    sf::Sprite spriteToDraw;

    sf::Vector2i dirInput;

    engine.textureRender.loadFromImage(engine.imageRender);
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseMoved) {
                engine.rotatePlayerOnMouse(sf::Mouse::getPosition(window), window);
            }
            if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) {
                engine.playerPosition.z  = engine.playerPosition.z - 2;

            }
            if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Right)) {
                engine.playerPosition.z = engine.playerPosition.z + 2;

            }

            if (((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Up))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.y = -1;
                if (event.type == sf::Event::KeyReleased)dirInput.y = 0;

            }
            if (((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Down)) {
                if (event.type == sf::Event::KeyPressed)dirInput.y = 1;
                if (event.type == sf::Event::KeyReleased)dirInput.y = 0;

            }
            if (((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Left))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.x = -1;
                if (event.type == sf::Event::KeyReleased)dirInput.x = 0;
            }
            if (((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Right))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.x = 1;
                if (event.type == sf::Event::KeyReleased)dirInput.x = 0;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
            {
                engine.bDebugRenderOn = !engine.bDebugRenderOn;
            }
            //window.clear();

            engine.movePlayerOnInput(dirInput);
            //engine.WallDraw();
            engine.Render();
            //window.draw(spriteToDraw);
            //window.display();
            
        }
    }
}