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

// matrix move directions - we can make this less global if the program is too beefy
const std::pair<int,int> N (-1,0);
const std::pair<int,int> NE (-1,1);
const std::pair<int,int> E (0,1);
const std::pair<int,int> SE (1,1);
const std::pair<int,int> S (1,0);
const std::pair<int,int> SW (1,-1);
const std::pair<int,int> W (0,-1);
const std::pair<int,int> NW (-1,-1);
	
#define NORTH 1
#define NORTHEAST 1 << 1
#define EAST 1 << 2
#define SOUTHEAST 1 << 3
#define SOUTH 1 << 4
#define SOUTHWEST 1 << 5
#define WEST 1 << 6
#define NORTHWEST 1 << 7



//---Struct-Ops---//
template <typename T, typename U>
//TODO fix warning for return type
//addition for pair
std::pair<T,U> operator+(const std::pair<T,U> & l, const std::pair<T,U> & r){
	return {l.first+r.first,l.second+r.second};
}

//---Creation-Functions---//
Game newGame(void){
	Game myGame = new GameInfo();
	
	myGame->turn = player1;
	//TODO have player enter name and refer to them by it 	
	//TODO make sure piece is not whitespace like /n or something
	//TODO maybe have the player enter the actual ascii code for desired piece (so they can have something not on the keyboard)
	//get desired tokens from user
	cout << "Player 1, please choose a game token:";
	cin.get(myGame->p1Token);
	cin.get();
	cout << "Player 2, please choose a game token:";
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

	//set valid movedirs
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

char getOpponentToken(Game myGame){
	if (myGame->turn == player1){
		return myGame->p2Token;
	} else{
		return myGame->p1Token;
	}
}

//---Manipulation-Functions---//
 
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

bool validateMove(Game myGame, const std::pair<int,int> move){
	std::pair<int,int> checkSpace = move;
	
	//check if empty
	if (myGame->board[move.first][move.second]->token != '-'){
		cout << "This space is not empty." << endl;
		return false;
	} 

	//check surrounding spaces
	//TODO segfault happening because we are indexing out of the matrix here. Need to check that checkSpace is in the matrix before using it to index each time can't think of a non ugly way to do it right now 
	checkSpace = move + N;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= NORTH; 
	} 
	checkSpace = move + NE;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= NORTHEAST; 
	} 
	checkSpace = move + E;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= EAST; 
	} 
	checkSpace = move + SE;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= SOUTHEAST; 
	} 
	checkSpace = move + S;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= SOUTH; 
	} 
	checkSpace = move + SW;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= SOUTHWEST; 
	} 
	checkSpace = move + W;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= WEST; 
	} 
	checkSpace = move + NW;
	if(myGame->board[checkSpace.first][checkSpace.second]->token == getOpponentToken(myGame)){
		myGame->board[move.first][move.second]->moveDirs |= NORTHWEST; 
	} 

	if(!myGame->board[move.first][move.second]->moveDirs){
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
