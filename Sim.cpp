
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <math.h>
#include "Sim.hpp"

using std::cout;
using std::endl;

Sim::Sim()
{
    this->size = 0;
    this->step = 0;
    this->stepsPerSecond = 100;
    this->initialized = false;
    this->antRow = 0;
    this->antCol = 0;
    this->antDirection = Direction::N;
}

void Sim::InitializeGrid(int size)
{
    if(size % 2 == 0)
    {
        cout << __FILE__ << ": Grid must be initialized to odd size." << endl;
        return;
    }

    this->size = size;
    for(int i = 0; i < size; i++)
    {
        this->grid.push_back(vector<Square>(size));
    }

    this->initialized = true;
    this->antRow = size / 2;
    this->antCol = size / 2;
}

void Sim::InitializeGrid(string spaceName)
{
    // Exists check

    // Get the size and data from the disk
    //this->size = .....
    //this->grid = new Square[size * size];

    this->initialized = true;
    this->antRow = size / 2;
    this->antCol = size / 2;
}

void Sim::StartSim()
{
    if(!this->initialized)
    {
        cout << __FILE__ << ": Simulation not started (Space is not initialized)." << endl;
        return;
    }
    cout << __FILE__ << ": Started the simulation." << endl;

    PrintGrid();
    while(true)
    {
        for(int i = 0; i < this->stepsPerSecond; i++)
        {
            SimStep();
            PrintGrid();
        }
        sleep(1);
    }
}

int Sim::GetStepsPerSecond()
{
    return this->stepsPerSecond;
}

void Sim::SetStepsPerSecond(int stepsPerSecond)
{
    this->stepsPerSecond = stepsPerSecond;
}

int Sim::GetCurrentSize()
{
    return this->size;
}

void Sim::SimStep()
{
    //int antLocation = GetIndex(this->antRow, this->antCol);
    if(this->grid[antRow][antCol].squareColor == SquareColor::white)
    {
        RotateAntClockwise();
        this->grid[antRow][antCol].squareColor = SquareColor::black;
    }
    else
    {
        RotateAntCounterClockwise();
        this->grid[antRow][antCol].squareColor = SquareColor::white;
    }

    MoveAntForward();
    this->step++;
}

void Sim::RotateAntClockwise()
{
    switch(this->antDirection)
    {
        case Direction::N:
            this->antDirection = Direction::E;
            break;
        case Direction::E:
            this->antDirection = Direction::S;
            break;
        case Direction::S:
            this->antDirection = Direction::W;
            break;
        case Direction::W:
            this->antDirection = Direction::N;
            break;
    }
}

void Sim::RotateAntCounterClockwise()
{
    switch(this->antDirection)
    {
        case Direction::N:
            this->antDirection = Direction::W;
            break;
        case Direction::E:
            this->antDirection = Direction::N;
            break;
        case Direction::S:
            this->antDirection = Direction::E;
            break;
        case Direction::W:
            this->antDirection = Direction::S;
            break;
    }
}

void Sim::MoveAntForward()
{    
    switch(this->antDirection)
    {
        case Direction::N:
            this->antRow -= 1;
            break;
        case Direction::E:
            this->antCol += 1;
            break;
        case Direction::S:
            this->antRow += 1;
            break;
        case Direction::W:
            this->antCol -= 1;
            break;
    }

    CheckBoundaries();
}

int Sim::GetIndex(int row, int col)
{
    return row * this->size + col;
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


        for(int i = 0; i < this->size; i++)
        {
            Square square;
            this->grid[i].insert(this->grid[i].begin(), square);
            this->grid.at(i).push_back(square);
        }

        this->size += 2;

        this->grid.insert(this->grid.begin(), vector<Square>(this->size));
        this->grid.push_back(vector<Square>(this->size));
    }
}

void Sim::PrintGrid()
{
    /*
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cout << this->grid[i][j].squareColor;
        }
        cout << endl;
    }
    cout << endl;

    cout << "Ant at row: " << this->antRow << ", col: " << this->antCol << endl;
    /*
    if((this->step % 5 == 0) && this->step < 1000)
    {
        cout << "STEP " << std::setw(15) << std::right << this->step << ": \033[1;4;31mCHAOS\033[0m" << endl;
    }
    else if((this->step % 5 == 0) && (this->step < 10000))
    {
          cout << "STEP " << std::setw(15) << std::right << this->step << ": \033[1;33mMIXED\033[0m" << endl;
    }
    else if((this->step % 5 == 0) && (this->step > 10000))
    {
        cout << "STEP " << std::setw(15) << std::right << this->step << ": \033[1;4;32mORDER\033[0m" << endl;
      }
    */
   if(this->step % 100 == 0)
   {
       cout << "STEP " << this->step << endl;
   }
}