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

typedef struct TileInfo * Tile;

typedef struct GameInfo * Game;

//---Creation-Functions---//
Game newGame(void);
	

//---Access-Functions---//
void printBoard(Game myGame);

int getTurn(Game myGame);


//---Manipulation-Functions---//
int makeMove(Game myGame, int i, int j);

int changeTurn(Game myGame);

std::pair<int,int> getMove(Game myGame);

#endif // BOARD_H
