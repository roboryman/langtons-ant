#include "Square.hpp"

Square::Square()
{
    this->squareColor = SquareColor::white;
}

Square::Square(SquareColor squareColor)
{
    this->squareColor = squareColor;
}