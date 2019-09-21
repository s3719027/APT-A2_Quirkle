
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
   void deleteTIle(Tile* tile);
   bool findTile(Node* node);
   Node* getHead();

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
