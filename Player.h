#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"
#include "Ball.h"

class Player	{
	int playerId;
	Point currPosition;
	Point zone_center; // This will be the initial Position of player
	int run_radius; //distance of a player for one step
	int zone_radius; // zone radius
	bool nearToBall;
	bool isMotionDefined;
	
	double xUnit;
	double yUnit;
	//radius of the player for display

public:
	Player();
	Player(int playerId, Point currPosition, int zone_radius, int run_radius);
	int getPlayerId();
	Point getCurrentPosition();
	Point getZoneCenter();
	void setCurrentPosition(Point point);
	void setNearToBall(bool nearToBall);
	bool isNearToBall();
	int getZoneRadius();
	int getRunRadius();
	void hitBall(Ball *ball, Point destination, int unitForce);
	void movePlayer();
	void display();
};
#endif
