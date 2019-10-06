#include <iostream>
#include <regex>

void startGame(Board* board, LinkedList* tilebag, Player* player1, Player* player2) {
	
	//state whos turn it is
	//print scores
	//print board
	//print hand
	//input until move is correct
	//add tile to players hand
	//swap player
	
	//reloop until tilebag empty or no tiles
	
	Player* currentPlayer = player1;
	std::string command = "";
	
	while (currentPlayer->getTilesOnHand()->size() != 0) {
		
		std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
		std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
		std::cout << board->printBoard() << std::endl;
		std::cout << currentPlayer->showTilesOnHand() << std::endl;
		
		bool validInput = false;
		while (!validInput) {
			std::cout << "> ";
			std::cin >> command;
			
			//splits command into vector array
			std::vector<std::string> commandParts;
			std::istringstream iss(command);
			for(std::string command; iss >> command; )
				commandParts.push_back(command);
				
			if (commandParts[0] == "place") {
				//validates the input is a possible tile
				if (std::regex_match(commandParts[1], "[A-G][1-6]")) {
					if (commandParts[2] == "at") {
						//validates the input is a possible position
						if (std::regex_match(commandParts[1], "[A-Z][0-25]")) {
							//checks if player has the tile
							if (currentPlayer->getTilesOnHand()->has(commandParts[1])) {
								//tries to place tile
								if (board->store(currentPlayer->findTile(commandParts[1]), commandParts[3].substr(0,1), commandParts[3].substr(1,2))) {
									
									//remove tile from hand
									currentPlayer->removeTile(commandParts[1]);
									
									//give player new tile
									currentPlayer->addTile(tilebag->getHead());
									
									//remove tile just taken from tilebag
									tilebag->deleteFront();
									validInput = true;
								}
							}
						}
					}
				}
			}
			else if (commandParts[0] == "replace") {
				if (std::regex_match(commandParts[1], "[A-G][1-6]")) {
					if (currentPlayer->getTilesOnHand()->has(commandParts[1])) {
						
						//add tile to tilebag
						tilebag->add(currentPlayer->findNode(commandParts[1])->getTile());
						
						//delete node from hand
						currentPlayer->getTilesOnHand()->remove(commandParts[1]);
						
						//add head to hand
						currentPlayer->addTile(tilebag->getHead()->getTile())
						
						//delete head of tilebag	
						tilebag->deleteFront();
									
						validInput = true;
					}
				}
			}
			else if (commandParts[0] == "save") {
				if (commandParts[1] != nullptr) {
					validInput = true;
				}
			}
			else {
				std::cout << "Invalid command..." << std::endl;
			}
		}	
	} 
}