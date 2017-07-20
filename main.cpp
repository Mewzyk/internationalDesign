
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "board.h"

using namespace std;


#ifndef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Welcome to Othello---" << endl << endl;
	Game myGame = newGame();
	char row, col;

	while(1){

		//TODO: Allow players to enter their own names
		//Player1's turn 
		printBoard(myGame);
		cout << "Player 1's turn" << endl;
		cout << "Column:";
		cin.get(col);
		cin.get();
		cout << "Row:";
		cin.get(row);
		cin.get();
		makeMove(player1,myGame,row-'0',col-'A');

		//Player2's turn 
		printBoard(myGame);
		cout << "Player 2's turn" << endl;
		cout << "Column:";
		cin.get(col);
		cin.get();
		cout << "Row:";
		cin.get(row);
		cin.get();
		makeMove(player2,myGame,row-'0',col-'A');


	}

	return 0;
}
#endif //MAIN

