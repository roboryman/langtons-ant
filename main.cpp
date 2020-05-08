#include <thread>
#include "GUI.hpp"

#define WINDOW_SIZE 1000

// Kick off the GUI. Ant simulation goes on a seperate thread.
int main()
{
    // Construct a new Sim and GUI.
    Sim sim;
    GUI gui(sim);

    // Start the simulation on a seperate thread, so it is independent of the GUI.
    std::thread simThread(&Sim::Start, &sim);

    // Display the GUI on a Render Window.
    gui.DisplayRenderWindow(WINDOW_SIZE, "Langton's Ant");

    // When the Render Window has closed, join the simulation thread.
    simThread.join();

    return 0;
}