#include "Player.h"

Player::Player(std::string name) : name(_name), points(0) {
}
std::string Player::getName() {
	return name;
}
int Player::getPoints() {
	return points;
}