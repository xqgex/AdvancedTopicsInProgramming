#include <cstdlib>	// atoi
#include <fstream>	// ifstream, ofstream, getline
#include <iostream>	// cout, endl
#include <sstream>	// istringstream
#include <string>	// c_str
using namespace std;
#include "main_aux.h"

// Convert string to int, Return 0 on success and 1 otherwise
int strToInt(string& source, int& destination) {
	unsigned i;
	for (i=0;i<source.length();i++) {
		if ((source[i]<'0')||(source[i]>'9')) {
			cout << ERROR_GENERAL << source << ERROR_NOT_NUMBER << endl; // "ERROR: '?' isn't a number"
			return 1; // This is not a number
		}
	}
	destination = atoi(source.c_str()); // Because we manually check 'atoi' input string, We can use her for the conversion (Instead of 'stoi')
	return 0;
}

// Compare between two integer for validation (0 is valid), Return winner and reason information
void positioningWinByError(int& winner, int& reason, int res_1, int res_2) {
	if ((res_1!=0)&&(res_2!=0)) { // Both players are invalid
		winner = 0; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
		reason = CODE_BAD_POSITION_BOTH;
	} else if (res_2!=0) { // Only player 2 have error
		winner = 1; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
		reason = CODE_BAD_POSITION_2;
	} else if (res_1!=0) { // Only player 1 have error
		winner = 2; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
		reason = CODE_BAD_POSITION_1;
	} else { // Both players are valid
		winner = -1; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
		reason = CODE_UNKNOWN;
	}
}

// The funcrion parse an initial board line, Return 0 if valid, 1 if invalid and -1 if the line is empty
int parsePositionLine(string& line, char& piece, int& x, int& y, int& is_joker) {
	int object_count = 0;
	int expected_count = 0;
	string splited_str;
	istringstream line_stream(line);
	is_joker = 0;
	while (getline(line_stream,splited_str,' ')) {
		if (splited_str.length()>0) { // Ignore double spaces
			if (splited_str[splited_str.size()-1]=='\r') { // In case the board file was created in WINDOWS
				splited_str.erase(splited_str.size() - 1); // We would have to remove the "\r" from the end of the line
			}
			switch (object_count) {
				case 0: if ((splited_str.length()!=1)||(splited_str[0]<'A')||(splited_str[0]>'Z')) {
						cout << ERROR_GENERAL << splited_str[0] << ERROR_NOT_CHAR << endl; // "ERROR: '?' is invalid char"
						return 1; // Invalid char
					} else if (splited_str[0]==JOKER) { // J <X> <Y> <PIECE_CHAR>
						is_joker = 1; // Found a joker
						expected_count = 4;
					} else { // <PIECE_CHAR> <X> <Y>
						piece = splited_str[0]; // Valid piece
						expected_count = 3;
					}
					break;
				case 1: if (strToInt(splited_str,x)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						cout << ERROR_INVALID_X << endl; // "ERROR: Invalid X coordinate"
						return 1; // Invalid input
					} // Valid <X>
					break;
				case 2: if (strToInt(splited_str,y)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						cout << ERROR_INVALID_Y << endl; // "ERROR: Invalid Y coordinate"
						return 1; // Invalid input
					} // Valid <Y>
					break;
				case 3: if ((is_joker==0)||(splited_str.length()!=1)||(splited_str[0]<'A')||(splited_str[0]>'Z')) {
						cout << ERROR_ARGS_MANY_OR_INVALID << endl; // "ERROR: There are too many arguments or you have enter invalid char as a piece"
						return 1; // Too many arguments or invalid piece
					} else {
						piece = splited_str[0]; // Valid piece
					}
					break;
				default: cout << ERROR_ARGS_MANY << endl; // "ERROR: There are too many arguments"
					return 1; // Too many arguments
					break;
			}
			object_count++;
		}
	}
	if (expected_count==0) {
		return -1; // Empty line
	} else if (expected_count==object_count) {
		return 0; // Valid
	} else {
		cout << ERROR_INVALID_POSITIONING << endl; // "ERROR: Found invalid positioning line"
		return 1; // Will return 1 if line didn't have all the fields
	}

}

