#pragma once

#include <vector>
#include <string>
#include "TileMap.hpp"
#include <SFML/System/Vector2.hpp>

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
    bool CheckIfActive();
    void PrintGrid();
    int TransformToRowMajorIndex(int row, int col);
    sf::Vector2i TransformToRowCol(int index);
    int windowSize;
    int size;
        TileMap *map;
        int antRow;
        int antCol;
        AntDirection antDirection;
        int step;
        float stepsPerSecond;
    public:
        Sim(int windowSize, TileMap *map, SquareColor defaultColor);
        Sim(int windowSize, string gridPath);
        void StartSim();
        vector<short> tileData;
};