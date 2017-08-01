#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "board.h"

using namespace std;

#ifndef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Welcome to Othello---" << endl << endl;
	Game myGame = newGame();
	bool valid = false;
	
	while(1){	
		//print current info
		printBoard(myGame);
		cout << "Player"<< getTurn(myGame) + 1 <<"'s turn" << endl;
	
		std::pair<int,int> newMove;	
		while(!valid){
			//get desired move
			newMove = getMove(myGame);
	
			//check if valid
			if(validateMove(myGame, newMove)){
				valid = true;	
			}
		}

		//make move
		makeMove(myGame, newMove.first, newMove.second);
		changeTurn(myGame);
		valid = false;
	}

	return 0;
}
#endif //MAIN
