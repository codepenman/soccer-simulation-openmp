#include "iostream"
#include "Point.h"
#include "Player.h"
#include "omp.h"
#include <boost/chrono.hpp>

using namespace std;
using namespace boost::chrono;

/*Breadth and Height of Football ground*/
int BREADTH = 300;
int HEIGHT = 200;

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

int main()	{

/***1 - 5 belongs to team - 1***/
	Point p1_pos;
	p1_pos.x = 145;
	p1_pos.y = 100; 
	Player p1(1, p1_pos, 3);

	Point p2_pos;
	p2_pos.x = 145;
	p2_pos.y = 175; 
	Player p2(2, p2_pos, 3);

	Point p3_pos;
	p3_pos.x = 135;
	p3_pos.y = 90; 
	Player p3(3, p3_pos, 3);

	Point p4_pos;
	p4_pos.x = 135;
	p4_pos.y = 125; 
	Player p4(4, p4_pos, 3);

	Point p5_pos;
	p5_pos.x = 15;
	p5_pos.y = 100; 
	Player p5(5, p5_pos, 3);

/***6 - 10 belongs to team - 2***/
	Point p6_pos;
	p6_pos.x = 155;
	p6_pos.y = 100; 
	Player p6(6, p6_pos, 3);

	Point p7_pos;
	p7_pos.x = 155;
	p7_pos.y = 175; 
	Player p7(7, p7_pos, 3);

	Point p8_pos;
	p8_pos.x = 165;
	p8_pos.y = 90; 
	Player p8(8, p8_pos, 3);

	Point p9_pos;
	p9_pos.x = 165;
	p9_pos.y = 125; 
	Player p9(9, p9_pos, 3);

	Point p10_pos;
	p10_pos.x = 285;
	p10_pos.y = 100; 
	Player p10(10, p10_pos, 3);

	cout << "Players are created \n";

	Player players[10] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10};

	cout << "P1->X: " << players[0].getPosition().x << "\n";

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
	#pragma omp parallel
	{
		while(i++ < 100000)	{	   		
	   		#pragma omp parallel for schedule(dynamic)
			for(int currentPlayer = 0; currentPlayer < 10; currentPlayer++)	{
				int loop = 0;

				while(loop++ < 100)	{
				}
			}		
		}		
	}

    dt = duration_cast<nanoseconds> (high_resolution_clock::now() - dt_s); 
    cout << "Parallel = " << dt.count() << " ns" << "\n";

	return 1;
}