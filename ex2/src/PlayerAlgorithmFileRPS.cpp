
/*
 * PlayerAlgorithmFileRPS.cpp
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class PlayerAlgorithm.h
 * 		That's the implementation of assignment 1.
 * 		This class read the moves pieces using input files.
 */

#include "PlayerAlgorithmFileRPS.h"

////////////////////////////////////////////////////////////////////
////	PlayerAlgorithmFileRPS 					////
////////////////////////////////////////////////////////////////////
PlayerAlgorithmFileRPS::PlayerAlgorithmFileRPS() {
	do_joker_change = 0;
	joker_rep = EMPTY;
	joker_x = 0;
	joker_y = 0;
	whoami = -1;
}

////////////////////////////////////////////////////////////////////
////	Abstract implementation					////
////////////////////////////////////////////////////////////////////
void PlayerAlgorithmFileRPS::getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill) {
	// Declare variables
	char piece;
	int x,y; // 1<=x<=M 1<=y<=N
	int counter_lines = 0;
	int is_joker = 0;
	int res;
	std::string line;
	std::ifstream init_file;
	// Who Am I?
	whoami = player;
	if (whoami==1) {
		init_file.open(FILE_BOARD_PLAYER_1, std::ifstream::in);
	} else { // whoami==2
		init_file.open(FILE_BOARD_PLAYER_2, std::ifstream::in);
	}
	// Check that all input files opened successfully
	if (!init_file.is_open()) { // is_open() Return true if the file stream has an associated file, false otherwise
		if (whoami==1) {
			std::cout << ERROR_OPEN_PLAYER << whoami << ERROR_OPEN_BOARD << FILE_BOARD_PLAYER_1 << ERROR_OPEN_ENDL << std::endl;
		} else {
			std::cout << ERROR_OPEN_PLAYER << whoami << ERROR_OPEN_BOARD << FILE_BOARD_PLAYER_2 << ERROR_OPEN_ENDL << std::endl;
		}
		vectorToFill.push_back(std::make_unique<PiecePositionRPS>(EMPTY,PointRPS(0,0),JOKER_FALSE,whoami));
		return;
	}
	// check also the move file
	if (openMoveFile()==1) { // OpenMoveFile() Return 0 on success and 1 otherwise
		if (whoami==1) {
			std::cout << ERROR_OPEN_PLAYER << whoami << ERROR_OPEN_MOVE << FILE_MOVES_PLAYER_1 << ERROR_OPEN_ENDL << std::endl;
		} else {
			std::cout << ERROR_OPEN_PLAYER << whoami << ERROR_OPEN_MOVE << FILE_MOVES_PLAYER_2 << ERROR_OPEN_ENDL << std::endl;
		}
		vectorToFill.push_back(std::make_unique<PiecePositionRPS>(EMPTY,PointRPS(0,0),JOKER_FALSE,whoami));
		return;
	}
	// Init the board
	while (getline(init_file,line)) {
		counter_lines++;
		// Parse the line
		res = parsePositionLine(line,piece,x,y,is_joker); // parsePositionLine() Return 0 if valid, 1 if invalid and -1 if the line is empty
		if (res==1) { // If invalid
			std::cout << ERROR_LINE << counter_lines << ERROR_IS_INVALID << std::endl; // "ERROR: Line ? is invalid"
			vectorToFill.push_back(std::make_unique<PiecePositionRPS>(EMPTY,PointRPS(0,0),JOKER_FALSE,whoami)); //invalid piecePosition
		} else if (res==0) { // Else if valid
			if (is_joker==1) {
				vectorToFill.push_back(std::make_unique<PiecePositionRPS>(piece,PointRPS(x,y),JOKER_TRUE,whoami));
			} else {
				vectorToFill.push_back(std::make_unique<PiecePositionRPS>(piece,PointRPS(x,y),JOKER_FALSE,whoami));
			}
		} // And ignore empty lines
	}
	// Cleanup
	init_file.close();
}

