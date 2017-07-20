/**
 * @class: board
 * 
 * Data
 * @tile: holds the gameboard
 * 
 */
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <stdexcept>
#include <unistd.h>

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
typedef TileInfo * Tile;

struct GameInfo{
	int turn; 
	char p1Token; 
	char p2Token; 
	Tile board[8][8];
};


typedef GameInfo * Game;

//---Creation-Functions---//
Game newGame(void);
	

//---Access-Functions---//
void printBoard(Game myGame);


//---Manipulation-Functions---//
int makeMove(int player, Game myGame, int i, int j);


#endif // BOARD_H
