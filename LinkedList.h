
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   
   void addBack(Node* node);
   void addFront(Node* node);
   void deleteFront();
   void deleteTile(Tile* tile);
   bool findTile(Tile* tile);
   Node* getHead();

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
