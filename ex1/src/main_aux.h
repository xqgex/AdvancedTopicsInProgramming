#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_

#include "game.h"

#define FILE_BOARD_PLAYER_1		"player1.rps_board"
#define FILE_BOARD_PLAYER_2		"player2.rps_board"
#define FILE_MOVES_PLAYER_1		"player1.rps_moves"
#define FILE_MOVES_PLAYER_2		"player2.rps_moves"
#define FILE_OUTPUT			"rps.output"

#define MSG_ALL_CAPTURED		"All flags of the opponent are captured"
#define MSG_ALL_EATEN			"All moving PIECEs of the opponent are eaten"
#define MSG_BAD_MOVES_1			"Bad Moves input file for player 1 - line "
#define MSG_BAD_MOVES_2			"Bad Moves input file for player 2 - line "
#define MSG_BAD_POSITION_1		"Bad Positioning input file for player 1 - line "
#define MSG_BAD_POSITION_2		"Bad Positioning input file for player 2 - line "
#define MSG_BAD_POSITION_BOTH_A		"Bad Positioning input file for both players - player 1: line "
#define MSG_BAD_POSITION_BOTH_B		", player 2: line "
#define MSG_OUTPUT_REASON		"Reason: "
#define MSG_OUTPUT_WINNER		"Winner: "
#define MSG_TIE_ALL_EATEN		"A tie - all flags are eaten by both players in the position files"
#define MSG_TIE_NO_MORE_MOVES		"A tie - both Moves input files done without a winner"

#define ERROR_ARGS_MANY			"ERROR: There are too many arguments"
#define ERROR_ARGS_MANY_FOR_JOKER	"ERROR: There are too many arguments for non joker move"
#define ERROR_ARGS_MANY_FOR_PIECE	"ERROR: There are too many arguments for joker move"
#define ERROR_ARGS_MANY_OR_INVALID	"ERROR: There are too many arguments or you have enter invalid char as a piece"
#define ERROR_ARGS_MISSING		"ERROR: You have not completed all the necessary arguments"
#define ERROR_AT			" at "
#define ERROR_GENERAL			"ERROR: '"
#define ERROR_INVALID_JOKER_COMMAND	"ERROR: Invalid joker command"
#define ERROR_INVALID_JOKER_FORMAT	"ERROR: Invalid format for the joker"
#define ERROR_INVALID_JOKER_PIECE	"ERROR: Invalid piece"
#define ERROR_INVALID_LINE		"ERROR: Invalid line format"
#define ERROR_INVALID_MOVE		"ERROR: Invalid move command"
#define ERROR_INVALID_POSITIONING	"ERROR: Found invalid positioning line"
#define ERROR_INVALID_X			"ERROR: Invalid X coordinate"
#define ERROR_INVALID_X_FROM		"ERROR: Invalid X_FROM coordinate"
#define ERROR_INVALID_X_TO		"ERROR: Invalid X_TO coordinate"
#define ERROR_INVALID_Y			"ERROR: Invalid Y coordinate"
#define ERROR_INVALID_Y_FROM		"ERROR: Invalid Y_FROM coordinate"
#define ERROR_INVALID_Y_TO		"ERROR: Invalid Y_TO coordinate"
#define ERROR_IS_INVALID		" is invalid"
#define ERROR_LINE			"ERROR: Line "
#define ERROR_NO_FLAGS			"ERROR: There must be at least one flag"
#define ERROR_NO_MORE_MOVES1		"ERROR: Player1 don't have any more moves"
#define ERROR_NO_MORE_MOVES2		"ERROR: Player2 don't have any more moves"
#define ERROR_NOT_CHAR			"' is invalid char"
#define ERROR_NOT_NUMBER		"' isn't a number"
#define ERROR_POSITIONING_FAILED	"ERROR: Couldn't put the piece "

// Convert string to int, Return 0 on seccess and 1 otherwise
int strToInt(string& source, int& destination);

// Compare between two integer for validation (0 is valid), Return winner and reason information
void positioningWinByError(int& winner, int& reason, int res_1, int res_2);

// The funcrion parse an initial board line, Return 0 if valid, 1 if invalid and -1 if the line is empty
int parsePositionLine(string& line, char& piece, int& x, int& y, int& is_joker);

// The funcrion parse move line, Return 0 if valid and 1 otherwise
int parseMoveLine(string& line, int& from_x, int& from_y, int& to_x, int& to_y, int& joker_x, int& joker_y, char& new_rep, int& change_joker);

// Add player pieces to board, Return 0 on success or the number of the invalid line
int initGameByFile(Game* game, ifstream& init_file); // $$The function change the current player before exit$$

void printBoard(Game* game, ofstream& output_file);

void printToOutputFile(Game* game, ofstream& output_file, int winner, int reason, int res_1, int res_2);

// perform a single move from the selected file to the current player, Return 0 if success, -2 on EOF and -1 otherwise
int takeMove(Game* game, ifstream& moves_player); // $$The function change the current player before exit$$

// The function run the moves files line by line, Return  0 on tie, 1 if player1 win and 2 if player2 win
void playGame(Game* game, ifstream& moves_player_1, ifstream& moves_player_2, int& winner, int& reason, int& counter);

#endif /* MAIN_AUX_H_ */
