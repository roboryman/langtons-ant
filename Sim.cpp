#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <SFML/System.hpp>
#include "Sim.hpp"

#define DEF_SPS 1000.0f
#define DEF_DIRECTION AntDirection::N;
#define SIZE_LIMIT 1000
#define DEFAULT_SIZE 111

using std::cout;
using std::endl;
using std::vector;

Sim::Sim(int windowSize, TileMap *map)
{
    this->windowSize = windowSize;
    this->size = DEFAULT_SIZE;
    this->map = map;
    this->antRow = size / 2;
    this->antCol = size / 2;
    this->antDirection = DEF_DIRECTION;
    this->step = 0;
    this->stepsPerSecond = DEF_SPS;
    this->tileData = vector<short> (size*size, 0);
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
    cout << __FILE__ << ": Started the simulation." << endl;

    map->update(windowSize / (float) size, size, tileData);
    while(true)
    {
        useconds_t periodicity = 1.0f / stepsPerSecond * 1000000;
        SimStep();
        //PrintGrid();
        usleep(periodicity);
    }
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
    this->step++;
}

void Sim::RotateAntClockwise()
{
    // todo; find a way to do a bimap easily
    std::unordered_map<AntDirection, AntDirection> CTransformation;
    CTransformation.emplace(AntDirection::N, AntDirection::E);
    CTransformation.emplace(AntDirection::E, AntDirection::S);
    CTransformation.emplace(AntDirection::S, AntDirection::W);
    CTransformation.emplace(AntDirection::W, AntDirection::N);

    this->antDirection = CTransformation[this->antDirection];
}

void Sim::RotateAntCounterClockwise()
{
    std::unordered_map<AntDirection, AntDirection> CCTransformation;
    CCTransformation.emplace(AntDirection::N, AntDirection::W);
    CCTransformation.emplace(AntDirection::W, AntDirection::S);
    CCTransformation.emplace(AntDirection::S, AntDirection::E);
    CCTransformation.emplace(AntDirection::E, AntDirection::N);
    
    this->antDirection = CCTransformation[this->antDirection];
}

void Sim::MoveAntForward()
{    
    switch(this->antDirection)
    {
        case AntDirection::N:
            this->antRow -= 1;
            break;
        case AntDirection::E:
            this->antCol += 1;
            break;
        case AntDirection::S:
            this->antRow += 1;
            break;
        case AntDirection::W:
            this->antCol -= 1;
            break;
    }

    CheckBoundaries();
}

void Sim::CheckBoundaries()
{
    if(    (this->antRow < 0) || (this->antRow >= this->size)
        || (this->antCol < 0) || (this->antCol >= this->size))
    {
        if(this->antRow < 0)
        {
            this->antRow = 0;
            this->antCol += 1;
        }
        else if(this->antRow >= this->size)
        {
            this->antRow += 1;
            this->antCol += 1;
        }
        else if(this->antCol < 0)
        {
            this->antCol = 0;
            this->antRow += 1;
        }
        else if(this->antCol >= this->size)
        {
            this->antCol += 1;
            this->antRow += 1;
        }

        for (int i = 0; i < tileData.size(); i+=(size+1))
        {
            tileData.insert(tileData.begin() + i, 0);
        }
        for (int i = (size+1); i <= tileData.size(); i+=(size+2))
        {
            tileData.insert(tileData.begin() + i, 0);
        }
        size += 2;
        tileData.insert(tileData.begin(), size, 0);
        tileData.insert(tileData.end(), size, 0);
        map->update(windowSize / (float) size, size, tileData);
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