/**
 * @class: board
 * 
 * Data
 * @tile: holds the gameboard
 * 
 */
#ifndef BOARD_H
#define BOARD_H


using namespace std;

//#define BOARD_TEST


enum {
	player1,
	player2
};


struct TileInfo{ //TODO make private
        int moveDirs;
        char token;
};

typedef struct TileInfo * Tile;

class Game { //TODO can we make all members of the class private too? 
	int turn;
	char p1Token;
	char p2Token;
	Tile board[8][8];
	int turnCount;

	public:
		Game();
		void printBoard();
		int getTurn();
		char getMyToken();
		char getOpponentToken();
		bool isOver();
		bool onBoard(pair<int,int> space); //TODO make private
		int flipTiles(pair<int,int> move, pair<int,int> dir); //TODO make private
		int makeMove(pair<int,int> move);
		int changeTurn();
		pair<int,int> getMove();
		bool followDirection(pair<int,int> move, const pair<int,int> dir); //TODO make private
		bool validateMove(const pair<int,int> move);
};
	
#endif // BOARD_H
