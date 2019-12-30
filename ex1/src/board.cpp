#include <iostream>	// cout, endl
using namespace std;
#include "board.h"

Board::Board(int max_r, int max_p, int max_s, int max_b, int max_j, int max_f) {
	int i,j;
	count_rock = 0;
	count_paper = 0;
	count_scissors = 0;
	count_bomb = 0;
	count_joker = 0;
	count_joker_rock = 0;
	count_joker_paper = 0;
	count_joker_scissors = 0;
	count_joker_bomb = 0;
	count_flag = 0;
	max_rock = max_r;
	max_paper = max_p;
	max_scissors = max_s;
	max_bomb = max_b;
	max_joker = max_j;
	max_flag = max_f;
	for (i=0;i<M_COLS;i++) { // 0<=i<=M-1 0<=j<=N-1
		for (j=0;j<N_ROWS;j++) {
			board[i][j] = EMPTY;
		}
	}
}

// Move piece from (x_from,y_from) to (x_to,y_to), Return 0 on success and 1 otherwise
int Board::move(int x_from, int y_from, int x_to, int y_to) {
	if ((x_from<1)||(x_from>M_COLS)) {
		cout << ERROR_X_SOURCE << x_from << ERROR_OUT_OF_RANGE << endl; // "ERROR: Source X coordinate '?' is out of range"
		return 1;
	}
	if ((x_to<1)||(x_to>M_COLS)) {
		cout << ERROR_X_DESTINATION << x_to << ERROR_OUT_OF_RANGE << endl; // "ERROR: Destination X coordinate '?' is out of range"
		return 1;
	}
	if ((y_from<1)||(y_from>N_ROWS)) {
		cout << ERROR_Y_SOURCE << y_from << ERROR_OUT_OF_RANGE << endl; // "ERROR: Source Y coordinate '?' is out of range"
		return 1;
	}
	if ((y_to<1)||(y_to>N_ROWS)) {
		cout << ERROR_Y_DESTINATION << y_to << ERROR_OUT_OF_RANGE << endl; // "ERROR: Destination Y coordinate '?' is out of range"
		return 1;
	}
	if ((y_to==y_from+1)||(y_to==y_from-1)) {
		if (x_to!=x_from) {
			cout << ERROR_MOVE_LIMITATION << endl; // "ERROR: You can only move left, right, up and down"
			return 1;
		}
	} else if ((x_to==x_from+1)||(x_to==x_from-1)) {
		if(y_to!=y_from) {
			cout << ERROR_MOVE_LIMITATION << endl; // "ERROR: You can only move left, right, up and down"
			return 1;
		}
	} else { // This will also catch if ((x_from==x_to)&&(y_from==y_to))
		cout << ERROR_MOVE_LIMITATION << endl; // "ERROR: You can only move left, right, up and down"
		return 1;
	}
	if (board[x_from-1][y_from-1]==EMPTY) {
		cout << ERROR_MOVE_EMPTY << endl; // "ERROR: You don't have any piece at your selected start location"
		return 1;
	}
	if (board[x_to-1][y_to-1]!=EMPTY) {
		cout << ERROR_MOVE_TAKEN << endl; // "ERROR: You're trying to move to a location that's already taken by you"
		return 1;
	}
	if ((board[x_from-1][y_from-1]==FLAG)||(board[x_from-1][y_from-1]==BOMB)||(board[x_from-1][y_from-1]==JOKER_BOMB)) {
		cout << ERROR_MOVE_FLAGS_BOMBS << endl; // "You can't move flag or bomb pieces"
		return 1;
	}
	board[x_to-1][y_to-1] = getPiece(x_from,y_from);
	board[x_from-1][y_from-1] = EMPTY;
	return 0; // The move success
}

// Change the joker at (x,y) to the new representation, Return 0 on success and 1 otherwise
int Board::changeJoker(char piece, int x, int y) { // 1<=x<=M 1<=y<=N
	char new_piece;
	char old_piece = getPiece(x,y);
	if ((x<1)||(x>M_COLS)) {
		cout << ERROR_X << x << ERROR_OUT_OF_RANGE << endl; // "ERROR: X coordinate '?' is out of range"
		return 1;
	}
	if ((y<1)||(y>N_ROWS)) {
		cout << ERROR_Y << y << ERROR_OUT_OF_RANGE << endl; // "ERROR: Y coordinate '?' is out of range"
		return 1;
	}
	switch (old_piece) {
		case JOKER_ROCK: count_joker_rock--;
			break;
		case JOKER_PAPER: count_joker_paper--;
			break;
		case JOKER_SCISSORS: count_joker_scissors--;
			break;
		case JOKER_BOMB: count_joker_bomb--;
			break;
		default: cout << ERROR_CHANGE_PIECE << old_piece << endl; // "ERROR: You cannot change piece of type "
			return 1; // Invalid piece
			break;
	}
	switch (piece) {
		case ROCK: count_joker_rock++;
			new_piece = JOKER_ROCK;
			break;
		case PAPER: count_joker_paper++;
			new_piece = JOKER_PAPER;
			break;
		case SCISSORS: count_joker_scissors++;
			new_piece = JOKER_SCISSORS;
			break;
		case BOMB: count_joker_bomb++;
			new_piece = JOKER_BOMB;
			break;
		default: cout << ERROR_CHANGE_JOKER << piece << endl; // "ERROR: You cannot change your joker to be "
			return 1; // Invalid piece
			break;
	}
	board[x-1][y-1] = new_piece;
	return 0;
}

