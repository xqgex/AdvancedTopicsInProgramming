/*
 * GameParameters.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: General parameters of the game and constants.
 */
#ifndef GAMEPARAMETERS_H_
#define GAMEPARAMETERS_H_

#define FILE_BOARD_PLAYER_1	"player1.rps_board"
#define FILE_BOARD_PLAYER_2	"player2.rps_board"
#define FILE_MOVES_PLAYER_1	"player1.rps_moves"
#define FILE_MOVES_PLAYER_2	"player2.rps_moves"
#define FILE_OUTPUT		"rps.output"

#define R_ROCK			2
#define P_PAPER			5
#define S_SCISSORS		1
#define B_BOMB			2
#define J_JOKER			2
#define F_FLAG			1
#define N_ROWS			10
#define M_COLS			10
#define NO_FIGHTS		100
#define NUMBER_OF_GAMES		30

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
#define NOT_JOKER		'#'

#define UNKNOWN			'?'
#define MOVABLE			'!'

#define REASON_UNKNOWN			0
#define REASON_ALL_CAPTURED		1
#define REASON_ALL_EATEN		2
#define REASON_TIE_NO_MORE_MOVES	3
#define REASON_TIE_ALL_EATEN		4
#define REASON_BAD_POSITION_1		5
#define REASON_BAD_POSITION_2		6
#define REASON_BAD_POSITION_BOTH	7
#define REASON_BAD_MOVES		8

