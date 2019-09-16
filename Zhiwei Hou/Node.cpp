
#include "Node.h"

Node::Node(Tile* tile, Node* next)
{
   this->title=title;
   this->next=next;
}

Node::Node(Node& other)
{
   // TODO
}
Tile* Node::getTile()
{
  return tile;
}
