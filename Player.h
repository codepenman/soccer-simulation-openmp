#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"

class Player	{
	int playerId;
	Point position;
	int run_radius; // movement radius
	//radius of the player for display

public:
	Player();
	Player(int playerId, Point position, int run_radius);
	int getPlayerId();
	Point getPosition();
	void setPosition(Point point);
};

#endif
