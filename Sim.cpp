#include <iostream>
#include <unistd.h>
#include <unordered_map>
#include "Sim.hpp"

Sim::Sim(int windowSize, int stepLimit, short defaultColor, AntDirection defaultDirection, int stepsPerSecond, std::string ruleset, bool showAnt, int size)
{
    this->windowSize = windowSize;
    this->size = size;
    this->antRow = size / 2;
    this->antCol = size / 2;
    this->antDirection = defaultDirection;
    this->defaultDirection = defaultDirection;
    this->step = 0;
    this->stepsPerSecond = stepsPerSecond;
    this->defaultColor = defaultColor;
    this->tileData = std::vector<short> (size*size, defaultColor);
    this->active = false;
    this->finished = false;
    this->stepLimit = stepLimit;
    this->ruleset = ruleset;
    this->showAnt = showAnt;
    this->windowClosed = false;
}

void Sim::Start()
{
    std::cout << __FILE__ << ": Simulation started." << std::endl;

    // Setup the TileMap, the visualization of the tile data.
    tileMap.Setup(windowSize / (float) size, size, tileData);

    // Keep running the thread forever until the window is closed
    while(!windowClosed)
    {
        // Only perform a step if the simulation is active and not finished.
        if(active && !finished)
        {
            useconds_t periodicity = 1.0f / stepsPerSecond * 1000000;
            SimStep();

            // Make sure ant is inside bounds and step < step limit.
            CheckIfFinished();

            // Sleep between steps! (todo: use sf::Timer instead)
            usleep(periodicity);
        }
    }

    std::cout << __FILE__ << ": Simulated stopped." << std::endl;
}

void Sim::SimStep()
{
    // Get the current tileData position of our ant.
    int antIndex = TransformToRowMajorIndex(antRow, antCol);

    // 3 color example
    // L R L:
    // 0 1 2
    //
    // 0: Flip to 1, turn left, go forwards
    // 1: Flip to 2, turn right, go forwards
    // 2: Flip to 0, turn left, go forwards 

    // Rotate the ant based on the rule.
    if(ruleset.at(tileData.at(antIndex)) == 'L')
    {
        RotateAntCounterClockwise();
    }
    else if(ruleset.at(tileData.at(antIndex))  == 'R')
    {
        RotateAntClockwise();
    }

    // "Flip" the tile to the next rule/color.
    tileData.at(antIndex) += 1;

    // Perhaps we went past the end of our ruleset... then cycle back!
    if(tileData.at(antIndex) == ruleset.length())
    {
        tileData.at(antIndex) = 0;
    }

    // Make sure to update the tile we just changed.
    tileMap.UpdateTile(antIndex, tileData);

    // Move the ant forward to the next tile and that completes a step.
    MoveAntForward();
    step++;
}

void Sim::RotateAntClockwise()
{
    // todo; find a way to do a bimap easily
    std::unordered_map<AntDirection, AntDirection> CTransformation;
    CTransformation.emplace(N, E);
    CTransformation.emplace(E, S);
    CTransformation.emplace(S, W);
    CTransformation.emplace(W, N);

    antDirection = CTransformation[antDirection];
}

void Sim::RotateAntCounterClockwise()
{
    std::unordered_map<AntDirection, AntDirection> CCTransformation;
    CCTransformation.emplace(N, W);
    CCTransformation.emplace(W, S);
    CCTransformation.emplace(S, E);
    CCTransformation.emplace(E, N);
    
    antDirection = CCTransformation[antDirection];
}

void Sim::MoveAntForward()
{
    // JUST DO IT
    switch(antDirection)
    {
        case N:
            antRow -= 1;
            break;
        case E:
            antCol += 1;
            break;
        case S:
            antRow += 1;
            break;
        case W:
            antCol -= 1;
            break;
    }
}


void Sim::CheckIfFinished()
{
    if (step >= stepLimit)
    {
        // Ah shit, we've reached the step limit.
        std::cout << __FILE__ << ": Reached step limit of " << stepLimit << "." << std::endl;
        finished = true;
        active = false;
    }
    if(    (antRow < 0) || (antRow >= size)
        || (antCol < 0) || (antCol >= size))
    {
        // Ah shit, the ant has gone OUT of bounds! :O
        std::cout << __FILE__ << ": Ant traversed out of bounds." << std::endl;
        finished = true;
        active = false;
    }
}

int Sim::TransformToRowMajorIndex(int row, int col)
{
    return row*size + col;
}

void Sim::ToggleActive()
{
    this->active = !this->active;
}

void Sim::SetActive(bool active)
{
    this->active = active;
}

void Sim::Reset()
{
    std::cout << "Resetting simulation." << std::endl;

    // Yeah, let's not have the simulation thread stepping while resetting.
    active = false;
    finished = false;

    // Reset back to step 0 defaults.
    antRow = size / 2;
    antCol = size / 2;
    antDirection = defaultDirection;
    step = 0;

    // Birth our tileData anew.
    tileData.clear();
    tileData = std::vector<short> (size*size, defaultColor);

    // Can't forget to re-setup the TileMap.
    tileMap.Setup(windowSize / (float) size, size, tileData);
}

TileMap& Sim::GetTileMap()
{
    return tileMap;
}

void Sim::SetNewSettings(int stepsPerSecond, int stepLimit, int size, std::string ruleset, int defaultDirection, bool showAnt)
{
    this->stepsPerSecond = stepsPerSecond;
    this->stepLimit = stepLimit;
    this->size = size;
    this->ruleset = ruleset;
    switch(defaultDirection)
    {
        case 0: this->defaultDirection = AntDirection::N; break;
        case 1: this->defaultDirection = AntDirection::E; break;
        case 2: this->defaultDirection = AntDirection::S; break;
        case 3: this->defaultDirection = AntDirection::W; break;
    }
    this->showAnt = showAnt;
}

void Sim::WindowClosed()
{
    this->windowClosed = true;
}

int Sim::GetStep()
{
    return step;
}

int Sim::GetStepLimit()
{
    return stepLimit;
}

int Sim::GetStepsPerSecond()
{
    return stepsPerSecond;
}