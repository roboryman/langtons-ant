#pragma once

#include <string>
#include <TGUI/TGUI.hpp>
#include "Sim.hpp"
#include "TileMap.hpp"

#define DEFAULT_ZOOM 50.0f
#define ZOOM_MODIFIER 40
#define WINDOW_SIZE 1000
#define STEP_LIMIT 15000

class GUI
{
    Sim &sim;
    tgui::Gui tgui;
    void onTabSelected(std::string selectedTab);
    void SaveButtonPressed();
    void SetupGUI();
    public:
        GUI(Sim &sim);
        void SetTileMap(TileMap &tileMap);
        void DisplayRenderWindow(int wSize, std::string wTitle);
};