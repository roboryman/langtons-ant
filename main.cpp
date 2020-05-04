#include <thread>
#include <iostream>
#include <TGUI/TGUI.hpp>
#include <SFML/System.hpp>
#include "Sim.hpp"
#include "TileMap.hpp"

#define WINDOW_SIZE 1000
#define FRAMERATE 100
#define ZOOM_MODIFIER 40
#define DEFAULT_ZOOM 50.0f
#define STEP_LIMIT 40000
#define TILEMAP_SIZE 210

using std::cout;
using std::endl;

void onTabSelected(tgui::Gui& gui, std::string selectedTab)
{
    if (selectedTab == "Settings")
    {
        gui.get("SettingsPanel")->setVisible(true);
        gui.get("SimulationPanel")->setVisible(false);
    }
    else if (selectedTab == "Simulation")
    {
        gui.get("SettingsPanel")->setVisible(false);
        gui.get("SimulationPanel")->setVisible(true);
    }
}

int main()
{
    sf::RenderWindow rw(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Langton's Ant");
    rw.setFramerateLimit(FRAMERATE);
    sf::View simView = rw.getDefaultView();
    simView.setSize(DEFAULT_ZOOM, DEFAULT_ZOOM);
    rw.setView(simView);

    TileMap map(TILEMAP_SIZE);
    Sim sim(&map, WINDOW_SIZE, STEP_LIMIT, White, N, 4000);

    tgui::Gui gui{rw};
    auto tabs = tgui::Tabs::create();
    tabs->add("Settings", true);
    tabs->add("Simulation", false);
    tabs->connect("TabSelected", onTabSelected, std::ref(gui));

    auto settingsPanel = tgui::Panel::create();
    auto wipLabel = tgui::Label::create("wip");
    wipLabel->setPosition(0, 100);
    settingsPanel->add(wipLabel);
    settingsPanel->setVisible(true);

    auto simulationPanel = tgui::Panel::create({"100%", tabs->getSize().y});
    //auto controlPanel = tgui::Panel::create({"100%", tabs->getSize().y});
    auto controlPanel = tgui::HorizontalLayout::create({"100%", tabs->getSize().y});
    controlPanel->setPosition(tabs->getSize().x, 0);

    auto toggleSimButton = tgui::Button::create("Start / Stop");
    //toggleSimButton->setPosition(tabs->getSize().x, 0);
    toggleSimButton->connect("pressed", &Sim::ToggleActive, &sim);
    controlPanel->add(toggleSimButton);

    auto resetSimButton = tgui::Button::create("Reset");
    //resetSimButton->setPosition(toggleSimButton->getPosition().x+toggleSimButton->getSize().x, 0);
    resetSimButton->connect("pressed", &Sim::Reset, &sim);
    controlPanel->add(resetSimButton);

    auto stepsPerSecondLabel = tgui::Label::create("Step / s: " + std::to_string(sim.stepsPerSecond));
    //stepsPerSecondLabel->setPosition(stepLabel->getPosition().x + 50, 0);
    controlPanel->add(stepsPerSecondLabel);

    auto stepLimitLabel = tgui::Label::create("Limit: " + std::to_string(sim.stepLimit));
    controlPanel->add(stepLimitLabel);

    auto stepLabel = tgui::Label::create();
    //stepLabel->setPosition(resetSimButton->getPosition().x + resetSimButton->getSize().x, 0);
    controlPanel->add(stepLabel);

    //controlPanel->insertSpace(1, 0.1f);
    controlPanel->addSpace(0.5f);

    simulationPanel->add(controlPanel);
    simulationPanel->setVisible(false);

    gui.add(settingsPanel, "SettingsPanel");
    gui.add(simulationPanel, "SimulationPanel");
    gui.add(tabs, "Tabs");

    std::thread simThread(&Sim::Start, &sim);

    sf::Event event;
	sf::Clock clock;

    while (rw.isOpen())
    {
        sf::Event event;
        while (rw.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                rw.close();
            }
            else if(event.type == sf::Event::MouseWheelMoved && simulationPanel->isVisible())
            {
                auto currentSize = simView.getSize();
                int deltaModified = event.mouseWheel.delta * WINDOW_SIZE / ZOOM_MODIFIER;
                if((currentSize.x > (WINDOW_SIZE / ZOOM_MODIFIER) || event.mouseWheel.delta < 0) && (currentSize.x < WINDOW_SIZE || event.mouseWheel.delta > 0))
                {
                    simView.setSize(currentSize.x - deltaModified, currentSize.y - deltaModified);
                    rw.setView(simView);
                }
            }
            gui.handleEvent(event);
        }

        stepLabel->setText("Step: " + std::to_string(sim.step));

        rw.clear(sf::Color::Blue);
        rw.draw(map);
        gui.draw();
        rw.display();
    }

    return 0;
}