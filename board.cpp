/* board.cpp 
 * edit 7/31 bbaltaxe
 * 	8/02 sgthomas
 *      8/03 sgthomas
 */

#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <utility>
#include "board.h"

using namespace std;

//#define BOARD_TEST

// matrix move directions - we can make this less global if the program is too beefy
const pair<int,int> N (-1,0);
const pair<int,int> NE (-1,1);
const pair<int,int> E (0,1);
const pair<int,int> SE (1,1);
const pair<int,int> S (1,0);
const pair<int,int> SW (1,-1);
const pair<int,int> W (0,-1);
const pair<int,int> NW (-1,-1);
	
#define NORTH 1
#define NORTHEAST 1 << 1
#define EAST 1 << 2
#define SOUTHEAST 1 << 3
#define SOUTH 1 << 4
#define SOUTHWEST 1 << 5
#define WEST 1 << 6
#define NORTHWEST 1 << 7

//simple operator+ implementation for integers
pair<int, int> operator+(const pair<int, int> & x, const pair<int, int> & y){
	return make_pair(x.first + y.first, x.second + y.second);
}

//---Creation-Functions---//
Game::Game(){
	turn = player1;
	//TODO have player enter name and refer to them by it 	
	//TODO make sure piece is not whitespace like /n or something
	//TODO maybe have the player enter the actual ascii code for desired piece (so they can have something not on the keyboard)
	//get desired tokens from user
	cout << "Player 1, please choose a game token:";
	cin.get(p1Token);
	cin.get();
	cout << "Player 2, please choose a game token:";
	cin.get(p2Token);
	cin.get();
	
	//initialize board
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			this->board[i][j] = new TileInfo;
			this->board[i][j]->token = '-';
		}
	}

	//set center pieces in place
	board[3][4]->token = p1Token;
	board[4][3]->token = p1Token;
	board[3][3]->token = p2Token;	
	board[4][4]->token = p2Token;
}

//---Access-Functions---//
void Game::printBoard(){
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
			cout << board[i][j]->token << " ";
		}
		cout << endl;
	}
	return; 
}

int Game::getTurn(){
	return turn;
}

char Game::getOpponentToken(){
	if (turn == player1){
		return p2Token;
	} else{
		return p1Token;
	}
}

//---Manipulation-Functions---//
 
//inserts player's move into board. Assume it has already been checked for validity
int Game::makeMove(int i, int j){
	if( (0 > i > 8) || (0 > j > 8)){
		cout << "cannot make move: indexing" << endl;
		return -1;
	}

	switch (turn){
		case player1:
			board[i][j]->token = p1Token;
			break;
		case player2:
			board[i][j]->token = p2Token;
			break;
		default:
			cout << "cannot make move: invalid player" << endl;
			return -1;
			break;
	}		
	return 0; //SUCCESS
}

//toggles turn
int Game::changeTurn(){
	if (turn == player1){
		turn = player2;
	}else{
		turn = player1;
	}
	return 0;
}


//requests move from player and checks its validity
pair<int,int> Game::getMove(){

	pair<char,char> charIndicies; //row,col
	pair<int,int> intIndicies; //row, col
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

bool Game::validateMove(const pair<int,int> move){
	pair<int,int> checkSpace = move;
	
	//check if empty
	if (board[move.first][move.second]->token != '-'){
		cout << "This space is not empty." << endl;
		return false;
	} 

	//check surrounding spaces
	//TODO segfault happening because we are indexing out of the matrix here. Need to check that checkSpace is in the matrix before using it to index each time can't think of a non ugly way to do it right now 
	checkSpace = move + N;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= NORTH; 
	} 
	checkSpace = move + NE;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= NORTHEAST; 
	} 
	checkSpace = move + E;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= EAST; 
	} 
	checkSpace = move + SE;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= SOUTHEAST; 
	} 
	checkSpace = move + S;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= SOUTH; 
	} 
	checkSpace = move + SW;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= SOUTHWEST; 
	} 
	checkSpace = move + W;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= WEST; 
	} 
	checkSpace = move + NW;
	if(board[checkSpace.first][checkSpace.second]->token == getOpponentToken()){
		board[move.first][move.second]->moveDirs |= NORTHWEST; 
	} 

	if(!board[move.first][move.second]->moveDirs){
		cout << "Please choose move adjacent to one of your opponent's tokens." << endl;
		return false;
	} else {
		//call helper 
	}

	//recurr 

	return true;
}	

//TODO make a helper function for validateMove to follow the possible moves through to see if they have a piece on the other end of the vector and update moveDirs
//TODO make a helper function for makeMove to flip all the pieces according to moveDirs (should look similar to the validateMove helper , but make changes)


//---File-Test-Harness---//
#ifdef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Board-Test---" << endl;
/*	Game this = newGame();

	cout << "player 1 chose: " << this->p1Token << endl;
	cout << "player 2 chose: " << this->p2Token << endl;
	
	cout << "---board maybe follows" << endl;

	printBoard(this);

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8 ; j++){
			makeMove(player1,this,i,j);
		}
	}
	printBoard(this);
*/
	return 0;
}

#endif //BOARD_TEST
