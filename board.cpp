/* board.cpp 
 * Last edit 7/20 bbaltaxe
 */


#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "board.h"

using namespace std;

//#define BOARD_TEST

//---Creation-Functions---//
Game newGame(void){
	Game myGame = new GameInfo();
	
	myGame->turn = player1;
	
	//get desired tokens from user
	cout << "Player 1, please choose a game piece:";
	cin.get(myGame->p1Token);
	cin.get();
	cout << "Player 2, please choose a game piece:";
	cin.get(myGame->p2Token);
	cin.get();
	

	//initialize board
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			myGame->board[i][j] = new TileInfo;
			myGame->board[i][j]->token = '-';
		}
	}

	//set center pieces in place
	myGame->board[3][4]->token = myGame->p1Token;
	myGame->board[4][3]->token = myGame->p1Token;
	myGame->board[3][3]->token = myGame->p2Token;	
	myGame->board[4][4]->token = myGame->p2Token;


	return myGame;
}

//---Access-Functions---//
void printBoard(Game myGame){
	char A = 'A';

	//print ABC index	
	cout << endl << "  ";
	for(int i = 0; i < 8 ; i++){
		cout << A << " ";
		A++;
	}
	cout << endl;

	for(int i = 0; i < 8 ; i++){
		cout << i << " ";
		for (int j = 0; j < 8; j++){
			cout << myGame->board[i][j]->token << " ";
		}
		cout << endl;
	}
	return; 
}

int getTurn(Game myGame){
	return myGame->turn;
}

//---Manipulation-Functions---//
int makeMove(int player, Game myGame, int i, int j){
	if( (0 > i > 8) || (0 > j > 8)){
		cout << "cannot make move: indexing" << endl;
		return -1;
	}

	switch (player){
		case player1:
			myGame->board[i][j]->token = myGame->p1Token;
			break;
		case player2:
			myGame->board[i][j]->token = myGame->p2Token;
			break;
		default:
			cout << "cannot make move: invalid player" << endl;
			return -1;
			break;
	}		
	return 0; //SUCCESS
}

//---File-Test-Harness---//
#ifdef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Board-Test---" << endl;
/*	Game myGame = newGame();

	cout << "player 1 chose: " << myGame->p1Token << endl;
	cout << "player 2 chose: " << myGame->p2Token << endl;
	
	cout << "---board maybe follows" << endl;
	
	printBoard(myGame);

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8 ; j++){
			makeMove(player1,myGame,i,j);
		}
	}
	printBoard(myGame);
*/
	return 0;
}

#endif //BOARD_TEST
