#ifndef MAIN_H
#define MAIN_H

#include "Point.h"

//List of methods exposed to Python API Call
void getPlayerPositions();
Point getBallPosition();
void play();
void stop();
int getBoundaryBreadth();
int getBoundaryHeight();

#endif