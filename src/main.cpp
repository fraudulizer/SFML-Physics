#include <SFML/Graphics.hpp>
#include <configuration.hpp>
#include <verlet.hpp>
#include <verletpendulum.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    Solver solver;

    auto window = sf::RenderWindow({ conf::window_size.x, conf::window_size.y }, "SFML Verlet Integration");
    window.setFramerateLimit(conf::max_framerate);

    sf::Font consolas;
    consolas.loadFromFile("C:\\Users\\Jandy\\source\\SFML-Physics\\SFML-Physics\\files\\Consolas.ttf");

    sf::Text energy;
    energy.setFont(consolas);
    sf::Text deltatime;
    deltatime.setFont(consolas);
    deltatime.setPosition(sf::Vector2f(0, 100));


    sf::SoundBuffer collision;
    if (!collision.loadFromFile("C:\\Users\\Jandy\\source\\SFML-Physics\\SFML-Physics\\files\\collision.wav"))
    {
        std::cout << "Error" << std::endl;
    }
    sf::Sound collisionsound;
    collisionsound.setBuffer(collision);
    sf::Clock clock;

    while (window.isOpen())
    {
        window.clear();

        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        solver.update(conf::dt);

        for (int i = 0; i < solver.count; i++)
        {
            if (solver.ball[i].collide == true)
            {
               // collisionsound.play();
            }
       }

        energy.setString(std::to_string(solver.energy));
        float currenttime = clock.restart().asSeconds();
        deltatime.setString(std::to_string(1.0f/currenttime));
        window.draw(deltatime);
        window.draw(energy);
        solver.render(window);
        window.display();
        solver.energy = 0;
        currenttime = 0;

    }
}
