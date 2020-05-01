#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

enum AntDirection { N, E, S, W };
enum SquareColor { White, Black };

class Sim
{
    void SimStep();
    void RotateAntClockwise();
    void RotateAntCounterClockwise();
    void MoveAntForward();
    void CheckBoundaries();
    void PrintGrid();
    public:
        Sim();
        Sim(string gridPath);
        void StartSim();

        int size;
        int antRow;
        int antCol;
        AntDirection antDirection;
        int step;
        float stepsPerSecond;
        vector<vector<int>> grid;
};