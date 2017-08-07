/* board.cpp 
 * edit 7/31 bbaltaxe
 * 	8/02 sgthomas
 *      8/03 sgthomas
 *      8/05 bbaltaxe
 *      8/07 bbaltaxe
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

char Game::getMyToken(){
	if(turn == player1){
		return p1Token;
	} else {
		return p2Token;
	}
}

char Game::getOpponentToken(){
	if (turn == player1){
		return p2Token;
	} else{
		return p1Token;
	}
}

bool Game::onBoard(pair<int,int> space){
	if((space.first < 0) || (space.second < 0) || (space.first > 7) || (space.second > 7)){
		return false; 
	}
	return true;
	
}

bool Game::isOver(){
	if (turnCount == 60){
		return true;
	}else{
		return false;
	}
}

bool Game::movesRemain(){
	for(int i = 0; i < 8 ; i++){
		for (int j = 0; j < 8; j++){
			if (validateMove(make_pair(i,j)) == SUCCESS){
				return true; //find first valid move and return
			}	
		}
	}
	return false;
}

int Game::getWinner(){
	int p1 = 0, p2 = 0;
	for(int i = 0; i < 8 ; i++){
		for (int j = 0; j < 8; j++){
			if(board[i][j]->token == p1Token){
				p1++;
			} else if (board[i][j]->token == p2Token){
				p2++;
			}
		}
	}
	
	if (p1>p2){ 
		return player1; 
	} else if (p2>p1){ 
		return player2; 
	} else { 
		return tie; 
	}
}
//---Manipulation-Functions---//
 
int Game::flipTiles(pair<int,int> move, const pair<int,int> dir){
	move = move + dir;
	if(board[move.first][move.second]->token == getOpponentToken()){
		board[move.first][move.second]->token = getMyToken();
		flipTiles(move,dir);
	} 
	return SUCCESS;
}


//inserts player's move into board. Assume it has already been checked for validity
int Game::makeMove(pair<int,int> move){
	//place piece
	board[move.first][move.second]->token = getMyToken();

	//flip pieces in all valid directions	
	if (board[move.first][move.second]->moveDirs & NORTH){
		flipTiles(move,N);	
	}
	if (board[move.first][move.second]->moveDirs & NORTHEAST){
		flipTiles(move,NE);	
	}
	if (board[move.first][move.second]->moveDirs & EAST){
		flipTiles(move,E);	
	}
	if (board[move.first][move.second]->moveDirs & SOUTHEAST){
		flipTiles(move,SE);	
	}
	if (board[move.first][move.second]->moveDirs & SOUTH){
		flipTiles(move,S);	
	}
	if (board[move.first][move.second]->moveDirs & SOUTHWEST){
		flipTiles(move,SW);	
	}
	if (board[move.first][move.second]->moveDirs & WEST){
		flipTiles(move,W);	
	}
	if (board[move.first][move.second]->moveDirs & NORTHWEST){
		flipTiles(move,NW);	
	}
	
	turnCount++;
	return SUCCESS;
}

//toggles turn
int Game::changeTurn(){
	if (turn == player1){
		turn = player2;
	}else{
		turn = player1;
	}
	return SUCCESS;
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
			cout << "\nYour desired move is not on the board. Please press 'Enter' to try again." << endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}

	}

	intIndicies.first = charIndicies.first - '0';
	intIndicies.second = charIndicies.second - 'A';	
	
	return intIndicies;
}		

bool Game::followDirection(pair<int,int> move, const pair<int,int> dir){
	move = move+dir;
	bool retval = false;

 	if((!onBoard(move)) || (board[move.first][move.second]->token == '-')){
		retval = false;
	} else if (board[move.first][move.second]->token == getMyToken()){
		retval =  true;
	} else if (board[move.first][move.second]->token == getOpponentToken()){
		retval = followDirection(move, dir);
	}
	return retval;	
}

int Game::validateMove(const pair<int,int> move){
	pair<int,int> checkSpace = move;

	//check if empty
	if (board[move.first][move.second]->token != '-'){
		return OCCUPIED_ERROR;
	} 
	
	//check surrounding spaces 
	checkSpace = move + N;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,N))){
		board[move.first][move.second]->moveDirs |= NORTH;
	} 
	checkSpace = move + NE;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,NE))){
		board[move.first][move.second]->moveDirs |= NORTHEAST; 
	} 
	checkSpace = move + E;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,E))){
		board[move.first][move.second]->moveDirs |= EAST; 
	} 
	checkSpace = move + SE;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,SE))){
		board[move.first][move.second]->moveDirs |= SOUTHEAST; 
	} 
	checkSpace = move + S;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,S))){
		board[move.first][move.second]->moveDirs |= SOUTH; 
	} 
	checkSpace = move + SW;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,SW))){
		board[move.first][move.second]->moveDirs |= SOUTHWEST; 
	} 
	checkSpace = move + W;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,W))){
		board[move.first][move.second]->moveDirs |= WEST; 
	} 
	checkSpace = move + NW;
	if( (onBoard(checkSpace)) && (board[checkSpace.first][checkSpace.second]->token == getOpponentToken()) && (followDirection(checkSpace,NW))){
		board[move.first][move.second]->moveDirs |= NORTHWEST; 
	} 

	if(!board[move.first][move.second]->moveDirs){
		return ISLAND_ERROR;
	} 

	return SUCCESS;
}	

//TODO make a function for no possible moves
//TODO make a function to check if there is a winner
//TODO make return values (success, error, etc.) consistent 
//TODO make a function to determine the winne and the score

//---File-Test-Harness---//
#ifdef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Board-Test---" << endl;
	return SUCCESS;
}

#endif //BOARD_TEST
