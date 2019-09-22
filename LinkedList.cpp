#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr){
}

LinkedList::~LinkedList() {
}

void LinkedList::addBack(Node* node) {
   if (head == nullptr) {
      head = node;
   }
   else {
      std::cout << "here1";
      Node* tempNode = head;
      while (tempNode->getNext() != nullptr) {
         tempNode = tempNode->getNext();
      }
      tempNode->setNext(node);
   }
}
void LinkedList::addFront(Node* node) {
   node->setNext(head);
   head = node;
}
void LinkedList::deleteFront() {
   Node* node = head;
   head = head->getNext();
   delete node;
}
void LinkedList::deleteTile(Tile* tile) {
   bool removed = false;
   Node* node = head;
   
   //check if head value matches tile
   if (node->getTile()->getColour() == tile->getColour() && node->getTile()->getShape() == tile->getShape()) {
      deleteFront();
      removed = true;
   }
   while (!removed) {
      if (node->getNext() != nullptr) {
         if (node->getNext()->getTile()->getColour() == tile->getColour() && node->getNext()->getTile()->getShape() == tile->getShape()) {
            Node* toDelete = node->getNext();
            node->setNext(node->getNext()->getNext());
            delete toDelete;
         }
      }
      else {
         node = node->getNext();
      }
   }
}
bool LinkedList::findTile(Tile* tile) {
   if (head != nullptr) {   
      Node* tempNode = head;
      do {
         if (tempNode->getTile()->getColour() == tile->getColour() && tempNode->getTile()->getShape() == tile->getShape()) {
                  return true;
               }
         if (tempNode->getNext() != nullptr) {
            tempNode = tempNode->getNext();
         }
      }
      while (tempNode->getNext() != nullptr);
   }
   return false;
}
Node* LinkedList::getHead() {
   return head;
}