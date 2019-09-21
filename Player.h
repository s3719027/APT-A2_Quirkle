#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

class Player {
public:
	Player(std::string _name);
	std::string getName();
	int getPoints();
	
private:
	std::string name;
	int points;
};

#endif // ASSIGN2_PLAYER_H