#ifndef GAME_H_
#define GAME_H_

#include "board.h"

#define R_ROCK			2
#define P_PAPER			5
#define S_SCISSORS		1
#define B_BOMB			2
#define J_JOKER			2
#define F_FLAG			1

#define CODE_UNKNOWN		0
#define CODE_ALL_CAPTURED	1
#define CODE_ALL_EATEN		2
#define CODE_TIE_NO_MORE_MOVES	3
#define CODE_TIE_ALL_EATEN	4
#define CODE_BAD_POSITION_1	5
#define CODE_BAD_POSITION_2	6
#define CODE_BAD_POSITION_BOTH	7
#define CODE_BAD_MOVES_1	8
#define CODE_BAD_MOVES_2	9

#define ERROR_MOVE_FROM		"ERROR: You cannot move your piece from "
#define ERROR_MOVE_TO		" to "

class Game {
private:
	int current_player; // 0=first player, 1=second player
	Board* board_0;
	Board* board_1;
public:
	Game(); // Default constructor (override the compiler's default constructor)
	~Game(); // Destructor
	Game & operator=(const Game&) = delete; // Block assignment operator

	int getCurrentPlayer() {
		return current_player;
	}
	void changePlayer() {
		current_player = 1 - current_player;
	}
	char getPiece(int x, int y);
	int positioning(char piece, int x, int y, int is_joker); // Put a new piece to the current player board, Return 0 if success and 1 otherwise
	int jokerCommand(char piece, int x, int y); // Perform a joker command from the moves file, Return 0 on success and 1 otherwise
	int doMove(int from_x, int from_y, int to_x, int to_y); // Try to make a move for the current player, Return 0 on success and 1 otherwise
	void checkWinner(int& winner, int& reason); // The function check if we have a winner
	void compareBoards();
	void fight(char piece_0, char piece_1, int x, int y); // Fight function is called ONLY if (x,y) at both boards isn't empty
	int flagsCounter();
};

#endif /* GAME_H_ */
