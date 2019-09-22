
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:
   Node(Tile* tile, Node* _next);
   Node(Node& other);
   void setNext(Node* _next);
   Node* getNext();
   Tile* getTile();
   
private:
   Tile*    tile;
   Node*    next;
};

#endif // ASSIGN2_NODE_H
