#include <iostream>

using namespace std;

/**
 * @class: board
 * 
 * Data
 * @tile: holds the gameboard
 * 
 */

class board {
	
	private:
		tile board[8][8];

	public:
		board() = default; // Default constructor
			   // Possibly in future have user send in an ID when they create a board or something
		//Functions of class board
		//with a reference to a board object call by board::methodName()	
		void initBoard();
		void printBoard();
		
				 
};

/**
 * Holds information for one node of the board
 *
 * @pair: coordinates in the grid 
 * @datum: token that will appear on the board
 */
struct tile {
	pair <int><int> locaton;
	char datum; 
};

