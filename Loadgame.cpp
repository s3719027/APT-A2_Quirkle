#include "Board.h"
#include <iostream>

void Board::save(string command, Bag* bag, Player* playerA, Player* playerB) {
	string filename = command.substr(5);
	ofstream ofile(filename);
	if (!ofile.fail()) {
		ofile << playerA->getName() << "\n";
		ofile << playerA->getScore() << "\n";
		ofile << playerA->getHandtiles()->toString();
		ofile << playerB->getName() << "\n";
		ofile << playerB->getScore() << "\n";
		ofile << playerB->getHandtiles()->toString();
		ofile << toString();
		ofile << bag->getBag()->toString();
		ofile << currentPlayer->getName();
	}
	ofile.close();
}