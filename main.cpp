#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Sim.hpp"
#include "TileMap.hpp"

#define WINDOW_SIZE 1000
#define FRAMERATE 100
#define ZOOM_MODIFIER 40
#define DEFAULT_ZOOM 50.0f

using std::cout;
using std::endl;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Langton's Ant");
    window.setFramerateLimit(FRAMERATE);
    window.setVerticalSyncEnabled(true);
    sf::View view = window.getDefaultView();
    view.setSize(DEFAULT_ZOOM, DEFAULT_ZOOM);
    window.setView(view);

    TileMap map;
    Sim sim(WINDOW_SIZE, &map, SquareColor::White);
    std::thread simThread(&Sim::StartSim, &sim);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseWheelMoved)
            {
                auto currentSize = view.getSize();
                int deltaModified = event.mouseWheel.delta * WINDOW_SIZE / ZOOM_MODIFIER;
                if((currentSize.x > (WINDOW_SIZE / ZOOM_MODIFIER) || event.mouseWheel.delta < 0) && (currentSize.x < WINDOW_SIZE || event.mouseWheel.delta > 0))
                {
                    view.setSize(currentSize.x - deltaModified, currentSize.y - deltaModified);
                    window.setView(view);
                }
            }
        }

        window.clear();
        window.draw(map);        
        window.display();
    }

    return 0;
}