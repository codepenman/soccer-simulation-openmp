#include "iostream"
#include "Ball.h"
using namespace std;

Ball::Ball(Point position)	{
	this->position.x = position.x;
	this->position.y = position.y;
}

Point Ball::getPosition()	{
	return position;
}

void Ball::setPosition(Point position)	{
	this->position.x = position.x;
	this->position.y = position.y;
}
