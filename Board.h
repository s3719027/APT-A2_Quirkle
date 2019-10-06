#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H


#include "Tile.h"
#include "Helper.h"
#include <iostream>
#include <vector>


using std::vector;
using std::string;

class Board {
public:

  Board(int rows, int cols);

  ~Board();

  void store(Tile* tile, int row, int col);

  void printBoard();

  string boardHeaderToString();

  string boardBodyToString();

  int getRows();

  int getCols();

  vector<vector<Tile*> > getTilesOnBoard();

  bool isWithinBound(int atRow, int atCol);

private:
  int rows = 0;
  int cols = 0;
  int maxRows = 26;
  int maxCols = 26;
  vector<vector<Tile*> > tilesOnBoard;

};

#endif
