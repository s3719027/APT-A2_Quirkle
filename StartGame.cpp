#include "StartGame.h"

StartGame::StartGame()
{
  //TO do {
    /* code */

}
StartGame::~StartGame()
{
  delete player1;
  delete player2;
  delete tileBag;
  delete board;
}
bool StartGame::GameOver()
{
  if(tileBag->size()==0&&(player1->getTilesOnHand()==0||player2->getTilesOnHand()==0))
   {
    return true;
   }
  return false;
}


void StartGame::SetUpGame()
{
  board=new Board(6,6);
  Bag* bag=new Bag();
  tileBag=bag->getBag();

  player1=new Player("AAA");
  player2=new Player("BBB");

  for (int i = 0; i < 6; i++){
    player1->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }

  //Player 2 get 6 tiles
  for (int i = 0; i < 6; i++){
    player2->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }
  currentPlayerName=player1->getName();
  while(!GameOver())
  {
    if(currentPlayerName==player1->getName())
    {
      showGameInfo(player1);
      playerMovement(player1,board);
      currentPlayerName=player2->getName();
    }else
    {
      showGameInfo(player2);
      playerMovement(player2,board);
      currentPlayerName=player1->getName();
    }
 }

}


/*std::string StartGame::PlayerSignIn(std::string player)
{
  std::string playerName="";
  std::cout<<"Enter a name for"<< player<<"(uppercase characters only)"<<std::endl;
  std::cin>>playerName;
  if(IsVaildInput(playerName)==true)
  {
   std::cout<<"Let's play!"<<std::endl;
   return playerName;
 }else{
   PlayerSignIn();
 }
}*/

//To make sure player enter uppercase name

void StartGame::playerMovement(Player* player,Board* board)
{
   std::string playerInput="";
   std::cout<<"< ";
   getline(std::cin,playerInput);
   int row=0;
   int col=0;
   std::stringstream ss;
   ss<<getInput(playerInput,13,playerInput.length());
   ss>>col;
   row=changeletterToInt(getInput(playerInput,12,13));
   std::string tilename=getInput(playerInput,6,8);
if(playerInput!="")
 {
  if(getInput(playerInput,0,5)=="PLACE"&&isTilesOnHand(player,getInput(playerInput,6,8))==1
  &&getInput(playerInput,9,11)=="AT"&&isInBoard(board,row,col)==1)
  {
         if(player->getTilesOnHand()->has(tilename))
         {
           Tile* tileToPlace = player->findTile(tilename);
           board->store(tileToPlace,row,col);
           player->removeTile(tilename);
           if (tileBag->size() > 0)
           {
             player->addTiles(tileBag->getNext()->getTile());
             //delete the withdrawn tile, which is always the head tile/node
             tileBag->deleteFront();
           }
         }
         else{
           std::cout<<"No these tile on your hand"<<std::endl;
          }
   }
   else if(getInput(playerInput,0,7)=="REPLACE")
   {
     replaceTileOnHand(player,getInput(playerInput,8,10));
   }
   else if(getInput(playerInput,0,4)=="SAVE")
   {
    std::string filename="";
    std::cout<<"Named your game"<<std::endl;
    getline(std::cin,filename);
    saveGame(filename,board,tileBag,player1,player2,currentPlayerName);
   }
   else if(getInput(playerInput,0,4)=="EXIT")
   {
     exit(0);
   }
  }
}

bool StartGame::isInBoard(Board* limitBoard,int row, int col)
{
  if(limitBoard->isWithinBound(row,col))
  {
    return true;
  }
  return false;

}
bool StartGame::isTilesOnHand(Player* player, std::string word)
{
  if(player->getTilesOnHand()->has(word))
  {
    return true;
  }
  return false;
}

bool StartGame::qwrikleRule(Tile* tile, int row, int col, std::vector<std::vector<Tile*>>tiles_on_board)
{
  std::vector<Tile*>
}
//replace function, it can  replace one tile in player's hand;
void StartGame::replaceTileOnHand(Player* player, std::string tilename)
{

    if(player->getTilesOnHand()->has(tilename))
    {
      player->getTilesOnHand()->remove(tilename);
      player->addTiles(tileBag->getNext()->getTile());
      tileBag->deleteFront();
    }
    else{
      std::cout<<"Can't find this tile"<<std::endl;
    }
}

void StartGame::showGameInfo(Player* player)
{
  std::cout<<player->getName()<<" is your turn."<<std::endl;
  std::cout<<player1->getName()<<":"<<std::endl;
  std::cout<<player2->getName()<<":"<<std::endl;
  std::cout <<std::endl;
  board->printBoard();
  std::cout <<std::endl;
  player->showTilesOnHand();
}

