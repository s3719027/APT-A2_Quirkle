
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   
   void addNode(*Node node);
   bool findTile(*Node node);

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
