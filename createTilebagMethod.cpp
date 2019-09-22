#include <vector>
#include <random>
#include <iostream>
#include "TileCodes.h"
#include "LinkedList.h"


#define NUMCOLOURS 6
#define NUMSHAPES 6

LinkedList* createTileBag();

LinkedList* createTileBag() {
	
	LinkedList* orderedBag = new LinkedList();
		
	char colours[NUMCOLOURS] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
	int shapes[NUMSHAPES] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
	
	for (int i = 0; i != NUMCOLOURS; i++) {
		for (int j = 0; j != NUMSHAPES; j++) {
			for (int k = 0; k != 4; k++) {
				Tile* tile = new Tile(colours[i], shapes[j]);
				Node* node = new Node(tile, nullptr);
				orderedBag->addBack(node);
			}
		}
	}
	//shuffleBag
	LinkedList* shuffledBag = new LinkedList();
	std::vector<Node*> nodes;
	Node* node = orderedBag->getHead();	
	
	while (node->getNext() != nullptr) {
		nodes.push_back(node);
		node = node->getNext();
	}
	std::srand (std::time(0));
	std::random_shuffle(nodes.begin(), nodes.end());
	
	for (int i = 0; i != nodes.size(); i++) {
		shuffledBag->addBack(nodes.at(i));
	}
	return shuffledBag;
}