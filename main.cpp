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
    sim.InitializeGrid(99);
    std::thread simThread(&Sim::StartSim, &sim);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Green);

        int currentSimSize = sim.GetCurrentSize();
        float squareSize = 1000.0f / (float)currentSimSize;
        for(int i = 0; i < currentSimSize; i++)
        {
            for(int j = 0; j < currentSimSize; j++)
            {
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                if(sim.grid.at(i).at(j).squareColor == SquareColor::white)
                {
                    square.setFillColor(sf::Color::White);
                }
                else
                {
                    square.setFillColor(sf::Color::Black);
                }
                square.setOutlineColor(sf::Color::Black);
                square.setOutlineThickness(squareSize / 10.0f);
                float x = j * squareSize;
                float y = i * squareSize;
                square.setPosition(x, y);
                window.draw(square);
            }
        }
        window.display();
    }

    return 0;
}