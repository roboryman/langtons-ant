#include "GUI.hpp"
#include <iostream>

GUI::GUI(Sim &sim) : sim(sim)
{
    SetupGUI();
}

void GUI::onTabSelected(std::string selectedTab)
{
    if (selectedTab == "Settings")
    {
        tgui.get("SettingsPanel")->setVisible(true);
        tgui.get("SimulationPanel")->setVisible(false);
    }
    else if (selectedTab == "Simulation")
    {
        tgui.get("SettingsPanel")->setVisible(false);
        tgui.get("SimulationPanel")->setVisible(true);
    }
}

void GUI::SaveButtonPressed()
{
    sim.stepsPerSecond = std::stoi( tgui.get<tgui::EditBox>("StepsPerSecondEditBox")->getText().toAnsiString() );
    sim.stepLimit = std::stoi( tgui.get<tgui::EditBox>("StepLimitEditBox")->getText().toAnsiString() );
    sim.size = std::stoi( tgui.get<tgui::EditBox>("TileMapSizeEditBox")->getText().toAnsiString() );
    sim.ruleset = tgui.get<tgui::EditBox>("RulesetEditBox")->getText().toAnsiString();
    switch(tgui.get<tgui::ComboBox>("DefaultDirectionComboBox")->getSelectedItemIndex())
    {
        case 0: sim.defaultDirection = AntDirection::N; break;
        case 1: sim.defaultDirection = AntDirection::E; break;
        case 2: sim.defaultDirection = AntDirection::S; break;
        case 3: sim.defaultDirection = AntDirection::W; break;
    }
    //sim.showAnt = tgui.get<tgui::CheckBox>("ShowAntCheckBox")->isChecked();
    sim.Reset();
}

