#include <thread>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Sim.hpp"

using std::cout;
using std::endl;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Langton's Ant");
    window.setFramerateLimit(60);

    Sim sim;
    std::thread simThread(&Sim::StartSim, &sim);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        
        auto stableGrid = sim.grid;
        float squareSize = 1000.0f / (float)sim.size;
        for(int i = 0; i < stableGrid.size(); i++)
        {
            for(int j = 0; j < stableGrid.size(); j++)
            {   
                if(stableGrid.at(i).at(j) == SquareColor::Black)
                {
                    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                    square.setFillColor(sf::Color::Black);
                    float x = j * squareSize;
                    float y = i * squareSize;
                    square.setPosition(x, y);
                    window.draw(square);
                }
            }
        }
        
        
        window.display();
    }

    return 0;
}