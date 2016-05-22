#include <iostream>
#include "Player.h"
#include "Ball.h"
#include "math.h"
using namespace std;

Player::Player()	{
	this->playerId = -1;
	this->position.x = -1;
	this->position.y = -1;
	this->run_radius = 0;
	nearToBall = false;
}

Player::Player(int playerId, Point position, int run_radius)	{
	this->playerId = playerId;
	this->position.x = position.x;
	this->position.y = position.y;
	this->run_radius = run_radius;	
	nearToBall = false;
}

int Player::getPlayerId()	{
	return playerId;
}

Point Player::getPosition()	{
	return position;
}

void Player::setPosition(Point position)	{
	this->position.x = position.x;
	this->position.y = position.y;
}

void Player::setNearToBall(bool nearToBall)	{
	this->nearToBall = nearToBall;
}

bool Player::isNearToBall()	{
	return nearToBall;
}

int Player::getRunRadius()	{
	return run_radius;
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
	// cout<<"Ball :"<<ballPosition.x<<","<<ballPosition.y<<endl;
	// cout<<"Destination :"<<destination.x<<","<<destination.y<<endl;
	// cout<<"Distance :"<<distance<<endl;
	// cout<<"Time :"<<time<<endl;
	// cout<<xUnit<<"\t"<<yUnit<<endl;
}

void Player::display() {
	cout<<"Player: { id="<<this->playerId<<", position=("
		<<this->position.x<<","<<this->position.y<<"), nearToBall="<<this->nearToBall<<"}"<<endl;
}