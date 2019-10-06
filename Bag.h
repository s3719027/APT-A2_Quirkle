#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H
#include "LinkedList.h"
#include "Tile.h"
#include "Node.h"
class Bag{
public:
	Bag();
	Bag(bool empty);
	LinkedList* getBag();
private:
	LinkedList* bag;

};
#endif
