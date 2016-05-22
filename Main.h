#ifndef MAIN_H
#define MAIN_H

#include "Point.h"
#include "Player.h"

extern Player players[10];

//List of methods exposed to Python API Call
Point getPlayerPositions(int i);
Point getBallPosition();
void init();
void play();
void stop();
int getBoundaryBreadth();
int getBoundaryHeight();

#endif