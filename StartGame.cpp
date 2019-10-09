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
      giveScore(player1);
      currentPlayerName=player2->getName();
    }else
    {
      showGameInfo(player2);
      playerMovement(player2,board);
      giveScore(player2);
      currentPlayerName=player1->getName();
    }
 }

}


void StartGame::PlayerSignIn()
{
  std::string playerName1="";
  std::string playerName2="";
  std::cout<<"Enter a name for player1 (uppercase characters only)"<<std::endl;
  std::cin>>playerName1;

  std::cout<<"Enter a name for player1 (uppercase characters only)"<<std::endl;
  std::cin>>playerName2;
  player2=new Player(playerName2);
  if(vaildInput(playerName1))
  {
    player1=new Player(playerName1);
  }
  if(vaildInput(playerName2))
  {
    player2=new Player(playerName2);
    std::cout<<"Let's play!"<<std::endl;
  }
  else{
   PlayerSignIn();
 }
}

//To make sure player enter uppercase name

void StartGame::playerMovement(Player* player,Board* board)
{
   std::string playerInput="";
   std::cout<<"< ";
   getline(std::cin,playerInput);
   transform(playerInput.begin(),playerInput.end(),playerInput.begin(), ::toupper);
   int row=0;
   int col=0;
   std::stringstream ss;
   ss<<getInput(playerInput,13,playerInput.length());
   ss>>col;
   row=changeletterToInt(getInput(playerInput,12,13));
   std::string tilename=getInput(playerInput,6,8);
   Tile* tileToPlace = player->findTile(tilename);
if(playerInput!="")
 {
  if(getInput(playerInput,0,5)=="PLACE"&&isTilesOnHand(player,getInput(playerInput,6,8))==1
  &&getInput(playerInput,9,11)=="AT"&&isInBoard(board,row,col)==1)
  {
    if(qwrikleRule(tileToPlace,row,col,board)==true)
    {
         if(player->getTilesOnHand()->has(tilename))
         {
           calculatePlayerScores(board,row,col);
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
  if(row<limitBoard->getRows()&&col<limitBoard->getCols())
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

bool StartGame::qwrikleRule(Tile* tile, int row, int col, Board* board)
{
//  bool vaild=false;
  bool colorIssue=true;
  bool shapeIssue=true;
  bool canPlace=false;
  int leftSide=col-1;
  int rightSide=col+1;
  int upSide=row-1;
  int lowerSide=row+1;
  std::vector<std::vector<Tile*>> v=board->getTilesOnBoard();
  std::vector<Tile*>toRight;//it is the direction of the tile placed
  std::vector<Tile*>toLeft;
  std::vector<Tile*>toUp;
  std::vector<Tile*>toLow;
  //to make sure these are tiles around the last tile
  //            t2
  //          tile1
  // Because the rule of qwirkle ask player to place the tile around the last tile;
  std::vector<Tile*> horizontalTiles;
  std::vector<Tile*> verticalTiles;

  if(isEmpty(board)==true)
  {
    //firstTile can place anywhere
    isFirstTile=true;
    canPlace=true;
  }else{
    isFirstTile=false;
  }
  //get the tile around the destination, if have tile around the destination, it means
  //player can place tile here;

  //it is single direction; up-low-right-left;
if(isFirstTile==false)
{
  while(leftSide>=0&&v[row][leftSide]!=nullptr)
  {
    //same horizontal must place same color tiles;
    if(isSameColor(tile,v[row][leftSide])&&!isSameShape(tile,v[row][leftSide]))
    {
      toRight.push_back(v[row][leftSide]);
      leftSide-=1;
      canPlace=true;
      //colorIssue=true;
    }else{
     canPlace=false;
     colorIssue=false;
    }

  }
  while(rightSide<board->getCols()&&v[row][rightSide]!=nullptr)
  {
    //same horizontal must place same color tiles;
    if(isSameColor(tile,v[row][rightSide])&&!isSameShape(tile,v[row][rightSide]))
    {
      toLeft.push_back(v[row][leftSide]);
      rightSide+=1;
      canPlace=true;
    //  colorIssue=true;
    }else{
      colorIssue=false;
      canPlace=false;
    }
  }
  while(upSide>=0&&v[upSide][col]!=nullptr)
  {
     if(isSameShape(tile,v[upSide][col])&&!isSameColor(tile,v[upSide][col]))
     {
       toLow.push_back(v[upSide][col]);
       upSide-=1;
       canPlace=true;
      // shapeIssue=true;
     }else{
       shapeIssue=false;
       canPlace=false;
     }
  }
  while(lowerSide<board->getRows()&&v[lowerSide][col]!=nullptr)
  {
    if(isSameShape(tile,v[lowerSide][col])&&!isSameColor(tile,v[lowerSide][col]))
    {
      toUp.push_back(v[lowerSide][col]);
      lowerSide+=1;
      canPlace=true;
      //shapeIssue=true;
    }else{
      shapeIssue=false;
      canPlace=false;
    }
  }
  // two direction

  if(colorIssue==false)
  {
   std::cout<<"You can't place here, you must to place the same color tile"<<std::endl;
 }else if(shapeIssue==false)
  {
   std::cout<<"You can't place here, you must to place the same shape tile"<<std::endl;
  }

  return canPlace;
}
 return canPlace;

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
  std::cout<<player1->getName()<<":"<<player1->getScore()<<std::endl;
  std::cout<<player2->getName()<<":"<<player2->getScore()<<std::endl;
  std::cout <<std::endl;
  board->printBoard();
  std::cout <<std::endl;
  player->showTilesOnHand();
  std::cout<<std::endl;
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

void StartGame::giveScore(Player* player)
{
  if(qwirkle)
  {
    score+=6;
  }
  player->addScore(score);
  score=0;
  qwirkle=false;
}
//Because the place where player want to place tile is empty, if we want to count the tiles,
//we have to start from the last tile;
void StartGame::calculatePlayerScores(Board* board, int row, int col)
{
  std::vector<std::vector<Tile*>> v=board->getTilesOnBoard();
  if(col>=0&&v[row][col-1]!=nullptr)
  {
    this->score+=countTilesInBoard(board,row,col,"Left");
  }
  if(col<board->getCols()&&v[row][col+1]!=nullptr)
  {
    this->score+=countTilesInBoard(board,row,col+1,"Right");
  }
  if(row>=0&&v[row-1][col]!=nullptr)
  {
    this->score+=countTilesInBoard(board,row-1,col,"Up");
  }
  if(row<board->getRows()&&v[row+1][col]!=nullptr)
  {
    this->score+=countTilesInBoard(board,row+1,col,"Low");
  }
}


int StartGame::countTilesInBoard(Board* board, int row, int col,std::string direction)
{
  int numberOfTiles=0;
  std::vector<std::vector<Tile*>> v=board->getTilesOnBoard();
  if(direction=="Right")
  {
    while(col<board->getCols()&&v[row][col]!=nullptr)
    {
      numberOfTiles+=1;
      col+=1;
    }
  }
  else if(direction=="Left")
  {
    while(col>=0&&v[row][col]!=nullptr)
    {
      numberOfTiles+=1;
      col-=1;
    }
  }
  else if(direction=="Up")
  {
    while(row>=0&&v[row][col]!=nullptr)
    {
      numberOfTiles+=1;
      row-=1;
    }
  }
  else if(direction=="Low")
  {
    while(row<board->getRows()&&v[row][col]!=nullptr)
    {
      numberOfTiles+=1;
      row+=1;
    }
  }
  //the last tile placed into the list cannot be counted
  //R1 R2 R3 R4 R5 R6
  //0  1  2  3  4   5
  //this function calculate the last in each tileList;
  if(numberOfTiles==5)
  {
     this->qwirkle=true;
     std::cout<<"Qwirkle!"<<std::endl;
  }
    return numberOfTiles;
}

void StartGame::saveGame(std::string saveName, Board* board, LinkedList* tilebag, Player* player1, Player* player2,std::string currentName)
{
  std::string filename = saveName + ".txt";

	std::ofstream saveGame;

  saveGame.open(filename,std::ios::out);

  std::string fullboard=board->boardHeaderToString();
      fullboard += board->boardBodyToString();

Node* current=player1->getTilesOnHand()->getHead();

	saveGame << player1->getName()<<std::endl;

	saveGame << player1->getScore()<<std::endl;

  while(current!=nullptr)
  {
    if(cuurent->next!=nullptr)
      saveGame<<cuurent->getTile()->toString()<<",";
    else
      saveGame<<current->getTile()->toString()<<std::endl;
    current=current->next;
  }

	saveGame << player2->getName()<<std::endl;

	saveGame << player2->getScore()<<std::endl;

	current=player2->getTilesOnHand()->getHead();

  while(current!=nullptr)
  {
    if(current->next!=nullptr)
      saveGame<<cuurent->getTile()->toString()<<",";
    else
      saveGame<<current->getTile()->toString()<<std::endl;
    current=current->next;
  }

	saveGame <<fullboard<<std::endl;

  Node* bagNode=tileBag->getHead();
   while(bagNode!=nullptr)
   {
     if(bagNode->next!=nullptr)
        saveGame<<bagNode->getTile()->toString()<<",";
     else
        saveGame<<bagNode->getTile()->toString()<<std::endl;
     bagNode=bagNode->next;
   }

	saveGame <<currentName<<std::endl;
	saveGame.close();
	std::cout << "Game saved successfully..." << std::endl;
  exit(0);
}

void StartGame::loadGame(std::string saveName)
{
  std::string filename = saveName + ".txt";
  std::string tile;
 std::ifstream loadGame;
 loadGame.open(filename,std::ios::in);
 //creates player with name

 std::string line;
 std::getline(loadGame, line);
 Player* player1 = new Player(line);

 //updates players score
 //the end of getline is /n
 std::getline(loadGame, line);
 int player1Score=0;
 std::stringstream ss;
 ss<<line;
 ss>>player1Score;
 player1->setScore(player1Score);
 //adds tiles to players hand
 std::getline(loadGame, line);


 std::stringstream ss(line);
 while (std::getline(ss, tile, ','))

 {

   Tile* tile = new Tile(tile.substr(0,1), tile.substr(1,1));

   player1->getTilesOnHand()->add(tile);

 }

 //creates player with name
 std::getline(loadGame, line);
 Player* player2 = new Player(line);
 //updates players score
  int player2Score=0;
 std::getline(loadGame, line);
 ss<<line;
 ss>>player2Score;
 player2->setScore(player2Score);
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

    for (int i = 2; i != line.length() - 1; i++) {

      if (line.substr(i,1) == "|") {
        
        //if the next board position is empty, add nullptr to vector
        if (line.substr(i,1) == "|") {

          board.at(rowIndex).push_back(nullptr);

        }
      }

      else if (std::regex_match(line.substr(i,1), pattern)) {

        Tile* tile = new Tile(line.substr(i,1), line.substr(i + 1,1));
        board.at(rowIndex).push_back(tile);
      }
    }
    rowIndex++;
  }
  while (line.substr(line.length() - 1,1) != "-");
  
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

 currentPlayerName=line;

 SetUpGame();
}


bool StartGame::vaildInput(std::string input)
{
  if(input=="")
  {
    for(char c:input)
    {
      if((!isupper(c)||!isalpha(c))
      {
        return false;
      }
    }
  }else{
    return false;
  }
  return true;
}
