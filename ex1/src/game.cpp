#include <iostream>	// cout, endl, tolower, toupper
using namespace std;
#include "game.h"

Game::Game() {
	current_player = 0;
	board_0 = new Board(R_ROCK,P_PAPER,S_SCISSORS,B_BOMB,J_JOKER,F_FLAG);
	board_1 = new Board(R_ROCK,P_PAPER,S_SCISSORS,B_BOMB,J_JOKER,F_FLAG);
}

Game::~Game() {
	delete board_0;
	delete board_1;
}

char Game::getPiece(int x, int y) {
	char player_0 = board_0->printPiece(x,y); // 1<=x<=M 1<=y<=N
	char player_1;
	if (player_0!=EMPTY) {
		return toupper(player_0);
	}
	player_1 = board_1->printPiece(x,y); // 1<=x<=M 1<=y<=N
	return tolower(player_1);
}

// Put a new piece to the current player board, Return 0 if success and 1 otherwise
int Game::positioning(char piece, int x, int y, int is_joker) { // 1<=x<=M 1<=y<=N
	if (getCurrentPlayer()==0) {
		return board_0->positioning(piece,x,y,is_joker); // positioning() Return 0 if success and 1 otherwise
	} else {
		return board_1->positioning(piece,x,y,is_joker); // positioning() Return 0 if success and 1 otherwise
	}
}

// Perform a joker command from the moves file, Return 0 on success and 1 otherwise
int Game::jokerCommand(char piece, int x, int y) { // 1<=x<=M 1<=y<=N
	int player = getCurrentPlayer();
	if (player==0) {
		return board_0->changeJoker(piece,x,y); // changeJoker() Return 0 on success and 1 otherwise
	} else {
		return board_1->changeJoker(piece,x,y); // changeJoker() Return 0 on success and 1 otherwise
	}
}

// Try to make a move for the current player, Return 0 on success and 1 otherwise
int Game::doMove(int from_x,int from_y,int to_x,int to_y) {
	int res;
	if (getCurrentPlayer()==0) { // It's Player 0 turn to make a move
		res = board_0->move(from_x,from_y,to_x,to_y); // move() Return 0 on success and 1 otherwise
	} else {
		res = board_1->move(from_x,from_y,to_x,to_y); // move() Return 0 on success and 1 otherwise
	}
	if (res==1) { // The move was invalid
		cout << ERROR_MOVE_FROM << "(" << from_x << "," << from_y << ")" << ERROR_MOVE_TO << "(" << to_x << "," << to_y << ")" << endl; // "ERROR: You cannot move your piece from (?,?) to (?,?)"
		return 1;
	} else {
		compareBoards(); // Check if we need to fight
		return 0;
	}
}

// The function check if we have a winner
void Game::checkWinner(int& winner, int& reason) { // winner = -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
	int player_0_status = board_0->checkGameOver(); // checkGameOver() Return 0 if there are any movable pieces and 1 otherwise
	int player_1_status = board_1->checkGameOver(); // checkGameOver() Return 0 if there are any movable pieces and 1 otherwise
	int player_0_flags = board_0->getFlagCounter(); // Return how many flags are in the board
	int player_1_flags = board_1->getFlagCounter(); // Return how many flags are in the board
	if ((player_0_flags==0)&&(player_1_flags==0)) { // All flags of the opponent are captured
		reason = CODE_TIE_ALL_EATEN;
		winner = 0; // Tie
	} else if (player_0_flags==0) {
		reason = CODE_ALL_CAPTURED;
		winner = 2; // Player 1 win
	} else if (player_1_flags==0) {
		reason = CODE_ALL_CAPTURED;
		winner = 1; // Player 0 win
	} else if ((player_0_status==1)&&(player_1_status==1)) { // Check if there are pieces that can move
		reason = CODE_TIE_NO_MORE_MOVES;
		winner = 0; // Tie
	} else if (player_0_status==1) {
		reason = CODE_ALL_EATEN;
		winner = 2; // Player 1 win
	} else if (player_1_status==1) {
		reason = CODE_ALL_EATEN;
		winner = 1; // Player 0 win
	} else {
		reason = CODE_UNKNOWN;
		winner = -1; // Game still on
	}
	return;
}

