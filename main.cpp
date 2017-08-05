#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "board.h"

using namespace std;

#ifndef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Welcome to Othello---" << endl << endl;
	Game myGame;
	bool valid = false;
	bool inGame = true;
	pair<int,int> newMove;

	
	while(inGame){	
		//print current info
		myGame.printBoard();
		cout << "Player"<< myGame.getTurn() + 1 <<"'s turn" << endl;

		//wait for valid move input
		valid = false;
		while(!valid){
			//get desired move
			newMove = myGame.getMove();
	
			//check if valid
			if(myGame.validateMove(newMove)){
				valid = true;	
			}
		}

		//make move
		myGame.makeMove(newMove);
		myGame.changeTurn();
		
		//check game state
		if(myGame.isOver()){
			inGame = false;
		}
	}

	return 0;
}
#endif //MAIN
