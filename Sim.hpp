#pragma once

#include <vector>
#include <string>
#include "Square.hpp"
#include <SFML/System.hpp>

using std::vector;
using std::string;

enum Direction { N, E, S, W };

class Sim
{
    int size;
    int step;
    int stepsPerSecond;
    bool initialized;
    int antRow;
    int antCol;
    Direction antDirection;

    void SimStep();
    void RotateAntClockwise();
    void RotateAntCounterClockwise();
    void MoveAntForward();
    void CheckBoundaries();
    int GetIndex(int row, int col);
    void PrintGrid();
    public:
        Sim();
        void InitializeGrid(int size);
        void InitializeGrid(string spaceName);
        void StartSim();
        int GetStepsPerSecond();
        void SetStepsPerSecond(int stepsPerSecond);
        int GetCurrentSize();
        vector<vector<Square>> grid;
};