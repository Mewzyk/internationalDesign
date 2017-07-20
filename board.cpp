/* board.cpp 
 * Last edit 7/20 bbaltaxe
 */


#include <iostream>
#include <stdexcept>
#include <unistd.h>

using namespace std;


#define BOARD_TEST

enum {
	player1,
	player2
};

struct TileInfo{
	int moveDirs; 
	char token;
};

typedef TileInfo * Tile;

struct GameInfo{
	int turn; 
	char p1Token; 
	char p2Token; 
	Tile board[8][8];
};

typedef GameInfo * Game;

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
		}
	}

	//set center pieces in place
	myGame->board[3][4]->token = myGame->p1Token;
	myGame->board[4][3]->token = myGame->p1Token;
	myGame->board[3][3]->token = myGame->p2Token;	
	myGame->board[4][4]->token = myGame->p2Token;


	return myGame;
}

void printBoard(Game myGame){
	char A = 'A';
	
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

#ifdef BOARD_TEST
int main (int argc, char** argv) {
	cout << "---Board-Test---" << endl;
	Game myGame = newGame();
/*	char test;
	cout << "Player 1, please choose a game piece:";
	cin.get(test);
	cout << "this was chosen" << endl << test << endl;	
*/
	cout << "player 1 chose: " << myGame->p1Token << endl;
	cout << "player 2 chose: " << myGame->p2Token << endl;
	
	cout << "---board maybe follows" << endl;
	
	printBoard(myGame);

	return 0;
}
#endif //BOARD_TEST