unique_ptr<Move> PlayerAlgorithmFileRPS::getMove() {
	std::string line;
	// Variables to return
	PointRPS from = PointRPS();
	PointRPS to = PointRPS();
	// Get and parse the line
	if (!getline(moves_file,line)) {
		moves_file.close();
		return nullptr; // No more lines in the file
	} else if (parseMoveLine(line,from,to)) { // parseMoveLine() Return 0 if valid and 1 otherwise
		std::cout << ERROR_INVALID_LINE << std::endl; // "ERROR: Invalid line format"
		return std::move(std::make_unique<MoveRPS>(PointRPS(0,0),PointRPS(0,0))); // Invalid line format
	} else {
		return std::move(std::make_unique<MoveRPS>(from,to));
	}
}

unique_ptr<JokerChange> PlayerAlgorithmFileRPS::getJokerChange() {
	if (do_joker_change) {
		return std::move(std::make_unique<JokerChangeRPS>(PointRPS(joker_x,joker_y),joker_rep));
	} else {
		return nullptr;
	}
}

////////////////////////////////////////////////////////////////////
////	PlayerAlgorithmFileRPS functions			////
////////////////////////////////////////////////////////////////////
// Open the move files, Return 0 on success and 1 otherwise
int PlayerAlgorithmFileRPS::openMoveFile() {
	if (!moves_file.is_open()) { // is_open() Return true if the file stream has an associated file, false otherwise
		if (whoami==1) {
			moves_file.open(FILE_MOVES_PLAYER_1, std::ifstream::in);
		} else if (whoami==2) {
			moves_file.open(FILE_MOVES_PLAYER_2, std::ifstream::in);
		}
		if (!moves_file.is_open()) { // is_open() Return true if the file stream has an associated file, false otherwise
			return 1;
		}
	}
	return 0;
}

// The function parse move line, Return 0 if valid and 1 otherwise
int PlayerAlgorithmFileRPS::parseMoveLine(std::string& line, PointRPS& from, PointRPS& to) {
	int from_x, from_y, to_x, to_y, joker_x, joker_y;
	char new_rep;
	int object_count = 0;
	int complete_move = 0;
	int complete_joker = 0;
	std::string splited_str;
	std::istringstream line_stream(line); // <FROM_X> <FROM_Y> <TO_X> <TO_Y> [J:   <Joker_X> <Joker_Y> <NEW_REP>]
	do_joker_change = 0;
	while (getline(line_stream,splited_str,' ')) {
		if (splited_str.length()>0) { // Ignore double spaces
			if (splited_str[splited_str.size()-1]=='\r') { // In case the move file was created in WINDOWS
				splited_str.erase(splited_str.size() - 1); // We would have to remove the "\r" from the end of the line
			}
			switch (object_count) {
				case 0: if (strToInt(splited_str,from_x)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						std::cout << ERROR_INVALID_X_FROM << std::endl; // "ERROR: Invalid X_FROM coordinate"
						return 1; // Invalid input
					} // Valid <FROM_X>
					break;
				case 1: if (strToInt(splited_str,from_y)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						std::cout << ERROR_INVALID_Y_FROM << std::endl; // "ERROR: Invalid Y_FROM coordinate"
						return 1; // Invalid input
					} // Valid <FROM_Y>
					break;
				case 2: if (strToInt(splited_str,to_x)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						std::cout << ERROR_INVALID_X_TO << std::endl; // "ERROR: Invalid X_TO coordinate"
						return 1; // Invalid input
					} // Valid <TO_X>
					break;
				case 3: if (strToInt(splited_str,to_y)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						std::cout << ERROR_INVALID_Y_TO << std::endl; // "ERROR: Invalid Y_TO coordinate"
						return 1; // Invalid input
					} // Valid <TO_Y>
					complete_move = 1;
					break;
				case 4: if ((splited_str.length()!=2)||(splited_str[0]!='J')||(splited_str[1]!=':')) {
						std::cout << ERROR_INVALID_JOKER_FORMAT << std::endl; // "ERROR: Invalid format for the joker"
						return 1; // Invalid input for the joker
					} else {
						do_joker_change = 1; // Found move of a joker
					}
					break;
				case 5: if (do_joker_change==0) {
							std::cout << ERROR_ARGS_MANY_FOR_PIECE << std::endl; // "ERROR: There are too many arguments for non joker move"
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
						std::cout << ERROR_INVALID_JOKER_PIECE << std::endl; // "ERROR: Invalid piece"
						return 1; // Invalid char
					} else {
						new_rep = splited_str[0]; // Joker <NEW_REP>
					}
					complete_joker = 1;
					break;
				default: std::cout << ERROR_ARGS_MANY_FOR_JOKER << std::endl; // "ERROR: There are too many arguments for joker move"
					return 1; // Too many arguments for joker move
					break;
			}
			object_count++;
		}
	}
	if ((complete_move==0)||((do_joker_change==1)&&(complete_joker==0))) {
		std::cout << ERROR_ARGS_MISSING << std::endl; // "ERROR: You have not completed all the necessary arguments"
		return 1; // Line didn't have all the fields
	} else {
		from.setX(from_x);
		from.setY(from_y);
		to.setX(to_x);
		to.setY(to_y);
		if (do_joker_change==1) {
			this->joker_x = joker_x;
			this->joker_y = joker_y;
			this->joker_rep = new_rep;
		}
		return 0;
	}
}

