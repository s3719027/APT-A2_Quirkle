#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include "Helper.h"
#include "Bag.h"
#include <sstream>
#include <iostream>
#include <fstream>
class StartGame{
  public:
      StartGame();
      ~StartGame();
      bool GameOver();
      void SetUpGame();
      void PlayerSignIn(std::string);
      void playerMovement(Player* player,Board* board);
      bool isTilesOnHand(Player* player,std::string word);
      bool isInBoard(Board* limitBoard,int row, int col);
      void showGameInfo(Player* player);
      void replaceTileOnHand(Player* player, std::string tilename);
      bool qwrikleRule(Tile* tile, int row, int col,Board* board);
      bool isEmpty(Board* board);
      void givePlayerScore(Board* board, int row, int col);
      int countTilesInBoard(Board* board, int row, int col,std::string direction);
      void calculatePlayerScores(Board* board, int row, int col);
      void giveScore(Player* player);
  private:
    Board* board;
    Player* player1;
    Player* player2;
    int score = 0;
    bool isFirstTile=true;
    bool qwirkle=false;
    std::string currentPlayerName;
    LinkedList* tileBag;
    //for same color different shape or same shape different color
    bool vaildInput(std::string input);
    bool isSameColor(Tile* tile1, Tile* tile2);
    bool isSameShape(Tile* tile1, Tile* tile2);
    void saveGame(std::string saveName, Board* board, LinkedList* tilebag, Player* player1, Player* player2,std::string currentName);
    void loadGame(std::string fileName);

};