// The funcrion validate that the piece can be entered to the board, Return 0 if valid and 1 otherwise
int Board::validation(char piece, int x, int y, int is_joker) {
	if ((x<1)||(x>M_COLS)) {
		cout << ERROR_X << x << ERROR_OUT_OF_RANGE << endl; // "ERROR: X coordinate '?' is out of range"
		return 1;
	}
	if ((y<1)||(y>N_ROWS)) {
		cout << ERROR_Y << y << ERROR_OUT_OF_RANGE << endl; // "ERROR: Y coordinate '?' is out of range"
		return 1;
	}
	if (board[x-1][y-1]!=EMPTY) {
		cout << ERROR_SAME_POSITION << endl; // "ERROR: Two or more PIECEs (of same player) are positioned at the same location"
		return 1;
	}
	if (is_joker) {
		if ((piece!=ROCK)&&(piece!=PAPER)&&(piece!=SCISSORS)&&(piece!=BOMB)) {
			cout << ERROR_INVALID_JOKER << piece << endl; // "ERROR: Invalid joker type "
			return 1;
		}
		if (count_joker>=max_joker) {
			cout << ERROR_COUNT_JOKER << endl; // "ERROR: There are too many jokers"
			return 1;
		}
	} else {
		switch (piece) {
			case ROCK: if (count_rock>=max_rock) {
					cout << ERROR_COUNT_ROCK << endl; // "ERROR: There are too many rocks"
					return 1;
				}
				break;
			case PAPER: if (count_paper>=max_paper) {
					cout << ERROR_COUNT_PAPER << endl; // "ERROR: There are too many papers"
					return 1;
				}
				break;
			case SCISSORS: if (count_scissors>=max_scissors) {
					cout << ERROR_COUNT_SCISSORS << endl; // "ERROR: There are too many scissors"
					return 1;
				}
				break;
			case BOMB: if (count_bomb>=max_bomb) {
					cout << ERROR_COUNT_BOMB << endl; // "ERROR: There are too many bombs"
					return 1;
				}
				break;
			case FLAG: if (count_flag>=max_flag) {
					cout << ERROR_COUNT_FLAG << endl; // "ERROR: There are too many flags"
					return 1;
				}
				break;
			default: cout << ERROR_INVALID_PIECE << piece << endl; // "ERROR: Invalid piece type "
				return 1;
				break;
		}
	}
	return 0;
}

// Put a new piece to the board, Return 0 if success and 1 otherwise
int Board::positioning(char piece, int x, int y, int is_joker) {
	if (validation(piece,x,y,is_joker)==0) { // validation() Return 0 if valid and 1 otherwise
		if (is_joker==0) {
			board[x-1][y-1] = piece;
			switch (piece) {
				case ROCK: count_rock++;
					break;
				case PAPER: count_paper++;
					break;
				case SCISSORS: count_scissors++;
					break;
				case BOMB: count_bomb++;
					break;
				case FLAG: count_flag++;
					break;
			}
		} else {
			count_joker++;
			switch (piece) {
				case ROCK: board[x-1][y-1] = JOKER_ROCK;
					count_joker_rock++;
					break;
				case PAPER: board[x-1][y-1] = JOKER_PAPER;
					count_joker_paper++;
					break;
				case SCISSORS: board[x-1][y-1] = JOKER_SCISSORS;
					count_joker_scissors++;
					break;
				case BOMB: board[x-1][y-1] = JOKER_BOMB;
					count_joker_bomb++;
					break;
			}
		}
		return 0;
	} else {
		return 1;
	}
}

void Board::killPiece(int x, int y) {
	char piece = board[x-1][y-1];
	switch (piece) {
		case ROCK: count_rock--;
			break;
		case PAPER: count_paper--;
			break;
		case SCISSORS: count_scissors--;
			break;
		case BOMB: count_bomb--;
			break;
		case FLAG: count_flag--;
			break;
		case JOKER_ROCK: count_joker_rock--;
			count_joker--;
			break;
		case JOKER_PAPER: count_joker_paper--;
			count_joker--;
			break;
		case JOKER_SCISSORS: count_joker_scissors--;
			count_joker--;
			break;
		case JOKER_BOMB: count_joker_bomb--;
			count_joker--;
			break;
	}
	board[x-1][y-1] = EMPTY;
}

// Function to check if there are pieces that can move, Return 0 if there are any movable pieces and 1 otherwise
int Board::checkGameOver(){
	if ((!count_rock)&&(!count_paper)&&(!count_scissors)&&(!count_joker_rock)&&(!count_joker_paper)&&(!count_joker_scissors)) {
		return 1; // There are only flags and bombs in the board
	} else {
		return 0;
	}
}

char Board:: printPiece(int x, int y) {
	char piece = getPiece(x, y);
	if (piece == JOKER_BOMB || piece == JOKER_PAPER || piece == JOKER_ROCK || piece == JOKER_SCISSORS) {
		return JOKER;
	}
	return piece;
}
