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

void StartGame::BasicSetting()
{
  Bag* bag=new Bag();
  tileBag=bag->getBag();
  board=new Board(6,6);
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
 if(GameOver())
 {
   showResult();
 }

}


void StartGame::PlayerSignIn()
{
  std::string playerName1="";
  std::string playerName2="";
  std::cout<<"Enter a name for player1 (uppercase characters only)"<<std::endl;
  std::cin>>playerName1;

  std::cout<<"Enter a name for player2 (uppercase characters only)"<<std::endl;
  std::cin>>playerName2;
  if(vaildInput(playerName1)==true&&vaildInput(playerName2)==true)
  {
    player1=new Player(playerName1);
    player2=new Player(playerName2);
    std::cout<<"Let's play!"<<std::endl;
  }
   else{
   PlayerSignIn();
 }
  currentPlayerName=player1->getName();
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
           board->store(tileToPlace,row,col);
           calculatePlayerScores(board,row,col);
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
    }else if(qwrikleRule(tileToPlace,row,col,board)==false){
      std::cout<<"You put invaild place"<<std::endl;
      playerMovement(player,board);
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
     showResult();
     exit(0);

   }
  }
}

bool StartGame::isInBoard(Board* limitBoard,int row, int col)
{
  if(row>=0&&col>=0&&row<limitBoard->getRows()&&col<limitBoard->getCols()&&row<26&&col<26)
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
      canPlace=false;
    }
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
  if(qwirkle==true)
  {
    score+=6;
    std::cout<<"Qwirkle!"<<std::endl;

  }
  player->addScore(score);
  qwirkle=false;
  score=0;
}
//Because the place where player want to place tile is empty, if we want to count the tiles,
//we have to start from the last tile;
void StartGame::calculatePlayerScores(Board* board, int row, int col)
{
  std::vector<std::vector<Tile*>> v=board->getTilesOnBoard();
  if(isFirstTile!=true)
  {
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
    if(current->next!=nullptr)
      saveGame<<current->getTile()->toString()<<",";
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
      saveGame<<current->getTile()->toString()<<",";
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

void StartGame::showResult(){
  board->printBoard();
  std::cout<<std::endl;
  std::cout<< "GAME OVER" <<std::endl;
  std::cout<< "Score for " << player1->getName() << ": " << player1->getScore() <<std::endl;
  std::cout<< "Score for " << player2->getName() << ": " << player2->getScore() <<std::endl;

  if (player1->getScore() > player2->getScore())
    std::cout<< "Player " << player1->getName() << " won " <<std::endl;
  else if (player1->getScore() < player2->getScore())
    std::cout<< "Player " << player2->getName() << " won " <<std::endl;
  else
    std::cout << " No winner " << std::endl;
}

void StartGame::loadGame()
{
  std::string allTiles;
  std::cout<<"Enter filename"<<std::endl;
  std::string filename="";
  std::getline(std::cin,filename);
  filename=filename+".txt";
    std::ifstream loadGame;
    loadGame.open(filename,std::ios::in);
   //creates player with name

   std::string line;

   //player1 name
   std::getline(loadGame, line);
   std::string player1name=line;
   player1=new Player(player1name);
   std::cout<<player1->getName()<<std::endl;
   //player1 scores
   std::getline(loadGame,line);
   int player1Score=line[0]-'0';
   player1->setScore(player1Score);
   std::cout<<player1->getScore()<<std::endl;

   //player1 tiles
   std::getline(loadGame,line);
   std::string player1Tiles=line;

   int acolor=0;//for color
   int ashape=1;//for shape
   //adds tiles to players hand
  //run 6 times, can get r1, r2, r3, r4, r5, r6
  for(int i=0; i<6; ++i)
  {
    char color=player1Tiles[acolor];
    //Because the ',' is place at the 0, 3, 6, 9, 12, 15
    int shape=player1Tiles[ashape]-'0';
    Tile* tile=new Tile(color,shape);
    //std::cout<<tile->toString()<<std::endl;
    player1->addTiles(tile);
    acolor+=3;
    ashape+=3;
  }
   player1->showTilesOnHand();

   //player2 name
   std::getline(loadGame,line);
   std::string player2name=line;
   player2=new Player(player2name);
   std::cout<<player2->getName()<<std::endl;

   //player2 scores
   std::getline(loadGame,line);
   int player2Score=line[0]-'0';
    player2->setScore(player2Score);
    std::cout<<player2->getScore()<<std::endl;

   //player2 tiles
   std::getline(loadGame,line);
   std::string player2Tiles=line;

   //get player2 hand tiles
   int bcolor=0;
   int bshape=1;
   for(int i=0; i<6; ++i)
   {
     char color=player2Tiles[bcolor];
     //Because the ',' is place at the 0, 3, 6, 9, 12, 15
     int shape=player2Tiles[bshape]-'0';
     Tile* tile=new Tile(color,shape);
     //std::cout<<tile->toString()<<std::endl;
     player2->addTiles(tile);
     bcolor+=3;
     bshape+=3;
   }
    player2->showTilesOnHand();

  std::getline(loadGame,line);
  std::string boardL=line;
  //it is first row,
  //the rows= boardR.length()/3-1

  // std::getline(loadGame,line,".");
  // std::string boardl=line;
  getline(loadGame, line);
  boardL = line + "\n";
  getline(loadGame, line);
  boardL += line + "\n";

  // used to split board and tilebag
  while(line[2] != ',') {
    getline(loadGame, line);
    if(line[2] != ','){
      boardL += line + "\n";
    }else{
        allTiles=line;
    }
  }
   //put the board from the second row "-----"into a string array
   //

   //TileBag

   int length12=0;
   int aazz=boardL.length();

   for(int i=0; i<aazz;++i)
    {
      if(boardL[i+2]=='A')
       {
         length12=i;
       }
     }
     //length/2 = the number of sapce in each row,then -header of board
   int boardRows=aazz%(length12/2)-2;
   int boardCols=length12/6-1;
    // use mathematic way to get the column and rows of board
   board = new Board(boardRows, boardCols);

    // use mathematic way to get tiles in board and the position of tiles
    for (int i= 1; i < aazz; i++) {
      if (boardL[i] == '|' && boardL[i-1] != ' ') {
       char color = boardL[i - 2];
       int shape = boardL[i-1]-'0';
        int tileCol = ((i - 2) % (3 * boardCols + 5)) / 3 - 1;
        int tileRow = ((i - 2) % (3 * boardCols + 5)) - 2;

        // place tiles
        board->store(new Tile(color, shape), tileRow, tileCol);
      }
    }

    int lengthTileBag=allTiles.length();
    int ccolor=0;
    int cshape=1;
    for(int i=0; i<(lengthTileBag+1)/3;++i)
    {
      char color=allTiles[ccolor];
      int shape=allTiles[cshape]-'0';
      Tile* tile=new Tile(color,shape);
      tileBag->add(tile);
      ccolor+=3;
      cshape+=3;
    }
     tileBag->show();

   //currentPlayer's name;
   std::getline(loadGame,line);
   std::string cname=line;
   currentPlayerName=cname;


  //for tilebag

   //if rows=6, boardR.length()=21;
   /*int aaa=boardR.length();
   int bbb=boardl.length();
   int rows=aaa/3-1;
   //the rows of the board;
   int cols=(bbb+aaa-rows)/21-2;
   // i try to used mathematic way to solve this question
   // if rows=6, board=153, cols=(153+21-6)/21-2=6;
   board=new Board(rows,cols);
   //dcol and dshape are for tiles on the board
   int dcolor=boardR.length()+4;//from 0
   int dshape=boardR.length()+5;
   int rowLength=boardR.length()+1;
   int startPlace=boardR.length()+4;
   for(int i=0; i<board.length()/3; ++i)
   {
     if(board[dcol]-1!="|"&&board[dshape]+1!=" ")
     {
       char color=boardl[dcolor];
       int shape=boardl[dshape]-'0';
       Tile* tile=new Tile(color,shape);
       realRow=dcolor/rowLength-1;
       realCol=(dcolor-startPlace)/3;
       board->store(tile,realRow,realCol);
       dcolor+=3;
       dshape+=3;
     }
   }*/
   SetUpGame();

}


bool StartGame::vaildInput(std::string input)
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
