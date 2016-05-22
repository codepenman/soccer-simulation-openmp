#include <iostream>
#include "stdlib.h"
#include "Player.h"
#include "Ball.h"
#include "math.h"
using namespace std;

Player::Player()	{
	this->playerId = -1;
	this->currPosition.x = -1;
	this->currPosition.y = -1;
	this->zone_radius = 0;
	nearToBall = false;
	isMotionDefined = false;
}

Player::Player(int playerId, Point currPosition, int zone_radius, int run_radius)	{
	this->playerId = playerId;
	this->currPosition.x = currPosition.x;
	this->currPosition.y = currPosition.y;
	this->zone_center.x = currPosition.x;
	this->zone_center.y = currPosition.y;
	this->zone_radius = zone_radius;
	this->run_radius = run_radius;	
	nearToBall = false;
	isMotionDefined = false;
}

int Player::getPlayerId()	{
	return playerId;
}

Point Player::getCurrentPosition()	{
	return currPosition;
}

void Player::setCurrentPosition(Point currPosition)	{
	this->currPosition.x = currPosition.x;
	this->currPosition.y = currPosition.y;
}

Point Player::getZoneCenter()	{
	return this->zone_center;
}

void Player::setNearToBall(bool nearToBall)	{
	this->nearToBall = nearToBall;
}

bool Player::isNearToBall()	{
	return this->nearToBall;
}

int Player::getZoneRadius()	{
	return this->zone_radius;
}

int Player::getRunRadius()	{
	return this->run_radius;
}

void Player::hitBall(Ball *ball, Point destination, int unitForce) {
	Point ballPosition = (*ball).getPosition();
	double distance = sqrt( pow((destination.x - ballPosition.x), 2) 
		+ pow((destination.y - ballPosition.y), 2));
	double time = distance / unitForce;
	double xUnit = (destination.x - ballPosition.x) / time;
	double yUnit = (destination.y - ballPosition.y) / time;

	(*ball).setXMovement(xUnit);
	(*ball).setYMovement(yUnit);
	(*ball).setDestination(destination);
}

void Player::movePlayer()	{

	if(!this->isMotionDefined)	{
		double radius = rand() % this->zone_radius; //between 0 and the radius of the circle
		double angle = rand() % 360; // between 0 and 360 (degrees)

		double x = this->zone_center.x + radius*cos(angle);
		double y = this->zone_center.y + radius*sin(angle); 		
		
		double distance = sqrt( pow((x - this->currPosition.x), 2) 
			+ pow((y - this->currPosition.y), 2));

		double time = distance / this->run_radius;
		this->xUnit = (x - currPosition.x) / time;
		this->yUnit = (y - currPosition.y) / time;

		this->isMotionDefined = true;
	}

	//if destination is not set then, set a random destination and calculate xUnit and yUnit	
	//if player has reached destination && not on circle
		//then update destination to new random number with in the zone and calculate xUnit and yUnit
	double distance = sqrt( pow((this->zone_center.x - this->currPosition.x), 2) 
		+ pow((this->zone_center.y - this->currPosition.y), 2));

	if(distance < this->zone_radius)	{
		Point p;
		p.x = this->currPosition.x + this->xUnit;
		p.y = this->currPosition.y + this->yUnit;

		setCurrentPosition(p);
		return;
	}

	Point p;
	p.x = this->currPosition.x - this->xUnit;
	p.y = this->currPosition.y - this->yUnit;

	setCurrentPosition(p);
}

void Player::display() {
	cout<<"Player: { id="<<this->playerId<<", position=("
		<<this->currPosition.x<<","<<this->currPosition.y<<"), nearToBall="<<this->nearToBall<<"}"<<endl;
}