#include "Tile.h"

Tile::Tile(Colour _colour, Shape _shape) {
	colour = _colour;
	shape = _shape;
}
Tile::~Tile() {
}
char Tile::getColour() {
	return this->colour;
}
int Tile::getShape() {
	return this->shape;
}