#define ERROR_ARGS_MANY			"ERROR: There are too many arguments"
#define ERROR_ARGS_MANY_FOR_JOKER	"ERROR: There are too many arguments for joker move"
#define ERROR_ARGS_MANY_FOR_PIECE	"ERROR: There are too many arguments for non joker move"
#define ERROR_ARGS_MANY_OR_INVALID	"ERROR: There are too many arguments or you have enter invalid char as a piece"
#define ERROR_ARGS_MISSING		"ERROR: You have not completed all the necessary arguments"
#define ERROR_AT			"' at "
#define ERROR_BAD_MOVE_B		" did invalid move"
#define ERROR_CHANGE_JOKER		"ERROR: You cannot change piece of type "
#define ERROR_CHANGE_PIECE		"ERROR: You cannot change your joker to be "
#define ERROR_COUNT_BOMB		"ERROR: There are too many bombs"
#define ERROR_COUNT_FLAG		"ERROR: There are too many flags"
#define ERROR_COUNT_JOKER		"ERROR: There are too many jokers"
#define ERROR_COUNT_PAPER		"ERROR: There are too many papers"
#define ERROR_COUNT_ROCK		"ERROR: There are too many rocks"
#define ERROR_COUNT_SCISSORS		"ERROR: There are too many scissors"
#define ERROR_DESTINATION_TAKEN		"ERROR: You already have piece at the destination"
#define ERROR_FAILED_LOAD_SO		"ERROR: Failed to load .so file - "
#define ERROR_GAME_ENDED_POSITIONING	"The game ended in failure during positioning"
#define ERROR_GENERAL			"ERROR: '"
#define ERROR_INVALID_ARGS		"ERROR: Invalid arguments"
#define ERROR_INVALID_JOKER		"ERROR: Invalid joker type '"
#define ERROR_INVALID_JOKER_COMMAND	"ERROR: Invalid joker command"
#define ERROR_INVALID_JOKER_FORMAT	"ERROR: Invalid format for the joker"
#define ERROR_INVALID_JOKER_PIECE	"ERROR: Invalid piece"
#define ERROR_INVALID_LINE		"ERROR: Invalid line format"
#define ERROR_INVALID_MOVE		"ERROR: Invalid move command"
#define ERROR_INVALID_PIECE		"ERROR: Invalid piece type "
#define ERROR_INVALID_POSITIONING	"ERROR: Found invalid positioning line"
#define ERROR_INVALID_X			"ERROR: Invalid X coordinate"
#define ERROR_INVALID_X_FROM		"ERROR: Invalid X_FROM coordinate"
#define ERROR_INVALID_X_TO		"ERROR: Invalid X_TO coordinate"
#define ERROR_INVALID_Y			"ERROR: Invalid Y coordinate"
#define ERROR_INVALID_Y_FROM		"ERROR: Invalid Y_FROM coordinate"
#define ERROR_INVALID_Y_TO		"ERROR: Invalid Y_TO coordinate"
#define ERROR_IS_INVALID		" is invalid"
#define ERROR_LINE			"ERROR: Line "
#define ERROR_MISSING_SO_FILES		"ERROR: Add more .so files and then run the program again."
#define ERROR_MOVE_EMPTY		"ERROR: You don't have any piece at your selected start location"
#define ERROR_MOVE_FLAGS_BOMBS		"ERROR: You can't move flag or bomb pieces"
#define ERROR_MOVE_FROM			"ERROR: You cannot move your piece from "
#define ERROR_MOVE_LIMITATION		"ERROR: You can only move left, right, up and down"
#define ERROR_MOVE_OPPONENT_A		"ERROR: You cannot move your opponent, You are "
#define ERROR_MOVE_OPPONENT_B		" and he is "
#define ERROR_MOVE_TAKEN		"ERROR: You're trying to move to a location that's already taken by you"
#define ERROR_MOVE_TO			" to "
#define ERROR_NO_FIGHT			"ERROR: Game ended after 100 moves without a fight"
#define ERROR_NO_FLAGS_B		" - There must be at least one flag"
#define ERROR_NO_JOKER			"ERROR: You don't have joker at the selected destination"
#define ERROR_NO_MORE_MOVES_B		" don't have any more moves"
#define ERROR_NOT_CHAR			"' is invalid char"
#define ERROR_NOT_NUMBER		"' isn't a number"
#define ERROR_OPEN_BOARD		" board file ('"
#define ERROR_OPEN_ENDL			"')"
#define ERROR_OPEN_MOVE			" move file ('"
#define ERROR_OPEN_PLAYER		"Failed to open player "
#define ERROR_OUT_OF_RANGE		"' is out of range"
#define ERROR_PLAYER_NUM		"ERROR: Player "
#define ERROR_POSITIONING_FAILED_B	" - Couldn't put the piece '"
#define ERROR_SAME_POSITION		"ERROR: Two or more PIECEs (of same player) are positioned at the same location"
#define ERROR_SHARED_LIB		"ERROR: RSPPlayer '"
#define ERROR_SHARED_LIB_B		"' already been loaded"
#define ERROR_USAGE			"Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
#define ERROR_X				"ERROR: X coordinate '"
#define ERROR_X_DESTINATION		"ERROR: Destination X coordinate '"
#define ERROR_X_SOURCE			"ERROR: Source X coordinate '"
#define ERROR_Y				"ERROR: Y coordinate '"
#define ERROR_Y_DESTINATION		"ERROR: Destination Y coordinate '"
#define ERROR_Y_SOURCE			"ERROR: Source Y coordinate '"

#define MSG_ALL_CAPTURED		"All flags of the opponent are captured"
#define MSG_ALL_EATEN			"All moving PIECEs of the opponent are eaten"
#define MSG_BAD_MOVES_1			"Bad Moves input file for player 1"
#define MSG_BAD_MOVES_2			"Bad Moves input file for player 2"
#define MSG_BAD_POSITION_1		"Bad Positioning input file for player 1"
#define MSG_BAD_POSITION_2		"Bad Positioning input file for player 2"
#define MSG_BAD_POSITION_BOTH		"Bad Positioning input file for both players"
#define MSG_DONE			"Done, Check the output file for more information"
#define MSG_NO_MORE_MOVES_BOTH		"Both players don't have any more moveable pieces"
#define MSG_OUTPUT_REASON		"Reason: "
#define MSG_OUTPUT_WINNER		"Winner: "
#define MSG_TIE_ALL_EATEN		"A tie - all flags are eaten by both players in the position files"
#define MSG_TIE_NO_MORE_MOVES		"A tie - both Moves input files done without a winner"

#endif /* GAMEPARAMETERS_H_ */
