
#include "Tile.h"

// Empty... for now?
Tile::Tile(Colour colour, Shape shape)
{
  this->colour=colour;
  this->shape=shape;
}

std::String Tile::toString()
{
  return colour + std::to_string(shape);
}

Colour Tile::getColour()
{
  return colour;
}
Shape Tile::getShape()
{
  return shape;
}
