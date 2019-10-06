#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include "Helper.h"
#include "Bag.h"
#include <sstream>
#include <iostream>
class StartGame{
  public:
      StartGame();
      ~StartGame();
      bool GameOver();
      void putTileOnBoard(Tile* tile);
      bool NoTilesOnBoard(int rows, int cols);
      void SetUpGame();
      std::string PlayerSignIn(std::string);
      void playerMovement(Player* player,Board* board);
      bool isTilesOnHand(Player* player,std::string word);
      bool isInBoard(Board* limitBoard,int row, int col);
      void showGameInfo(Player* player);
      void replaceTileOnHand(Player* player, std::string tilename);
      bool qwrikleRule(Tile* tile, int row, int col, std::vector<std::vector<Tile*>> tiles_on_board);
      bool isEmpty(Board* board);

  private:
    Board* board;
    Player* player1;
    Player* player2;
    int boardRows = 6;
    int boardCols = 6;
    int scoreToGive = 0;
    bool isFirstTile=true;
    std::string currentPlayerName;
    LinkedList* tileBag;
  //  void PlayerInterface(Player* a, Player* b, Board* board);
    bool IsVaildInput(std::string input);
    //for same color different shape or same shape different color
    bool isSameColor(Tile* tile1, Tile* tile2);
    bool isSameShape(Tile* tile1, Tile* tile2);
    void saveGame(std::string saveName, Board* board, LinkedList* tilebag, Player* player1, Player* player2,std::string currentName);
    void loadGame(std::string saveMName);
    void startLoadGame(Board* board, Player* player1, Player* player2, LinkedList* tileBag,
    LinkedList* player1Hand, LinkedList* player2Hand);
};