void GUI::SetupGUI()
{
    auto tabs = tgui::Tabs::create();
    tabs->add("Settings", true);
    tabs->add("Simulation", false);
    tabs->connect("TabSelected", &GUI::onTabSelected, this);

    auto settingsPanel = tgui::Panel::create();
    auto spsLabel = tgui::Label::create("Steps/s");
    spsLabel->setPosition(100, 50);
    auto spsEditBox = tgui::EditBox::create();
    spsEditBox->setText("1");
    spsEditBox->setPosition(225, 50);
    spsEditBox->setSize(75, 20);
    auto slLabel = tgui::Label::create("Step Limit");
    slLabel->setPosition(100, 80);
    auto slEditBox = tgui::EditBox::create();
    slEditBox->setText("15000");
    slEditBox->setPosition(225, 80);
    slEditBox->setSize(75, 20);
    auto tsLabel = tgui::Label::create("Tilemap Size");
    tsLabel->setPosition(100, 110);
    auto tsEditBox = tgui::EditBox::create();
    tsEditBox->setText("200");
    tsEditBox->setPosition(225, 110);
    tsEditBox->setSize(75, 20);
    auto rsLabel = tgui::Label::create("Ruleset");
    rsLabel->setPosition(100, 140);
    auto rsEditBox = tgui::EditBox::create();
    rsEditBox->setText("RL");
    rsEditBox->setPosition(225, 140);
    rsEditBox->setSize(75, 20);
    auto ddLabel = tgui::Label::create("Default Direction");
    ddLabel->setPosition(100 , 170);
    auto ddComboBox = tgui::ComboBox::create();
    ddComboBox->setSize(150, 20);
    ddComboBox->setPosition(225, 170);
    ddComboBox->addItem("AntDirection::N");
    ddComboBox->addItem("AntDirection::E");
    ddComboBox->addItem("AntDirection::S");
    ddComboBox->addItem("AntDirection::W");
    ddComboBox->setSelectedItem("AntDirection::N");
    auto saLabel = tgui::Label::create("Show Ant Location");
    saLabel->setPosition(100, 200);
    auto saCheckBox = tgui::CheckBox::create();
    saCheckBox->setPosition(225, 200);
    saCheckBox->setEnabled(false);
    auto saveButton = tgui::Button::create();
    saveButton->setPosition(100, 230);
    saveButton->setText("Save");
    saveButton->setSize(100, 20);
    saveButton->connect("pressed", &GUI::SaveButtonPressed, this);
    auto exportButton = tgui::Button::create();
    exportButton->setPosition(225, 230);
    exportButton->setText("Export");
    exportButton->setSize(100, 20);
    auto infoLabel = tgui::Label::create("Interesting Rulesets");
    infoLabel->setPosition(600, 50);
    auto infoChatBox = tgui::ChatBox::create();
    infoChatBox->setSize(240, 200);
    infoChatBox->setTextSize(20);
    infoChatBox->setPosition(550, 80);
    infoChatBox->addLine("LR");
    infoChatBox->addLine("LRRL");
    infoChatBox->addLine("LLRR");
    infoChatBox->addLine("LRRRRRLLR");
    infoChatBox->addLine("RRLLLRLLLRRR");
    infoChatBox->addLine("LLRRRLRLRLLR");
    settingsPanel->add(spsLabel);
    settingsPanel->add(spsEditBox, "StepsPerSecondEditBox");
    settingsPanel->add(slLabel);
    settingsPanel->add(slEditBox, "StepLimitEditBox");
    settingsPanel->add(tsLabel);
    settingsPanel->add(tsEditBox, "TileMapSizeEditBox");
    settingsPanel->add(rsLabel);
    settingsPanel->add(rsEditBox, "RulesetEditBox");
    settingsPanel->add(ddLabel);
    settingsPanel->add(ddComboBox, "DefaultDirectionComboBox");
    settingsPanel->add(saLabel);
    settingsPanel->add(saCheckBox, "ShowAntCheckBox");
    settingsPanel->add(saveButton);
    settingsPanel->add(exportButton);
    settingsPanel->add(infoLabel);
    settingsPanel->add(infoChatBox);
    settingsPanel->setVisible(true);

    auto simulationPanel = tgui::Panel::create({"100%", tabs->getSize().y});
    auto controlPanel = tgui::HorizontalLayout::create({"100%", tabs->getSize().y});
    controlPanel->setPosition(tabs->getSize().x, 0);
    auto toggleSimButton = tgui::Button::create("Start / Stop");
    toggleSimButton->connect("pressed", &Sim::ToggleActive, &sim);
    auto resetSimButton = tgui::Button::create("Reset");
    resetSimButton->connect("pressed", &Sim::Reset, &sim);
    auto stepsPerSecondLabel = tgui::Label::create();
    auto stepLimitLabel = tgui::Label::create();
    auto stepLabel = tgui::Label::create();
    controlPanel->add(toggleSimButton, "ToggleSimButton");
    controlPanel->add(resetSimButton, "ResetSimButton");
    controlPanel->add(stepsPerSecondLabel, "StepsPerSecondLabel");
    controlPanel->add(stepLimitLabel, "StepLimitLabel");
    controlPanel->add(stepLabel, "StepLabel");
    controlPanel->addSpace(0.5f);
    simulationPanel->add(controlPanel, "ControlPanel");
    simulationPanel->setVisible(false);

    tgui.add(settingsPanel, "SettingsPanel");
    tgui.add(simulationPanel, "SimulationPanel");
    tgui.add(tabs, "Tabs");
}

void GUI::DisplayRenderWindow(int wSize, std::string wTitle)
{
    sf::RenderWindow rw(sf::VideoMode(wSize, wSize), wTitle);
    rw.setFramerateLimit(60);

    sf::View simView = rw.getDefaultView();
    simView.setSize(DEFAULT_ZOOM, DEFAULT_ZOOM);

    rw.setView(simView);
    tgui.setTarget(rw);

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
            else if(event.type == sf::Event::MouseWheelMoved && tgui.get<tgui::Panel>("SimulationPanel")->isVisible())
            {
                auto currentSize = simView.getSize();
                int deltaModified = event.mouseWheel.delta * (int) wSize / ZOOM_MODIFIER;
                if((currentSize.x > (wSize / ZOOM_MODIFIER) || event.mouseWheel.delta < 0) && (currentSize.x < wSize || event.mouseWheel.delta > 0))
                {
                    simView.setSize(currentSize.x - deltaModified, currentSize.y - deltaModified);
                    rw.setView(simView);
                }
            }
            tgui.handleEvent(event);
        }

        tgui.get<tgui::Label>("StepsPerSecondLabel")->setText("Step / s: " + std::to_string(sim.stepsPerSecond));
        tgui.get<tgui::Label>("StepLimitLabel")->setText("Limit: " + std::to_string(sim.stepLimit));
        tgui.get<tgui::Label>("StepLabel")->setText("Step: " + std::to_string(sim.step));

        rw.clear(sf::Color::Blue);
        rw.draw(sim.GetTileMap());
        tgui.draw();
        rw.display();
    }
}