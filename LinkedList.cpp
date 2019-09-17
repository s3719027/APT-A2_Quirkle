
#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr){
   
}

LinkedList::~LinkedList() {
}

void LinkedList::addNode(*Node node) {
   if (head == nullptr) {
      head = node;
   }
   else {
      Node* tempNode = head;
      while (tempNode.getNext() != nullptr) {
         tempNode = tempNode.getNext();
      }
      tempNode.setNext(node);
   }
}
bool LinkedList::findTile(*Node node) {
   if (head != nullptr) {
      Node* tempNode = head;
      do {
         if (tempNode.getTile().getColour() == node.getTile().getColour() && tempNode.getTile().getShape() == node.getTile().getShape()) {
                  return true;
               }
         if (tempNode.getNext() != nullptr) {
            tempNode = tempNode.getNext();
         }
      }
      while (tempNode.getNext() != nullptr)
   }
}