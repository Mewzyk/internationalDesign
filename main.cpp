
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "board.h"

using namespace std;

#ifndef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Welcome to Othello---" << endl << endl;
	Game myGame = newGame();

	while(1){	
		//print current info
		printBoard(myGame);
		cout << "Player"<< getTurn(myGame) + 1 <<"'s turn" << endl;

		//get desired move
		std::pair<int,int> newMove = getMove(myGame);

		//check if valid

		//make move
		makeMove(myGame, newMove.first, newMove.second);
		changeTurn(myGame);
	}

	return 0;
}
#endif //MAIN

