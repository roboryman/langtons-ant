#pragma once

#include <string>
#include <TGUI/TGUI.hpp>
#include "Sim.hpp"

// Define useful defaults for the GUI
#define DEFAULT_ZOOM 50.0f
#define ZOOM_MODIFIER 40
#define STEP_LIMIT 15000


/**
 * GUI
 * Defines the GUI shown to the user.
 */
class GUI
{
    Sim &sim;
    tgui::Gui tgui;

    // Show or display panels based on the newly selected tab.
    void onTabSelected(std::string selectedTab);

    // Communicate our new settings to the simulation, and reset it.
    void SaveButtonPressed();

    // Create, setup, and add all GUI widgets to the render tree.
    void SetupGUI();

    public:
        // Construct a GUI for a particular simulation.
        GUI(Sim &sim);

        // Create a SFML Render Window and display our GUI and simulation on it.
        void DisplayRenderWindow(int wSize, std::string wTitle);
};