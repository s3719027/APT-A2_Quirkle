#include <iostream>


bool saveGame(std::string saveName, Board* board, LinkedList* tilebag, Player* player1, Player* player2, Player* currPlayer) {
	
	std::string filename = saveName + ".txt"; 
	std::ofstream saveGame (filename);
	
	saveGame << player1->getName();
	saveGame << player1->getScore();
	saveGame << player1->getTilesOnHand()->toString();
	saveGame << player2->getName();
	saveGame << player2->getScore();
	saveGame << player2->getTilesOnHand()->toString();
	
	saveGame << board->toString();
	saveGame << tilebag->toString();
	saveGame << currPlayer->getName();
	
	saveGame.close();
	std::cout << "Game saved successfully..." << std::endl;
}