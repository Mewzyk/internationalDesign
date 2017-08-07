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
		cout << "Player"<< myGame.getTurn()<<"'s turn" << endl;

		//wait for valid move input
		valid = false;
		while(!valid){
			//get desired move
			newMove = myGame.getMove();
	
			//check if valid
			int moveStatus = myGame.validateMove(newMove);
			if(moveStatus == SUCCESS){
				valid = true;	
				//make move
				myGame.makeMove(newMove);

			} else if (moveStatus == ISLAND_ERROR){
				cout << "Invalid move: No flips can be made here. Please try again." << endl;
			} else if (moveStatus == OCCUPIED_ERROR){
				cout << "Invalid move: That space is not empty. Please try again." << endl;
			} else if (!myGame.movesRemain()){
				valid = true;
				cout << "Oops! You have no moves. It is now your opponent's turn." << endl;		
			} 
		}

		myGame.changeTurn();
		
		//check game state
		if(myGame.isOver()){
			inGame = false;
			int results = myGame.getWinner();
			if(results == tie){
				cout << "----it's a tie!----" << endl;
			} else {
				cout << "---Player" << results <<" wins!" << endl;
			}
		}
	}

	return 0;
}
#endif //MAIN
