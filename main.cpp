#include <thread>
#include "Sim.hpp"
#include "GUI.hpp"

#define WINDOW_SIZE 1000

int main()
{
    Sim sim;
    GUI gui(sim);
    std::thread simThread(&Sim::Start, &sim);

    gui.DisplayRenderWindow(WINDOW_SIZE, "Langton's Ant");

    return 0;
}