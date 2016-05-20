#include "iostream"
#include "stdlib.h"
#include "Math.h"
#include "Player.h"
#include "Ball.h"
#include "omp.h"
#include <boost/chrono.hpp>
#include "Main.h"

using namespace std;
using namespace boost::chrono;

/*Breadth and Height of Football ground*/
int BREADTH = 300;
int HEIGHT = 200;

Player players[10];
Ball ball;

/********************************************************************************************************************
		View of ground

		Y-AXIS
		^
		|
		|
		|
		|
		|
		|        
		|
		|                   300
		|--------------------------------------------
		|					   |					|
		|					   |					|
		|					   |					|
		|----				   |				----|
		|	|				   |				|	| 200
		|	|				   |				|	|
		|----				   |				----|
		|					   |					|
		|					   |					|
		|______________________|____________________|______________________> X - Axis
		(0, 0)
***********************************************************************************************************************/

void initPositions()	{

	Point ball_position;
	ball_position.x = 150;
	ball_position.y = 100;

	ball.setPosition(ball_position);

/***1 - 5 belongs to team - 1***/
	Point p1_pos;
	p1_pos.x = 145;
	p1_pos.y = 100; 
	Player p1(1, p1_pos, 3);
	players[0] = p1;

	Point p2_pos;
	p2_pos.x = 145;
	p2_pos.y = 175; 
	Player p2(2, p2_pos, 3);
	players[1] = p2;

	Point p3_pos;
	p3_pos.x = 135;
	p3_pos.y = 90; 
	Player p3(3, p3_pos, 3);
	players[2] = p3;

	Point p4_pos;
	p4_pos.x = 135;
	p4_pos.y = 125; 
	Player p4(4, p4_pos, 3);
	players[3] = p4;

	Point p5_pos;
	p5_pos.x = 15;
	p5_pos.y = 100; 
	Player p5(5, p5_pos, 3);
	players[4] = p5;

/***6 - 10 belongs to team - 2***/
	Point p6_pos;
	p6_pos.x = 155;
	p6_pos.y = 100; 
	Player p6(6, p6_pos, 3);
	players[5] = p6;

	Point p7_pos;
	p7_pos.x = 155;
	p7_pos.y = 175; 
	Player p7(7, p7_pos, 3);
	players[6] = p7;

	Point p8_pos;
	p8_pos.x = 165;
	p8_pos.y = 90; 
	Player p8(8, p8_pos, 3);
	players[7] = p8;

	Point p9_pos;
	p9_pos.x = 165;
	p9_pos.y = 125; 
	Player p9(9, p9_pos, 3);
	players[8] = p9;

	Point p10_pos;
	p10_pos.x = 285;
	p10_pos.y = 100; 
	Player p10(10, p10_pos, 3);
	players[9] = p10;
}

int main()	{

	initPositions();

	cout << "Players are created \n";

	cout << "P1->X: " << players[0].getPosition().x << "\n";

	cout << "Starting to play\n";
	play();

	return 1;
}

void play()	{
	
	initPositions();

	int i = 0;
    
    auto dt_s = high_resolution_clock::now();

	while(i++ < 100000)	{

		for(int currentPlayer = 0; currentPlayer < 10; currentPlayer++)	{
			int loop = 0;
			while(loop++ < 100)	{
			}
		}
	}

    auto dt = duration_cast<nanoseconds> (high_resolution_clock::now() - dt_s); 
    cout << "Sequential = " << dt.count() << " ns" << "\n";

    dt_s = high_resolution_clock::now();

	i = 0;
	
	//I assume p1 has the ball first, p1 location should be reachable to ball location..
	Point currBallPosition = ball.getPosition();

	Point playerPosition;
	playerPosition.x = currBallPosition.x - 1;
	playerPosition.y = currBallPosition.y - 1;	
	players[0].setPosition(playerPosition);

	//P1 got to the ball first and kicked the ball to player with id 2 in his team
	int x = players[1].getPosition().x;
	int y = players[1].getPosition().y;

	Point nextBallPosition;
	nextBallPosition.x = x;
	nextBallPosition.y = y;

	//Calculate slope and constant of the line equation(y = mx + c) given start and end point
	float slope, constant;
	slope = (float)(nextBallPosition.y - currBallPosition.y) / (float)(nextBallPosition.x - currBallPosition.x);
	constant = nextBallPosition.y - (slope * nextBallPosition.x);

	//#pragma omp parallel
	{	
		while(i++ < 100000)	{	   		
			//Update the location of ball by unit in x direction and mx + c in y direction.
			currBallPosition.x++;
			//Stmt below depends on above statement to finish evaluation..
			currBallPosition.y = slope * currBallPosition.x + constant;

			/* Loop over all the players and perform these operations
			a. Check if ball is in the vicinity of any player
			b. If yes then update player variable which tells player is having ball
			c. If no then relevant player should run in the direction of ball*/
	   		//#pragma omp parallel for schedule(dynamic)
			for(int currentPlayer = 0; currentPlayer < 10; currentPlayer++)	{
				bool isInVicinity = isPlayerInBallVicinity(players[currentPlayer]);
				if(isInVicinity)	{
					players[currentPlayer].setNearToBall(true);
				}else	{
					runTowardsBall(players[currentPlayer]);
				}
			}		

			/* If there is player in the vicinity of the ball randomly select my team player near by to you
			and kick to him, else just continue */

		}		
	}

    dt = duration_cast<nanoseconds> (high_resolution_clock::now() - dt_s); 
    cout << "Parallel = " << dt.count() << " ns" << "\n";
}

/*#pragma omp declare simd 
Refer to http://www.hpctoday.com/hpc-labs/explicit-vector-programming-with-openmp-4-0-simd-extensions/ */
bool isPlayerInBallVicinity(Player currentPlayer)	{
	/* Check Distance between current player location and ball location
	If less than Player run radius return true, else false */
	float distance = sqrt( pow((currentPlayer.x - ball.getPosition().x), 2) 
						+ pow((currentPlayer.y - ball.getPosition().y), 2) );
	if(distance <= currentPlayer.getRunRadius())	{
		return true;
	}		
	return false;
}

/*#pragma omp declare simd
Refer to http://www.hpctoday.com/hpc-labs/explicit-vector-programming-with-openmp-4-0-simd-extensions/ */
void runTowardsBall(Player player)	{
	if(shouldRun(player))	{

	}else {
		//Move the player to a point by selecting a random point with in run radius circle
	}
}

/* Check the location of player and location of ball, then decide weather this player can run towards ball
or not */
bool shouldRun(Player player)	{

}

void stop()	{

}

Point* getPlayerPositions()	{
	Point *points;
	points = new Point[10];
	for (int i=0; i<10; i++) {
		points[i] = players[i].getPosition();
	}

	for (int i=0; i<10; i++) {
		cout<<points[i].x<<endl;
	}
	return points;
}

Point getBallPosition()	{
	return ball.getPosition();
}

int getBoundaryBreadth()	{
	return BREADTH;
}

int getBoundaryHeight()	{
	return HEIGHT;
}