void Game::compareBoards() {
	int i,j; // 1<=i<=M 1<=j<=N
	char player_0,player_1;
	for (i=1;i<=M_COLS;i++) {
		for (j=1;j<=N_ROWS;j++) {
			player_0 = board_0->getPiece(i,j); // 1<=i<=M 1<=j<=N
			player_1 = board_1->getPiece(i,j); // 1<=i<=M 1<=j<=N
			if ((player_0!=EMPTY)&&(player_1!=EMPTY)) { // We have a fight
				fight(player_0,player_1,i,j);
			}
		}
	}
}

// Fight function is called ONLY if (x,y) at both boards isn't empty
void Game::fight(char piece_0, char piece_1, int x, int y) {
//						Player 0
//			R	P	S	B	F	J_R	J_P	J_S	J_B
//		R	B	0	1	B	1	B	0	1	B
//		P	1	B	0	B	1	1	B	0	B
//		S	0	1	B	B	1	0	1	B	B
//		B	B	B	B	B	B	B	B	B	B
// player 1	F	1	1	1	B	B	1	1	1	B
//		J_R	B	0	1	B	1	B	0	1	B
//		J_P	1	B	0	B	1	1	B	0	B
//		J_S	0	1	B	B	1	0	1	B	B
//		J_B	B	B	B	B	B	B	B	B	B
	int player_0_lose = 1;
	int player_1_lose = 1;
	switch (piece_0) {
		case ROCK: case JOKER_ROCK: // ROCK can survive only SCISSORS & JOKER_SCISSORS & FLAG
			if ((piece_1==SCISSORS)||(piece_1==JOKER_SCISSORS)||(piece_1==FLAG)) {
				player_0_lose = 0;
			}
			break;
		case PAPER: case JOKER_PAPER: // PAPER can survive only ROCK & JOKER_ROCK & FLAG
			if ((piece_1==ROCK)||(piece_1==JOKER_ROCK)||(piece_1==FLAG)) {
				player_0_lose = 0;
			}
			break;
		case SCISSORS: case JOKER_SCISSORS: // SCISSORS can survive only PAPER & JOKER_PAPER & FLAG
			if ((piece_1==PAPER)||(piece_1==JOKER_PAPER)||(piece_1==FLAG)) {
				player_0_lose = 0;
			}
			break;
	}
	switch (piece_1) {
		case ROCK: case JOKER_ROCK: // ROCK can survive only SCISSORS & JOKER_SCISSORS & FLAG
			if ((piece_0==SCISSORS)||(piece_0==JOKER_SCISSORS)||(piece_0==FLAG)) {
				player_1_lose = 0;
			}
			break;
		case PAPER: case JOKER_PAPER: // PAPER can survive only ROCK & JOKER_ROCK & FLAG
			if ((piece_0==ROCK)||(piece_0==JOKER_ROCK)||(piece_0==FLAG)) {
				player_1_lose = 0;
			}
			break;
		case SCISSORS: case JOKER_SCISSORS: // SCISSORS can survive only PAPER & JOKER_PAPER & FLAG
			if ((piece_0==PAPER)||(piece_0==JOKER_PAPER)||(piece_0==FLAG)) {
				player_1_lose = 0;
			}
			break;
	}
	if (player_0_lose==1) {
		board_0->killPiece(x,y); // 1<=x<=M 1<=y<=N
	}
	if (player_1_lose==1) {
		board_1->killPiece(x,y); // 1<=x<=M 1<=y<=N
	}
}

// Count how many flags the current player have
int Game::flagsCounter(){
	if (current_player) {
		return board_1->getFlagCounter(); // Return how many flags are in the board
	} else {
		return board_0->getFlagCounter(); // Return how many flags are in the board
	}
}

