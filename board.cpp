/* board.cpp 
 * Last edit 7/31 bbaltaxe
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <utility>
#include "board.h"

using namespace std;

//#define BOARD_TEST

struct TileInfo{
	int moveDirs; 
	char token;
};

struct GameInfo{
	int turn; 
	char p1Token; 
	char p2Token; 
	Tile board[8][8];
};

//TODO addition op for pair

//---Creation-Functions---//
Game newGame(void){
	Game myGame = new GameInfo();
	
	myGame->turn = player1;
	
	//TODO make sure piece is not whitespace like /n or something
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
//TODO make move using pair maybe? 
//inserts player's move into board. Assume it has already been checked for validity
int makeMove(Game myGame, int i, int j){
	if( (0 > i > 8) || (0 > j > 8)){
		cout << "cannot make move: indexing" << endl;
		return -1;
	}

	switch (myGame->turn){
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

//toggles turn
int changeTurn(Game myGame){
	if (myGame->turn == player1){
		myGame->turn = player2;
	}else{
		myGame->turn = player1;
	}
	return 0;
}

//requests move from player and checks its validity
std::pair<int,int> getMove(Game myGame){

	std::pair<char,char> charIndicies; //row,col
	std::pair<int,int> intIndicies; //row, col
	bool Valid = false;

	//loop until valid move is made
       	while(!Valid){	
		//get desired move
		cout << "Row(number):";
		cin.get(charIndicies.first);
		cin.get();
		cout << "Column(letter):";
		cin.get(charIndicies.second);
		charIndicies.second = toupper(charIndicies.second);
		cin.get();
	
		//check that it is on the board
		if (('0' <= charIndicies.first ) && (charIndicies.first<='7') && 
		    ('A' <= charIndicies.second) && (charIndicies.second <= 'H')){
			Valid = true;
		} else {
			cout << "Your desired move is not on the board. Please try again." << endl;
		}

	}

	intIndicies.first = charIndicies.first - '0';
	intIndicies.second = charIndicies.second - 'A';	

	return intIndicies;
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
