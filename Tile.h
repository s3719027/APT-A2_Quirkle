
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
  Tile();
   Tile(Colour _colour, Shape _shape);
   ~Tile();
   char getColour();
   int getShape();
   bool checkSimilar( Tile *tile );
   bool checkEmpty();

   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H
