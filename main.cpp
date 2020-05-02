#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Sim.hpp"
#include "TileMap.hpp"

#define WINDOW_SIZE 1000
#define FRAMERATE 100

using std::cout;
using std::endl;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Langton's Ant");
    window.setFramerateLimit(FRAMERATE);
    window.setVerticalSyncEnabled(true);

    TileMap map;
    Sim sim(WINDOW_SIZE, &map);
    std::thread simThread(&Sim::StartSim, &sim);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(map);        
        window.display();
    }

    return 0;
}