#ifndef BOARD_H_
#define BOARD_H_

#define N_ROWS			10
#define M_COLS			10
#define EMPTY			' '
#define ROCK			'R'
#define PAPER			'P'
#define SCISSORS		'S'
#define BOMB			'B'
#define FLAG			'F'
#define JOKER			'J'
#define JOKER_ROCK		'0'
#define JOKER_PAPER		'1'
#define JOKER_SCISSORS		'2'
#define JOKER_BOMB		'3'

#define ERROR_CHANGE_JOKER	"ERROR: You cannot change piece of type "
#define ERROR_CHANGE_PIECE	"ERROR: You cannot change your joker to be "
#define ERROR_COUNT_BOMB	"ERROR: There are too many bombs"
#define ERROR_COUNT_FLAG	"ERROR: There are too many flags"
#define ERROR_COUNT_JOKER	"ERROR: There are too many jokers"
#define ERROR_COUNT_PAPER	"ERROR: There are too many papers"
#define ERROR_COUNT_ROCK	"ERROR: There are too many rocks"
#define ERROR_COUNT_SCISSORS	"ERROR: There are too many scissors"
#define ERROR_INVALID_JOKER	"ERROR: Invalid joker type "
#define ERROR_INVALID_PIECE	"ERROR: Invalid piece type "
#define ERROR_MOVE_EMPTY	"ERROR: You don't have any piece at your selected start location"
#define ERROR_MOVE_FLAGS_BOMBS	"ERROR: You can't move flag or bomb pieces"
#define ERROR_MOVE_LIMITATION	"ERROR: You can only move left, right, up and down"
#define ERROR_MOVE_TAKEN	"ERROR: You're trying to move to a location that's already taken by you"
#define ERROR_OUT_OF_RANGE	"' is out of range"
#define ERROR_SAME_POSITION	"ERROR: Two or more PIECEs (of same player) are positioned at the same location"
#define ERROR_X			"ERROR: X coordinate '"
#define ERROR_X_DESTINATION	"ERROR: Destination X coordinate '"
#define ERROR_X_SOURCE		"ERROR: Source X coordinate '"
#define ERROR_Y			"ERROR: Y coordinate '"
#define ERROR_Y_DESTINATION	"ERROR: Destination Y coordinate '"
#define ERROR_Y_SOURCE		"ERROR: Source Y coordinate '"

class Board {
private:
	int count_rock;
	int count_paper;
	int count_scissors;
	int count_bomb;
	int count_joker;
	int count_joker_rock;
	int count_joker_paper;
	int count_joker_scissors;
	int count_joker_bomb;
	int count_flag;
	int max_rock;
	int max_paper;
	int max_scissors;
	int max_bomb;
	int max_joker;
	int max_flag;
	char board[N_ROWS][M_COLS];
public:
	Board() = delete; // Block default constructor
	Board(int max_r, int max_p, int max_s, int max_b, int max_j, int max_f); // constructor
	// The default destructor is enough (there arn't pointer fields)
	Board & operator=(const Board&) = delete; // Block assignment operator

	// Get piece at (x,y)
	char getPiece(int x, int y) {
		return board[x-1][y-1];
	}
	// Return how many flags are in the board
	int getFlagCounter() {
		return count_flag;
	}
	int move(int x_from, int y_from, int x_to, int y_to); // Move piece from (x_from,y_from) to (x_to,y_to), Return 0 on success and 1 otherwise
	int changeJoker(char piece, int x, int y); // Change the joker at (x,y) to the new representation, Return 0 on success and 1 otherwise
	int pieceCounter(char piece); // Return how many pieces of selected type are in the board, Return -1 for invalid input
	int validation(char piece, int x, int y, int is_joker); // The funcrion validate that the piece can be entered to the board, Return 0 if valid and 1 otherwise
	int positioning(char piece, int x, int y, int is_joker); // Put a new piece to the board, Return 0 if success and 1 otherwise
	void killPiece(int x, int y);
	int checkGameOver(); // Function to check if there are pieces that can move, Return 0 if there are any movable pieces and 1 otherwise
	char printPiece(int x, int y);
};

#endif /* BOARD_H_ */
