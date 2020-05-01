#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <unordered_map>
#include <SFML/System.hpp>
#include "Sim.hpp"

#define DEF_INIT_SIZE 3
#define DEF_SPS 5000.0f
#define DEF_DIRECTION AntDirection::N;
#define SIZE_LIMIT 10000

using std::cout;
using std::endl;
using std::vector;

Sim::Sim()
{
    this->size = DEF_INIT_SIZE;
    this->antRow = DEF_INIT_SIZE / 2;
    this->antCol = DEF_INIT_SIZE / 2;
    this->antDirection = DEF_DIRECTION;
    this->step = 0;
    this->stepsPerSecond = DEF_SPS;
    this->grid = vector<vector<int>> (DEF_INIT_SIZE, vector<int> (DEF_INIT_SIZE));
}

Sim::Sim(string gridPath)
{
    // Get the size and data from the disk
    //this->size = .....
    //this->grid = new Square[size * size];
}

void Sim::StartSim()
{
    cout << __FILE__ << ": Started the simulation." << endl;

    //PrintGrid();
    while(this->size < SIZE_LIMIT)
    {
        useconds_t periodicity = 1.0f / this->stepsPerSecond * 1000000;
        SimStep();
        //PrintGrid();
        usleep(periodicity);
    }
}

void Sim::SimStep()
{
    if(this->grid.at(antRow).at(antCol) == SquareColor::White)
    {
        RotateAntClockwise();
        this->grid.at(antRow).at(antCol) = SquareColor::Black;
    }
    else
    {
        RotateAntCounterClockwise();
        this->grid.at(antRow).at(antCol) = SquareColor::White;
    }

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

        this->grid.insert(this->grid.begin(), vector<int>(this->size, SquareColor::White));
        this->grid.push_back(vector<int>(this->size, SquareColor::White));
        this->size += 2;
        for(int i = 0; i < this->size; i++)
        {
            this->grid.at(i).insert(this->grid.at(i).begin(), SquareColor::White);
            this->grid.at(i).push_back(SquareColor::White);
        }
        cout << "New size: " << this->size << endl;
    }
}

void Sim::PrintGrid()
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout << this->grid.at(i).at(j);
        }
        cout << endl;
    }
    cout << endl;
}