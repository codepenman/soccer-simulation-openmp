#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"
#include "Ball.h"

class Player	{
	int playerId;
	Point position;
	int run_radius; // movement radius
	bool nearToBall;
	//radius of the player for display

public:
	Player();
	Player(int playerId, Point position, int run_radius);
	int getPlayerId();
	Point getPosition();
	void setPosition(Point point);
	void setNearToBall(bool nearToBall);
	bool isNearToBall();
	int getRunRadius();
	void hitBall(Ball *ball, Point destination, int unitForce);
	void display();
};
#endif
