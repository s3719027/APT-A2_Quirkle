#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H


#include "Tile.h"
#include "Helper.h"
#include <iostream>
#include <vector>


class Board {
public:

  Board(int rows, int cols);

  ~Board();

  void store(Tile* tile, int row, int col);

  void printBoard();

  std::string boardHeaderToString();

  std::string boardBodyToString();

  int getRows();

  int getCols();

  std::vector<std::vector<Tile*> > getTilesOnBoard();

private:
  int rows = 0;
  int cols = 0;
  int maxRows = 26;
  int maxCols = 26;
  std::vector<std::vector<Tile*> > tilesOnBoard;

};

#endif