// The funcrion parse move line, Return 0 if valid and 1 otherwise
int parseMoveLine(string& line, int& from_x, int& from_y, int& to_x, int& to_y, int& joker_x, int& joker_y, char& new_rep, int& change_joker) {
	int object_count = 0;
	int complete_move = 0;
	int complete_joker = 0;
	string splited_str;
	istringstream line_stream(line); // <FROM_X> <FROM_Y> <TO_X> <TO_Y> [J:   <Joker_X> <Joker_Y> <NEW_REP>]
	change_joker = 0;
	while (getline(line_stream,splited_str,' ')) {
		if (splited_str.length()>0) { // Ignore double spaces
			if (splited_str[splited_str.size()-1]=='\r') { // In case the move file was created in WINDOWS
				splited_str.erase(splited_str.size() - 1); // We would have to remove the "\r" from the end of the line
			}
			switch (object_count) {
				case 0: if (strToInt(splited_str,from_x)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						cout << ERROR_INVALID_X_FROM << endl; // "ERROR: Invalid X_FROM coordinate"
						return 1; // Invalid input
					} // Valid <FROM_X>
					break;
				case 1: if (strToInt(splited_str,from_y)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						cout << ERROR_INVALID_Y_FROM << endl; // "ERROR: Invalid Y_FROM coordinate"
						return 1; // Invalid input
					} // Valid <FROM_Y>
					break;
				case 2: if (strToInt(splited_str,to_x)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						cout << ERROR_INVALID_X_TO << endl; // "ERROR: Invalid X_TO coordinate"
						return 1; // Invalid input
					} // Valid <TO_X>
					break;
				case 3: if (strToInt(splited_str,to_y)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						cout << ERROR_INVALID_Y_TO << endl; // "ERROR: Invalid Y_TO coordinate"
						return 1; // Invalid input
					} // Valid <TO_Y>
					complete_move = 1;
					break;
				case 4: if ((splited_str.length()!=2)||(splited_str[0]!='J')||(splited_str[1]!=':')) {
						cout << ERROR_INVALID_JOKER_FORMAT << endl; // "ERROR: Invalid format for the joker"
						return 1; // Invalid input for the joker
					} else {
						change_joker = 1; // Found move of a joker
					}
					break;
				case 5: if (change_joker==0) {
							cout << ERROR_ARGS_MANY_FOR_JOKER << endl; // "ERROR: There are too many arguments for non joker move"
							return 1; // Too many arguments for non joker move
					} else {
						if (strToInt(splited_str,joker_x)==1) { // strToInt() Return 0 on seccess and 1 otherwise
							return 1; // Invalid input
						} // Valid <Joker_X>
					}
					break;
				case 6: if (strToInt(splited_str,joker_y)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						return 1; // Invalid input
					} // Valid <Joker_Y>
					break;
				case 7: if ((splited_str.length()!=1)||(splited_str[0]<'A')||(splited_str[0]>'Z')) {
						cout << ERROR_INVALID_JOKER_PIECE << endl; // "ERROR: Invalid piece"	
						return 1; // Invalid char
					} else {
						new_rep = splited_str[0]; // Joker <NEW_REP>
					}
					complete_joker = 1;
					break;
				default: cout << ERROR_ARGS_MANY_FOR_PIECE << endl; // "ERROR: There are too many arguments for joker move"
					return 1; // Too many arguments for joker move
					break;
			}
			object_count++;
		}
	}
	if ((complete_move==0)||((change_joker==1)&&(complete_joker==0))) {
		cout << ERROR_ARGS_MISSING << endl; // "ERROR: You have not completed all the necessary arguments"
		return 1; // Line didn't have all the fields
	} else {
		return 0;
	}
}

