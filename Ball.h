#ifndef BALL_H
#define BALL_H

#include "Point.h"

class Ball	{
	Point position;
	int radius;
	double xUnit;
	double yUnit;
	Point destination;

public:
	Ball();	
	Point getPosition();
	void setPosition(Point Point);
	Point getDestination();
	void setDestination(Point point);
	void setXMovement(double x);
	void setYMovement(double y);
	double getXMovement();
	double getYMovement();
	void display();
};

#endif