#include "iostream"
#include "stdlib.h"
#include "math.h"
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

int PLAYER_VICINITY_TO_PLAY = 40;
int PLAYER_VICINITY_TO_CAPTURE = 20;

/*Time for which simulation will continue. Basically, count of while loop iterations*/
int TIME = 10;

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

/*#pragma omp declare simd 
Refer to http://www.hpctoday.com/hpc-labs/explicit-vector-programming-with-openmp-4-0-simd-extensions/ */
bool isPlayerInBallVicinity(Player currentPlayer)	{
	/* Check Distance between current player location and ball location
	If less than Player run radius return true, else false */
	double distance = sqrt( pow((currentPlayer.getPosition().x - ball.getPosition().x), 2) 
						+ pow((currentPlayer.getPosition().y - ball.getPosition().y), 2) );
	if(distance <= currentPlayer.getRunRadius())	{
		return true;
	}		
	return false;
}

/*#pragma omp declare simd
Refer to http://www.hpctoday.com/hpc-labs/explicit-vector-programming-with-openmp-4-0-simd-extensions/ */
void runTowardsBall(Player* currentPlayer)	{
	double distance = sqrt( pow(((*currentPlayer).getPosition().x - ball.getPosition().x), 2) 
						+ pow(((*currentPlayer).getPosition().y - ball.getPosition().y), 2) );

	if(distance < 10)	{
		double time = distance / 2;
		double xUnit = (ball.getPosition().x - (*currentPlayer).getPosition().x) / time;
		double yUnit = (ball.getPosition().y - (*currentPlayer).getPosition().y) / time;	

		Point position = (*currentPlayer).getPosition();
		position.x += xUnit;
		position.y += yUnit;
		(*currentPlayer).setPosition(position);
	}/*else {
		//Move the player to a point by selecting a random point with in run radius circle
		Point position;
		double xMovement = rand() % (*currentPlayer).getRunRadius();
		double yMovement = rand() % (*currentPlayer).getRunRadius();

		position = (*currentPlayer).getPosition();
		position.x += xMovement;
		position.y += yMovement;

		(*currentPlayer).setPosition(position);
	}*/
}


void stop()	{

}

Point getPlayerPositions(int i)	{
	return players[i].getPosition();
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

void updateBall() {
	Point currBallPosition = ball.getPosition();

	Point p;
	// Move ball by unit distance. We can not move that in parallel threads.
	//Update the location of ball by unit in x direction and mx + c in y direction.
	p.x = currBallPosition.x + ball.getXMovement();

	//Stmt below depends on above statement to finish evaluation..
	p.y = currBallPosition.y + ball.getYMovement();

	/* Ball is deflected if it reaches the boudary edges in X-Driection */
	if(p.x == 0 || p.x == BREADTH)	{
		ball.setXMovement(ball.getXMovement() * -1);
/*		cout<<"#####################################################"
		<<"Deflecting on x"<<endl;
*/	}

	/* Ball is deflected if it reaches the boudary edges in Y-Direction */
	if(p.y == 0 || p.y == HEIGHT)	{
		ball.setYMovement(ball.getYMovement() * -1);
/*		cout<<"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"
		<<"Deflecting on y"<<endl;*/		
	}

/*	cout<<ball.getXMovement()<<"===="<<ball.getYMovement()<<endl;
	cout << p.x <<"===="<<p.y<<endl;
*/	ball.setPosition(p);		
	//ball.display();
}

void play()	{
	
	initPositions();

	int i = 0;
    
    auto dt_s = high_resolution_clock::now();

	while(i++ < TIME)	{

		for(int currentPlayer = 0; currentPlayer < 10; currentPlayer++)	{
			int loop = 0;

			while(loop++ < 10)	{
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
/*	double slope, constant;
	slope = (double)(nextBallPosition.y - currBallPosition.y) / (double)(nextBallPosition.x - currBallPosition.x);
	constant = nextBallPosition.y - (slope * nextBallPosition.x);
*/
	int j = 0;
	
	#pragma omp parallel
	{	
		while(i++ < TIME) {
			/* Loop over all the players and perform these operations
			a. Check if ball is in the vicinity of any player
			b. If yes then update player variable which tells player is having ball
			c. If no then relevant player should run in the direction of ball*/
	   		#pragma omp for
			for(int currentPlayer = 0; currentPlayer < 10; currentPlayer++)	{

				bool isInVicinity = isPlayerInBallVicinity(players[currentPlayer]);
				if (isInVicinity) {
					players[currentPlayer].setNearToBall(true);
					players[currentPlayer].hitBall(&ball, players[rand()%10].getPosition(), 3);
				} else {
					players[currentPlayer].setNearToBall(false);
					runTowardsBall(&players[currentPlayer]);
				}
/*
				// displaying updated position
				#pragma omp critical
				{
					players[currentPlayer].display();
				}*/
			}		
			#pragma omp single	
			{
				updateBall();
			}
			/* If there is player in the vicinity of the ball randomly select my team player near by to you
			and kick to him, else just continue */

		}		
	}

    dt = duration_cast<nanoseconds> (high_resolution_clock::now() - dt_s); 
    cout << "Parallel = " << dt.count() << " ns" << "\n";
}

int main()	{
	initPositions();
	cout << "Players are created \n";
	cout << "P1->X: " << players[0].getPosition().x << "\n";
	cout << "Starting to play\n";
	// Point p;
	// p.x = 400;
	// p.y = 400;
	// players[0].hitBall(&ball, p, 2);
	// players[0].hitBall(&ball, p, 1);
	
	// p.x = 0;
	// p.y = 0;
	// players[0].hitBall(&ball, p, 2);

	ball.display();
	play();
	return 1;
}