// Add player pieces to board, Return 0 on success or the number of the invalid line
int initGameByFile(Game* game, ifstream& init_file) { // $$The function change the current player before exit$$
	// Declare variables
	string line;
	int x,y; // 1<=x<=M 1<=y<=N
	char piece;
	int counter_lines = 0;
	int is_joker = 0;
	int res;
	// Init the board
	while (getline(init_file,line)) {
		counter_lines++;
		// Parse the line
		res = parsePositionLine(line,piece,x,y,is_joker); // parsePositionLine() Return 0 if valid, 1 if invalid and -1 if the line is empty
		if (res==1) { // If invalid
			cout << ERROR_LINE << counter_lines << ERROR_IS_INVALID << endl; // "ERROR: Line ? is invalid"
			game->changePlayer();
			return counter_lines; // Invalid line format
		} else if (res==0) { // Else if valid
			// Check validation
			if (game->positioning(piece,x,y,is_joker)==1) { // positioning() Return 0 if success and 1 otherwise
				cout << ERROR_POSITIONING_FAILED << piece << ERROR_AT << "(" << x << "," << y << ")" << endl; // "ERROR: Couldn't put the piece ? at (?,?)"
				game->changePlayer();
				return counter_lines; // Could not put the pieces over there
			}
		} // And ignore empty lines
	}
	if (!game->flagsCounter()) { // Count how many flags the current player have
		cout << ERROR_NO_FLAGS << endl; // "ERROR: There must be at least one flag"
		game->changePlayer();
		return counter_lines;
	}
	game->changePlayer();
	return 0;
}

void printBoard(Game* game, ofstream& output_file) {
	int i,j;
	for (j=1;j<=N_ROWS;j++) {
		for (i=1;i<=M_COLS;i++) {
			output_file << game->getPiece(i,j); // 1<=i<=M 1<=j<=N
		}
		output_file << endl;
	}
}

void printToOutputFile(Game* game, ofstream& output_file, int winner, int reason, int res_1, int res_2) {
	if ((output_file.is_open())&&(winner>=0)&&(winner<=2)) { // is_open() Return true if the file stream has an associated file, false otherwise
		output_file << MSG_OUTPUT_WINNER << winner << endl; // Winner == -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
		switch (reason) {
			case CODE_ALL_CAPTURED:
				output_file << MSG_OUTPUT_REASON << MSG_ALL_CAPTURED << endl; // "All flags of the opponent are captured"
				break;
			case CODE_ALL_EATEN:
				output_file << MSG_OUTPUT_REASON << MSG_ALL_EATEN << endl; // "All moving PIECEs of the opponent are eaten"
				break;
			case CODE_TIE_NO_MORE_MOVES:
				output_file << MSG_OUTPUT_REASON << MSG_TIE_NO_MORE_MOVES << endl; // "A tie - both Moves input files done without a winner"
				break;
			case CODE_TIE_ALL_EATEN:
				output_file << MSG_OUTPUT_REASON << MSG_TIE_ALL_EATEN << endl; // "A tie - all flags are eaten by both players in the position files"
				break;
			case CODE_BAD_POSITION_1:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_POSITION_1 << res_1 << endl; // "Reason: Bad Positioning input file for player 1 - line <line>"
				break;
			case CODE_BAD_POSITION_2:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_POSITION_2 << res_2 << endl; // "Reason: Bad Positioning input file for player 2 - line <line>"
				break;
			case CODE_BAD_POSITION_BOTH:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_POSITION_BOTH_A << res_1 << MSG_BAD_POSITION_BOTH_B << res_2 << endl; // "Bad Positioning input file for both players - player 1: line <line>, player 2: line <line>"
				break;
			case CODE_BAD_MOVES_1:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_MOVES_1 << res_1 << endl; // "Bad Moves input file for player 1 - line <line>"
				break;
			case CODE_BAD_MOVES_2:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_MOVES_2 << res_1 << endl; // "Bad Moves input file for player 2 - line <line>"
				break;
			default: // Never should happen
				return;
				break;
		}
		output_file << endl; // The 3rd line would be: an empty line
		printBoard(game,output_file);
	}
}

