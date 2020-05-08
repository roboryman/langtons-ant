#pragma once

#include <vector>
#include <string>
#include "TileMap.hpp"

// Represents the possible directions the ant can be in.
enum AntDirection { N, E, S, W };

/**
 * Sim
 * Defines a Langton's Ant Simulation.
 */
class Sim
{
    std::vector<short> tileData;
    TileMap tileMap;
    AntDirection antDirection;
    AntDirection defaultDirection;
    std::string ruleset;
    short defaultColor;
    int windowSize;
    int antRow;
    int antCol;
    int step;
    int stepsPerSecond;
    int stepLimit;
    int size;
    bool active;
    bool finished;
    bool showAnt;
    bool windowClosed;
    
    // Step forward in the simulation, according to the ruleset.
    void SimStep();

    // Rotate the ant 90 deg clockwise, equivalent to a "R" rule.
    void RotateAntClockwise();

    // Rotate the ant 90 deg counter-clockwise, equivalent to a "L" rule.
    void RotateAntCounterClockwise();

    // Move the ant "forward" based on its current direction.
    void MoveAntForward();

    // Check if the ant has reached the step limit or traversed outside of the TileMap.
    void CheckIfFinished();

    // Return the index of a given 2D location in the simulation data.
    int TransformToRowMajorIndex(int row, int col);

    public:
        // No point in 1-liner getters and setters.

        // Construct a Langton's ant simulation with given properties.
        Sim(int windowSize = 1000, int stepLimit = 15000, short defaultColor = 0, AntDirection defaultDirection = N, int stepsPerSecond = 1, std::string ruleset = "RL", bool showAnt = true, int size = 999);
        
        // Start the simulation, stepping until stopped or window closed.
        void Start();

        // Toggle the active status of the simulation.
        void ToggleActive();

        // Set the active status of the simulation.
        void SetActive(bool active);

        // Stop and completely reset the properties of the simulation.
        void Reset();

        // Return a reference to the TileMap used by the simulation, possibly for drawing.
        TileMap& GetTileMap();

        // Alter the simulation.
        void SetNewSettings(int stepsPerSecond, int stepLimit, int size, std::string ruleset, int defaultDirection, bool showAnt);

        // Signal that the Render Window has closed.
        void WindowClosed();

        // Getter for the current step.
        int GetStep();

        // Getter for the step limit.
        int GetStepLimit();

        // Getter for the steps per second.
        int GetStepsPerSecond();
};