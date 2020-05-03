#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <unordered_map>
#include <SFML/System.hpp>
#include "Sim.hpp"

#define DEF_SPS 1000.0f
#define DEF_DIRECTION AntDirection::N;
#define SIZE_LIMIT 1000
#define DEFAULT_SIZE 999
#define STEP_LIMIT 20000

using std::cout;
using std::endl;
using std::vector;

// Constructor for a simulation with empty 
Sim::Sim(int windowSize, TileMap *map, SquareColor defaultColor)
{
    this->windowSize = windowSize;
    this->size = DEFAULT_SIZE;
    this->map = map;
    this->antRow = size / 2;
    this->antCol = size / 2;
    this->antDirection = DEF_DIRECTION;
    this->step = 0;
    this->stepsPerSecond = DEF_SPS;
    this->tileData = vector<short> (size*size, defaultColor);
}

Sim::Sim(int windowSize, string gridPath)
{
    this->windowSize = windowSize;
    // Get the size and data from the disk
    //this->size = .....
    //this->grid = new Square[size * size];
}

void Sim::StartSim()
{
    cout << __FILE__ << ": Simulation started." << endl;

    map->load(windowSize / (float) size, size, tileData);
    while(CheckIfActive())
    {
        useconds_t periodicity = 1.0f / stepsPerSecond * 1000000;
        SimStep();
        usleep(periodicity);
    }

    cout << __FILE__ << ": Simulated stopped." << endl;
}

void Sim::SimStep()
{
    int antIndex = TransformToRowMajorIndex(antRow, antCol);

    if(tileData.at(antIndex) == SquareColor::White)
    {
        RotateAntClockwise();
        tileData.at(antIndex) = SquareColor::Black;
    }
    else
    {
        RotateAntCounterClockwise();
        tileData.at(antIndex) = SquareColor::White;
    }

    map->UpdateTile(antIndex, tileData);
    MoveAntForward();
    step++;
}

void Sim::RotateAntClockwise()
{
    // todo; find a way to do a bimap easily
    std::unordered_map<AntDirection, AntDirection> CTransformation;
    CTransformation.emplace(AntDirection::N, AntDirection::E);
    CTransformation.emplace(AntDirection::E, AntDirection::S);
    CTransformation.emplace(AntDirection::S, AntDirection::W);
    CTransformation.emplace(AntDirection::W, AntDirection::N);

    antDirection = CTransformation[antDirection];
}

void Sim::RotateAntCounterClockwise()
{
    std::unordered_map<AntDirection, AntDirection> CCTransformation;
    CCTransformation.emplace(AntDirection::N, AntDirection::W);
    CCTransformation.emplace(AntDirection::W, AntDirection::S);
    CCTransformation.emplace(AntDirection::S, AntDirection::E);
    CCTransformation.emplace(AntDirection::E, AntDirection::N);
    
    antDirection = CCTransformation[antDirection];
}

void Sim::MoveAntForward()
{    
    switch(antDirection)
    {
        case AntDirection::N:
            antRow -= 1;
            break;
        case AntDirection::E:
            antCol += 1;
            break;
        case AntDirection::S:
            antRow += 1;
            break;
        case AntDirection::W:
            antCol -= 1;
            break;
    }
}


bool Sim::CheckIfActive()
{
    if (step >= STEP_LIMIT)
    {
        cout << __FILE__ << ": Reached step limit of " << STEP_LIMIT << "." << endl;
        return false;
    }
    if(    (antRow < 0) || (antRow >= size)
        || (antCol < 0) || (antCol >= size))
    {
        
        cout << __FILE__ << ": Ant traversed out of bounds." << endl;
        return false;
    }

    return true;
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