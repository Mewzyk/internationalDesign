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


struct TileInfo{
        int moveDirs;
        char token;
};

typedef struct TileInfo * Tile;

class Game {
	int turn;
	char p1Token;
	char p2Token;
	Tile board[8][8];

	public:
		Game();
		void printBoard();
		int getTurn();
		char getOpponentToken();
		int makeMove(int i, int j);
		int changeTurn();
		pair<int,int> getMove();
		bool validateMove(const pair<int,int> move);
};
	
#endif // BOARD_H
