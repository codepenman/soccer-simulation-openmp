#include "iostream"
#include "Ball.h"
using namespace std;

Ball::Ball()	{
}

Point Ball::getPosition()	{
	return position;
}

void Ball::setPosition(Point position)	{
	this->position.x = position.x;
	this->position.y = position.y;
}

Point Ball::getDestination() {
	return destination;
}

void Ball::setDestination(Point destination) {
	this->destination.x = destination.x;
	this->destination.y = destination.y;
}

void Ball::setXMovement(double x) {
	this->xUnit = x;
}

void Ball::setYMovement(double y) {
	this->yUnit = y;
}

double Ball::getXMovement() {
	return this->xUnit;
}

double Ball::getYMovement() {
	return this->yUnit;
}

void Ball::display() {
	cout<<"Ball { Position: ("<<this->position.x<<","<<this->position.y<<"), "
		<<" Destination: ("<<this->destination.x<<","<<this->destination.y<<"), "
		<<"Movement Vector: ("<<this->xUnit<<","<<this->yUnit<<")}"<<endl;
}