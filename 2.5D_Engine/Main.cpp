#include "2.5D_Engine.h"

int main() {

    const unsigned int xWidth = 1500;
    const unsigned int yHeight = 1000;
    sf::RenderWindow window(sf::VideoMode(xWidth, yHeight), "My 2.5D Engine / SFML");
    //sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width ,sf::VideoMode::getDesktopMode().height,32), "2.5_Renderer", sf::Style::Fullscreen);
    //window.setPosition(sf::Vector2i{ -10,-10 });

    sf::CircleShape player;
    player.setRadius(10);
    player.setFillColor(sf::Color::Blue);


    Engine engine(window);

    sf::Sprite spriteToDraw;

    sf::Vector2i dirInput;

    engine.textureRender.loadFromImage(engine.imageRender);
    sf::Clock clock;
        
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            
            //dirInput.y = 0;
            //dirInput.x = 0;
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

            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.y += -1;
            }
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) )
            {
                if (event.type == sf::Event::KeyPressed)dirInput.y += 1;
            }
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.x += -1;
            }
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.x += 1;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
            {
                engine.bDebugRenderOn = !engine.bDebugRenderOn;
            }

            if ((event.type == sf::Event::KeyReleased) && (
                (event.key.code == sf::Keyboard::Up) ||
                (event.key.code == sf::Keyboard::Down)))
            {
                dirInput.y = 0;
            }
            if ((event.type == sf::Event::KeyReleased) && (
                (event.key.code == sf::Keyboard::Left) ||
                (event.key.code == sf::Keyboard::Right)))
            {
                dirInput.x = 0;
            }
            //window.clear();

                        
            //window.draw(spriteToDraw);
            //window.display();
            
        }
        engine.movePlayerOnInput(dirInput);
        //engine.WallDraw();
        engine.Render();
        sf::Time elapsed = clock.restart();

        cout << "Delta : " << elapsed.asMilliseconds() << " | " << (1000 / elapsed.asMilliseconds()) << endl;

    }
}