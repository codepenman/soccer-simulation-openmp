#include <iostream>
#include "Player.h"
using namespace std;

Player::Player()	{
	this->playerId = -1;
	this->position.x = -1;
	this->position.y = -1;
	this->run_radius = 0;
}

Player::Player(int playerId, Point position, int run_radius)	{
	this->playerId = playerId;
	this->position.x = position.x;
	this->position.y = position.y;
	this->run_radius = run_radius;	
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

