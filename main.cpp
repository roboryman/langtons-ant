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

    //sf::View simView(sf::FloatRect(0, 0, WINDOW_SIZE, WINDOW_SIZE));
    //simView.setViewport(sf::FloatRect(0, 0, WINDOW_SIZE/(float)(WINDOW_SIZE+100), 1));
    //simView.setSize(DEFAULT_ZOOM, DEFAULT_ZOOM);
    
    sf::View simView = window.getDefaultView();
    sf::View infoView = window.getDefaultView();

    //sf::View controlView(sf::FloatRect(0, 0, 100.0f, WINDOW_SIZE));
    //controlView.setViewport(sf::FloatRect(WINDOW_SIZE/(float)(WINDOW_SIZE+100), 0, 1.0f-(WINDOW_SIZE/(float)(WINDOW_SIZE+100)), 1));


    sf::Text stepText;
    sf::Font font;
    font.loadFromFile("Verdana.ttf");
    stepText.setFont(font);
    stepText.setFillColor(sf::Color::Blue);
    stepText.setStyle(sf::Text::Bold);
    stepText.setCharacterSize(24);

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
                auto currentSize = simView.getSize();
                int deltaModified = event.mouseWheel.delta * WINDOW_SIZE / ZOOM_MODIFIER;
                if((currentSize.x > (WINDOW_SIZE / ZOOM_MODIFIER) || event.mouseWheel.delta < 0) && (currentSize.x < WINDOW_SIZE || event.mouseWheel.delta > 0))
                {
                    simView.setSize(currentSize.x - deltaModified, currentSize.y - deltaModified);
                }
            }
        }

        stepText.setString("Steps: " + std::to_string(sim.step));
        sf::FloatRect stepTextRect = stepText.getLocalBounds();
        stepText.setOrigin(stepTextRect.left + stepTextRect.width/2.0f, stepTextRect.top + stepTextRect.height/2.0f);
        stepText.setPosition(sf::Vector2f(WINDOW_SIZE/2.0f, 25.0f));

        window.clear(sf::Color::Blue);
        window.setView(simView);
        window.draw(map);
        window.setView(infoView);
        window.draw(stepText);
        window.display();
    }

    return 0;
}