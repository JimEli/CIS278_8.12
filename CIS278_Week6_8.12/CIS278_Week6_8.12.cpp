/*************************************************************************
* Title: Simulation: The Tortoise and the Hare
* File: CIS278_Week6_8.12.cpp
* Author: James Eli
* Date: 2/2/2018
*
* Exercise 8.12 on page 374 - 375, Simulation: The Tortoise and the Hare
*
* In this exercise, you’ll recreate the classic race of the tortoise and 
* the hare. You’ll use random number generation to develop a simulation 
* of this memorable event.
*
* Our contenders begin the race at "square 1" of 70 squares. Each square 
* represents a possible position along the race course. The finish line 
* is at square 70. The first contender to reach or pass square 70 is 
* rewarded with a pail of fresh carrots and lettuce. The course weaves 
* its way up the side of a slippery mountain, so occasionally the 
* contenders lose ground.
*
* There is a clock that ticks once per second. With each tick of the 
* clock, your program should use function moveTortoise and moveHare to
* adjust the position of the animals according to the rules in Fig. 8-18.
* These functions should use pointer-based pass-by-reference to modify 
* the position of the tortoise and the hare.
*                       Percent
*   Animal   Move type  of time Actual move
*   Tortoise Fast plod  50%     3 squares to the right
*            Slip       20%     6 squares to the left
*            Slow plod  30%     1 square to the right
*   Hare     Sleep      20%     No move at all
*            Big hop    20%     9 squares to the right
*            Big slip   10%     12 squares to the left
*            Small hop  30%     1 square to the right
*            Small slip 20%     2 squares to the left
*
* Use variables to keep track of the positions of the animals (i.e., 
* position numbers are 1-70). Start each animal at position 1 (i.e., the 
* "starting gate"). If an animal slips left before square 1, move the 
* animal back to square 1.
* Generate the percentages in Fig. 8-18 by producing a random integer i 
* in the range 1<=i<=10. For the tortoise, perform a "fast plod" when 
* 1<=i<=5, a "slip" when 6<=i<-7 or a "slow plod" when 8<=i<=10. Use a 
* similar technique to move the hare.
*
* Begin the race by displaying
*   BANG !!!!!
*   AND THEY’RE OFF !!!!!
* For each tick of the clock (i.e., each iteration of a loop), display a 
* 70-position line showing the letter T in the tortoise’s position and 
* the letter H in the hare’s position. Occasionally, the contenders land 
* on the same square. In this case, the tortoise bites the hare and your 
* program should display OUCH!!! beginning at that position. All positions 
* other than the T, the H or the OUCH!!! (in case of a tie) should be 
* blank.
*
* After displaying each line, test whether either animal has reached or 
* passed square 70. If so, display the winner and terminate the simulation.
* If the tortoise wins display TORTOISE WINS!!!YAY!!! If the hare wins, 
* display Hare wins. Yuch. If both animals win on the same clock tick, you 
* may want to favor the tortoise (the "underdog"), or you may want to 
* display It’s a tie. If neither animal wins, perform the loop again to 
* simulate the next tick of the clock.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   02/02/2018: Initial release. JME
*************************************************************************/
#include <iostream> // cin/cout/endl
#include <string>   // string
#include <ctime>    // time for random seed
#include <random>   // random
#include <chrono>   // delay
#include <thread>   // delay

using namespace std;

// Check position not outside course bounds & return true if across finsihline.
bool checkCourseLimits(int& pos)
{
	// Position of the finishline.
	const int FINISH_LINE{ 70 };

	// Check if position less than 1, or > finishline.
	if (pos < 1)
		pos = 1;
	return pos >= FINISH_LINE ? true : false;
}

// Random numbe generator [0...10).
int rng(void) {
	return int(10 * rand() / (RAND_MAX + 1.0)); 
}

int main()
{
	// Race contestants
	enum Contestants { NEITHER = 0, HARE, TORTOISE };
	// Flag for determining when race is complete.
	Contestants winner{ NEITHER };
	// Contestant positions.
	int tortoisePos{ 1 }, harePos{ 1 };

	// Seed the rng.
	srand((unsigned)time(0));

	// Start the race.
	cout << "The Tortoise and the Hare Simulation\n";
	cout << "BANG !!!!!\n" << "AND THEY'RE OFF !!!!!\n";
	
	// Loop until we have a winner.
	while (!winner)
	{
		// Race course without contestants.
		string raceCourse = string(70, '-') + "|" + string(12, ' ');
		// Tortoise & hare movement increments.
		const int tMoves[10] = { 3, 3, 3, 3, 3, -6, -6, 1, 1, 1 };
		const int hMoves[10] = { 0, 0, 9, 9, -12, 1, 1, 1, -2, -2 };

		// Move contestants until somebody wins via annonymous lambda functions.
		if ([=](int& tPos, int rn) mutable -> bool { tPos += tMoves[rn]; return checkCourseLimits(tPos); }(tortoisePos, rng()))
			winner = Contestants::TORTOISE;
		if ([=](int& hPos, int rn) mutable -> bool { hPos += hMoves[rn]; return checkCourseLimits(hPos); }(harePos, rng()))
			winner = Contestants::HARE;

		if (tortoisePos == harePos)
			raceCourse.replace(harePos, 7, "OUCH!!!");
		else
		{
			raceCourse.replace(harePos, 1, "H");
			raceCourse.replace(tortoisePos, 1, "T");
		}

		// Display race course.
		cout << raceCourse << '\r';

		// Insert a 0.5 second delay between turns.
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	// Declare winner.
	cout << (winner == Contestants::TORTOISE ? "\nTORTOISE WINS!!! YAY!!!\n" : "\nHare wins. Yuch.\n");

	return 0;
}

