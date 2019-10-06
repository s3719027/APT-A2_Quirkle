#include "Tile.h"

Tile::Tile() {
	this->colour = ' ';
	this->shape = ' '; 
}

Tile::Tile(Colour _colour, Shape _shape) {
	this->colour = _colour;
	this->shape = _shape;
}

Tile::~Tile() {
}

char Tile::getColour() {
	return this->colour;
}

int Tile::getShape() {
	return this->shape;
}

bool Tile::checkSimilar( Tile *tile ) {
	if ( this->colour == tile->colour && this->shape == tile->shape ) {
		return true;
	}
	return false;
}

bool Tile::checkEmpty() {
	if ( this->colour == ' ' || this->shape == ' ' ) {
		return true;
	}
	return false;
}