bool StartGame::isEmpty(Board* board)
{
  std::vector<std::vector<Tile*>> tiles=board->getTilesOnBoard();
  //initial board is 6x6
  for(int i=0; i<6; ++i)
  {
    for(int j=0; j<6; ++j)
    {
      if(tiles[i][j]!=nullptr)
      {
        return false;
      }
    }
  }
  return true;
}

bool StartGame::isSameColor(Tile* tile1,Tile* tile2)
{
   if(tile1->getColour()==tile2->getColour())
   {
     return true;
   }
   return false;
}

bool StartGame::isSameShape(Tile* tile1, Tile* tile2)
{
  if(tile1->getShape()==tile2->getShape())
  {
    return true;
  }
  return false;
}

void StartGame::saveGame(std::string saveName, Board* board, LinkedList* tilebag, Player* player1, Player* player2,std::string currentName)
{
  std::string filename = saveName + ".txt";

	std::ofstream saveGame;
  save.open(filename,std::ios::out);
  std::string fullboard=board->boardHeaderToString();
      fullBoard += board->boardBodyToString();
	saveGame << player1->getName()<<std::endl;

	saveGame << player1->getScore()<<std::endl;

	saveGame << player1->getTilesOnHand()->toString();

	saveGame << player2->getName()<<std::endl;

	saveGame << player2->getScore()<<std::endl;

	saveGame << player2->getTilesOnHand()->toString();

	saveGame <<fullboard<<std::endl;
	//saveGame << tilebag->toString();

	saveGame <<currentName<<std::endl;
	saveGame.close();
	std::cout << "Game saved successfully..." << std::endl;
  exit(0);
}

void StartGame::loadGame(std::string saveName)
{
  std::string filename = saveName + ".txt";

 std::ifstream loadGame (filename);
 //creates player with name

 std::string line;
 std::getline(loadGame, line);
 player* player1 (line);

 //updates players score
 std::getline(loadGame, line);
 player1->setScore(std::stoi(line));
 //adds tiles to players hand
 std::getline(loadGame, line);

 std::stringstream ss(line);

 std::string tile;

 while (std::getline(ss, tile, ','))

 {

   Tile* tile = new Tile(tile.substr(0,1), tile.substr(1,1));

   player1->getTilesOnHand()->add(tile);

 }

 //creates player with name
 std::getline(loadGame, line);
 Player* player2 (line);
 //updates players score

 std::getline(loadGame, line);
 player2->setScore(std::stoi(line));
 //adds tiles to players hand

 std::getline(loadGame, line);

 std::stringstream ss(line);

 while (std::getline(ss, tile, ','))

 {

   Tile* tile = new Tile(tile.substr(0,1), tile.substr(1,1));

   player2->getTilesOnHand()->add(tile);

 }

 //skip first two lines of board print

 std::getline(loadGame, line);

 std::getline(loadGame, line);
 int rowIndex = 0;

 std::vector<std::vector<Tile*>> board;

 do {

   std::getline(loadGame, line);

   for (int i = 2; i != line.length(); i++) {



     if (line.substr(i,1) == "|") {

       //if the next board position is empty, add nullptr to vector

       if (line.substr(i + 1,1) == "|") {

         board->at(rowIndex)->push_back(nullptr);

       }

     }

     else if (std::regex_match(line.substr(i,1), "[A-F]")) {

       Tile* tile = new Tile(line.substr(i,1), line.substr(i + 1,1));

       board->at(rowIndex)->push_back(tile);

     }

   }

   rowIndex++;

 }

 while (line.substr(0,1) != "-");
 //skip next line

 std::getline(loadGame, line);

 std::getline(loadGame, line);

 std::stringstream ss(line);

 std::string tile;
 //load tilebag

 LinkedList* tilebag = new LinkedList();

 while (std::getline(ss, tile, ','))

 {

   Tile* tile = new Tile(tile.substr(0,1), tile.substr(1,1));

   tilebag->add(tile);

 }
 //set current player

 std::getline(loadGame, line);

 Player* currPlayer;

 if (player1->getName == line) {

   currPlayer = player1;

 }

 else {
   currPlayer = player2;
 }

 startGame(board, tilebag, player1, player2, currPlayer);
}


void StartGame::startLoadGame(Board* board, Player* player1, Player* player2, LinkedList* tileBag,
 LinkedList* player1Hand, LinkedList* player2Hand)
  {

    while(!GameOver())
    {
      if(currentPlayerName==player1->getName())
      {
        showGameInfo(player1);
        playerMovement(player1,board);
        currentPlayerName=player2->getName();
      }else
      {
        showGameInfo(player2);
        playerMovement(player2,board);
        currentPlayerName=player1->getName();
      }
   }
  }


bool StartGame::IsVaildInput(std::string input)
{
  bool valid = true;

  if (input != ""){
    for (char c: input)
      if ((!isalpha(c) || !isupper(c)))
        valid = false;
  }
  else
    valid = false;

  return valid;
}
