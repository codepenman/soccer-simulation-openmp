#include "iostream"
#include "stdlib.h"
#include "math.h"
#include "Player.h"
#include "Ball.h"
#include "omp.h"
#include <boost/chrono.hpp>
#include <unistd.h>
#include "Main.h"

using namespace std;
using namespace boost::chrono;

/*Breadth and Height of Football ground*/
int BREADTH = 300;
int HEIGHT = 200;

int DISTANCE_TO_BALL_TO_RUN = 10;
//int PLAYER_VICINITY_TO_CAPTURE = 20;

/*Time for which simulation will continue. Basically, count of while loop iterations*/
long TIME = 100000;

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
	Player p1(1, p1_pos, 20, 3);
	players[0] = p1;

	Point p2_pos;
	p2_pos.x = 125;
	p2_pos.y = 175; 
	Player p2(2, p2_pos, 20, 3);
	players[1] = p2;

	Point p3_pos;
	p3_pos.x = 125;
	p3_pos.y = 90; 
	Player p3(3, p3_pos, 20, 3);
	players[2] = p3;

	Point p4_pos;
	p4_pos.x = 105;
	p4_pos.y = 175; 
	Player p4(4, p4_pos, 20, 3);
	players[3] = p4;

	Point p5_pos;
	p5_pos.x = 105;
	p5_pos.y = 90; 
	Player p5(5, p5_pos, 20, 3);
	players[4] = p5;

/***6 - 10 belongs to team - 2***/
	Point p6_pos;
	p6_pos.x = 155;
	p6_pos.y = 100; 
	Player p6(6, p6_pos, 20, 3);
	players[5] = p6;

	Point p7_pos;
	p7_pos.x = 175;
	p7_pos.y = 175; 
	Player p7(7, p7_pos, 20, 3);
	players[6] = p7;

	Point p8_pos;
	p8_pos.x = 175;
	p8_pos.y = 90; 
	Player p8(8, p8_pos, 20, 3);
	players[7] = p8;

	Point p9_pos;
	p9_pos.x = 195;
	p9_pos.y = 175; 
	Player p9(9, p9_pos, 20, 3);
	players[8] = p9;

	Point p10_pos;
	p10_pos.x = 195;
	p10_pos.y = 90; 
	Player p10(10, p10_pos, 20, 3);
	players[9] = p10;
}

/*#pragma omp declare simd 
Refer to http://www.hpctoday.com/hpc-labs/explicit-vector-programming-with-openmp-4-0-simd-extensions/ */
bool isPlayerInBallVicinity(Player player)	{
	/* Check Distance between current player location and ball location
	If less than Player run radius return true, else false */
	double distance = sqrt( pow((player.getCurrentPosition().x - ball.getPosition().x), 2) 
						+ pow((player.getCurrentPosition().y - ball.getPosition().y), 2) );
	if(distance <= player.getRunRadius())	{
		return true;
	}		
	return false;
}

/*#pragma omp declare simd
Refer to http://www.hpctoday.com/hpc-labs/explicit-vector-programming-with-openmp-4-0-simd-extensions/ */
void runTowardsBall(Player* player)	{
	double distance = sqrt( pow(((*player).getZoneCenter().x - ball.getPosition().x), 2) 
						+ pow(((*player).getZoneCenter().y - ball.getPosition().y), 2) );

	if(distance < (*player).getZoneRadius())	{
		//Move towards the ball
		double time = distance / (*player).getRunRadius();
		Point currPosition = (*player).getCurrentPosition();

		double x = (ball.getPosition().x - currPosition.x) / time;
		double y = (ball.getPosition().y - currPosition.y) / time;		

		// Move ball by unit distance. We can not move that in parallel threads.
		//Update the location of player by unit in x direction and in y direction.

		Point p;		
		p.x = currPosition.x + x;
		p.y = currPosition.y + y;
		(*player).setCurrentPosition(p);
	}else {
		//Move the player with in a circle
		(*player).movePlayer();
	}
}


void stop()	{

}

Point getPlayerPositions(int i)	{
	return players[i].getCurrentPosition();
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
		ball.setXMovement(ball.getXMovement() * -1);	}

	/* Ball is deflected if it reaches the boudary edges in Y-Direction */
	if(p.y == 0 || p.y == HEIGHT)	{
		ball.setYMovement(ball.getYMovement() * -1);
	}

	ball.setPosition(p);		
}

long play(int threadNum)	{
	
	initPositions();
    auto dt_s = high_resolution_clock::now();
    
	//I assume p1 has the ball first, p1 location should be reachable to ball location..
	Point currBallPosition = ball.getPosition();

	Point playerPosition;
	playerPosition.x = currBallPosition.x - 1;
	playerPosition.y = currBallPosition.y - 1;	
	players[0].setCurrentPosition(playerPosition);

	//As a start , player 1 will hit the ball to player 2
	players[0].hitBall(&ball, players[1].getCurrentPosition(), 3);

	// omp_set_num_threads(threadNum);
	#pragma omp parallel
	{
		int i = 0;
		// cout<<"Printing threads.."<<endl;
		// cout<<omp_get_thread_num()<<endl;	
		while(i++ < TIME) {
			// usleep(200000);
			/* Loop over all the players and perform these operations
			a. Check if ball is in the vicinity of any player
			b. If yes then update player variable which tells player is having ball
			c. If no then relevant player should run in the direction of ball*/
	   		#pragma omp for nowait
			for(int currentPlayer = 0; currentPlayer < 10; currentPlayer++)	{

				bool isInVicinity = isPlayerInBallVicinity(players[currentPlayer]);
				if (isInVicinity) {
					players[currentPlayer].setNearToBall(true);
					players[currentPlayer].hitBall(&ball, players[rand()%10].getCurrentPosition(), 3);
				} else {
					players[currentPlayer].setNearToBall(false);
					runTowardsBall(&players[currentPlayer]);					
				}
			}
			#pragma omp single nowait	
			{
				updateBall();
			}
		}		
	}

    auto dt = duration_cast<nanoseconds> (high_resolution_clock::now() - dt_s); 
    cout << "Parallel = " << dt.count() << " ns" << "\n";
    return dt.count();
}

void init(long time) {
	TIME = time;
}

int main()	{
	initPositions();
	cout << "Players are created \n";
	cout << "P1->X: " << players[0].getCurrentPosition().x << "\n";
	cout << "Starting to play\n";
	play(4);
	return 1;
}