#include <iostream>
#include <string>
#include <fstream>
#include <regex>

void loadGame(std::string saveName) {
	
	std::string filename = saveName + ".txt";
	std::ifstream loadGame (filename);
	
	//creates player with name
	std::string line;
	std::getline(loadGame, line);
	Player* player1 (line);
	
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
	std::vector<std::vector<Tile*>*>* board;
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