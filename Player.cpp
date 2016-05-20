#include <iostream>
#include "Player.h"
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