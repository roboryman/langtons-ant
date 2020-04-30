#pragma once

enum SquareColor { white, black };

struct Square
{
    SquareColor squareColor;
    Square();
    Square(SquareColor squareColor);
};