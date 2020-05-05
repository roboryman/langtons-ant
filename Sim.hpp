#pragma once

#include <vector>
#include <string>
#include "TileMap.hpp"

using std::vector;
using std::string;

enum AntDirection { N, E, S, W };

class Sim
{
    void SimStep();
    void RotateAntClockwise();
    void RotateAntCounterClockwise();
    void MoveAntForward();
    void CheckIfFinished();
    void PrintGrid();
    int TransformToRowMajorIndex(int row, int col);
    int windowSize;
    TileMap tileMap;
    int antRow;
    int antCol;
    AntDirection antDirection;
    short defaultColor;
    bool active;
    bool finished;
    public:
        vector<short> tileData;
        int step;
        int stepsPerSecond;
        int stepLimit;
        int size;
        string ruleset;
        bool showAnt;
        AntDirection defaultDirection;
        Sim(int windowSize = 1000, int stepLimit = 15000, short defaultColor = 0, AntDirection defaultDirection = N, int stepsPerSecond = 1, string ruleset = "RL", bool showAnt = true, int size = 999);
        void Start();
        void ToggleActive();
        void SetActive(bool active);
        void Reset();
        void setStepsPerSecond(int stepsPerSecond);
        TileMap& GetTileMap();
};