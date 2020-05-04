#include <iostream>
#include <iomanip>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <SFML/System.hpp>
#include "Sim.hpp"

using std::cout;
using std::endl;
using std::vector;

// Constructor for a simulation with empty 
Sim::Sim(TileMap *map, int windowSize, int stepLimit, SquareColor defaultColor, AntDirection defaultDirection, int stepsPerSecond)
{
    this->windowSize = windowSize;
    this->size = map->size;
    this->map = map;
    this->antRow = size / 2;
    this->antCol = size / 2;
    this->antDirection = defaultDirection;
    this->defaultDirection = defaultDirection;
    this->step = 0;
    this->stepsPerSecond = stepsPerSecond;
    this->defaultColor = defaultColor;
    this->tileData = vector<short> (size*size, defaultColor);
    this->active = false;
    this->finished = false;
    this->stepLimit = stepLimit;
}


void Sim::Start()
{
    cout << __FILE__ << ": Simulation started." << endl;

    map->load(windowSize / (float) size, size, tileData);
    while(true)
    {
        if(active && !finished)
        {
            useconds_t periodicity = 1.0f / stepsPerSecond * 1000000;
            SimStep();
            CheckIfFinished();
            usleep(periodicity);
        }
    }

    cout << __FILE__ << ": Simulated stopped." << endl;
}

void Sim::SimStep()
{
    int antIndex = TransformToRowMajorIndex(antRow, antCol);

    if(tileData.at(antIndex) == White)
    {
        RotateAntClockwise();
        tileData.at(antIndex) = Black;
    }
    else
    {
        RotateAntCounterClockwise();
        tileData.at(antIndex) = White;
    }

    map->UpdateTile(antIndex, tileData);
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
        cout << __FILE__ << ": Reached step limit of " << stepLimit << "." << endl;
        finished = true;
        active = false;
    }
    if(    (antRow < 0) || (antRow >= size)
        || (antCol < 0) || (antCol >= size))
    {
        
        cout << __FILE__ << ": Ant traversed out of bounds." << endl;
        finished = true;
        active = false;
    }
}

void Sim::PrintGrid()
{
    cout << "Tile data size: " << tileData.size();
    vector<short>::size_type tdS = tileData.size();
    for (int i = 0; i < tdS; i++)
    {
        if(i % size == 0)
            cout << endl;
        cout << tileData[i] << " ";
    }

    cout << endl;
}

int Sim::TransformToRowMajorIndex(int row, int col)
{
    return row*size + col;
}

sf::Vector2i Sim::TransformToRowCol(int index)
{
    return sf::Vector2i(index / size, index % size);
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
    cout << "Resetting simulation." << endl;
    active = false;
    finished = false;
    antRow = size / 2;
    antCol = size / 2;
    antDirection = defaultDirection;
    step = 0;
    std::fill(tileData.begin(), tileData.end(), defaultColor);
    map->load(windowSize / (float) size, size, tileData);
}


void Sim::setStepsPerSecond(int stepsPerSecond)
{
    this->stepsPerSecond = stepsPerSecond;
}