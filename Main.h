#ifndef MAIN_H
#define MAIN_H

#include "Point.h"

//List of methods exposed to Python API Call
extern Point* getPlayerPositions();
extern Point getBallPosition();
extern void play();
void stop();
int getBoundaryBreadth();
int getBoundaryHeight();

#endif