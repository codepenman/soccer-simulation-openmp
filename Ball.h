#ifndef BALL_H
#define BALL_H

#include "Point.h"

class Ball	{
	Point position;
	//define radius of the ball

public:
	Ball();	
	Point getPosition();
	void setPosition(Point Point);
};

#endif