// perform a single move from the selected file to the current player, Return 0 if success, -2 on EOF and -1 otherwise
int takeMove(Game* game, ifstream& moves_player) { // $$The function change the current player before exit$$
	// Declare variables
	int from_x,from_y,to_x,to_y,joker_x,joker_y,change_joker;
	int ret = 0;
	char new_rep;
	string line;
	// Get and parse the line
	if (!getline(moves_player,line)) {
		ret = -2; // No more lines in the file
	} else if (parseMoveLine(line,from_x,from_y,to_x,to_y,joker_x,joker_y,new_rep,change_joker)) { // parseMoveLine() Return 0 if valid and 1 otherwise
		cout << ERROR_INVALID_LINE << endl; // "ERROR: Invalid line format"
		ret = -1; // Invalid line format
	} else if (game->doMove(from_x,from_y,to_x,to_y)==1) { // doMove() Return 0 on success and 1 otherwise
		cout << ERROR_INVALID_MOVE << endl; // "ERROR: Invalid move command"
		ret = -1; // Invalid move
	} else if (change_joker==1) {
		if (game->jokerCommand(new_rep,joker_x,joker_y)) { // jokerCommand() Return 0 on success and 1 otherwise
			cout << ERROR_INVALID_JOKER_COMMAND << endl; // "ERROR: Invalid joker command"
			ret = -1; // Invalid joker command
		} 
	}
	game->changePlayer();
	return ret; // Valid move
}

// The function run the moves files line by line, Return  0 on tie, 1 if player1 win and 2 if player2 win
void playGame(Game* game, ifstream& moves_player_1, ifstream& moves_player_2, int& winner, int& reason, int& counter_lines) {
	winner = -1; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
	int res = 0;
	int no_lines = 0;
	game->checkWinner(winner,reason);
	while (winner==-1) {
		counter_lines++;
		if (winner==-1) { // Game is on
			res = takeMove(game,moves_player_1); // takeMove() Return 0 if success, -2 on EOF and -1 otherwise, $$The function change the current player before exit$$
			if (no_lines==1) { // Player 2 does not have any more moves
				if (res==-2) { // Tie, Both players does not have any more moves
					winner = 0; // Tie
					reason = CODE_TIE_NO_MORE_MOVES;
					return;
				} else { // Player 1 win, Player 2 does not have any more moves
					winner = 1;
					reason = CODE_BAD_MOVES_2;
					cout << ERROR_NO_MORE_MOVES2 << endl; // "ERROR: Player2 don't have any more moves"
					return;
				}
			} else if (res==-1) { // Player 2 win, Player 1 did invalid move
				winner = 2;
				reason = CODE_BAD_MOVES_1;
				return;
			} else if (res==-2) { // Player 1 does not have any more moves
				no_lines = 1;
			} else { // Player 1 move was fine
				no_lines = 0;
			}
			game->checkWinner(winner,reason);
		}
		if (winner==-1) { // Game is on
			res = takeMove(game,moves_player_2); // takeMove() Return 0 if success, -2 on EOF and -1 otherwise, $$The function change the current player before exit$$
			if (no_lines==1) { // Player 1 does not have any more moves
				if (res==-2) { // Tie, Both players does not have any more moves
					winner = 0; // Tie
					reason = CODE_TIE_NO_MORE_MOVES;
					return;
				} else { // Player 2 win, Player 1 does not have any more moves
					winner = 2;
					cout << ERROR_NO_MORE_MOVES1 << endl; // "ERROR: Player1 don't have any more moves"
					reason = CODE_BAD_MOVES_1;
					return;
				}
			} else if (res==-1){ // Player 1 win, Player 2 did invalid move
				winner = 1;
				reason = CODE_BAD_MOVES_2;
				return;
			} else if (res==-2) { // Player 2 does not have any more moves
				no_lines = 1;
			} else {
				no_lines = 0; // Player 2 move was fine
			}
			game->checkWinner(winner,reason);
		}
	}
	return;
}