// The function parse an initial board line, Return 0 if valid, 1 if invalid and -1 if the line is empty
int PlayerAlgorithmFileRPS::parsePositionLine(std::string& line, char& piece, int& x, int& y, int& is_joker) {
	int object_count = 0;
	int expected_count = 0;
	std::string splited_str;
	std::istringstream line_stream(line);
	is_joker = 0;
	while (getline(line_stream,splited_str,' ')) {
		if (splited_str.length()>0) { // Ignore double spaces
			if (splited_str[splited_str.size()-1]=='\r') { // In case the board file was created in WINDOWS
				splited_str.erase(splited_str.size() - 1); // We would have to remove the "\r" from the end of the line
			}
			switch (object_count) {
				case 0: if ((splited_str.length()!=1)||(splited_str[0]<'A')||(splited_str[0]>'Z')) {
					std::cout << ERROR_GENERAL << splited_str[0] << ERROR_NOT_CHAR << std::endl; // "ERROR: '?' is invalid char"
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
					std::cout << ERROR_INVALID_X << std::endl; // "ERROR: Invalid X coordinate"
						return 1; // Invalid input
					} // Valid <X>
					break;
				case 2: if (strToInt(splited_str,y)==1) { // strToInt() Return 0 on seccess and 1 otherwise
						std::cout << ERROR_INVALID_Y << std::endl; // "ERROR: Invalid Y coordinate"
						return 1; // Invalid input
					} // Valid <Y>
					break;
				case 3: if ((is_joker==0)||(splited_str.length()!=1)||(splited_str[0]<'A')||(splited_str[0]>'Z')) {
						std::cout << ERROR_ARGS_MANY_OR_INVALID << std::endl; // "ERROR: There are too many arguments or you have enter invalid char as a piece"
						return 1; // Too many arguments or invalid piece
					} else {
						piece = splited_str[0]; // Valid piece
					}
					break;
				default: std::cout << ERROR_ARGS_MANY << std::endl; // "ERROR: There are too many arguments"
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
		std::cout << ERROR_INVALID_POSITIONING << std::endl; // "ERROR: Found invalid positioning line"
		return 1; // Will return 1 if line didn't have all the fields
	}
}

// Convert string to int, Return 0 on success and 1 otherwise
int PlayerAlgorithmFileRPS::strToInt(std::string& source, int& destination) {
	unsigned i;
	for (i=0;i<source.length();++i) {
		if ((source[i]<'0')||(source[i]>'9')) {
			std::cout << ERROR_GENERAL << source << ERROR_NOT_NUMBER << std::endl; // "ERROR: '?' isn't a number"
			return 1; // This is not a number
		}
	}
	destination = atoi(source.c_str()); // Because we manually check 'atoi' input string, We can use her for the conversion (Instead of 'stoi')
	return 0;
}
