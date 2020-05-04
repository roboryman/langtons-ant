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
    void CheckIfFinished();
    void PrintGrid();
    int TransformToRowMajorIndex(int row, int col);
    sf::Vector2i TransformToRowCol(int index);
    int windowSize;
    int size;
    TileMap *map;
    int antRow;
    int antCol;
    AntDirection antDirection;
    AntDirection defaultDirection;
    SquareColor defaultColor;
    bool active;
    bool finished;
    public:
        vector<short> tileData;
        int step;
        int stepsPerSecond;
        int stepLimit;
        Sim(TileMap *map, int windowSize, int stepLimit, SquareColor defaultColor = White, AntDirection defaultDirection = N, int stepsPerSecond = 1);
        void Start();
        void ToggleActive();
        void SetActive(bool active);
        void Reset();
        void setStepsPerSecond(int stepsPerSecond);
};