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


//Errors
#define SUCCESS 0
#define ISLAND_ERROR -1
#define OFF_BOARD_ERROR -2
#define OCCUPIED_ERROR -3


enum {
	tie,
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
	int turnCount;

	public:
		Game();
		void printBoard();
		int getTurn(); 
		char getMyToken(); 
		char getOpponentToken();
		bool isOver();
		bool onBoard(pair<int,int> space); 
		bool movesRemain();
		int getWinner();
		int flipTiles(pair<int,int> move, pair<int,int> dir); 
		int makeMove(pair<int,int> move);
		int changeTurn();
		pair<int,int> getMove();
		bool followDirection(pair<int,int> move, const pair<int,int> dir); 
		int validateMove(const pair<int,int> move);
};
	
#endif // BOARD_H
