#include <cstdlib>	// EXIT_SUCCESS, EXIT_FAILURE
#include <fstream>	// ifstream, ofstream
#include <iostream>	// cout, endl
using namespace std;
#include "main_aux.h"

int main() {
	// Declare general variables
	int counter = 0;
	int res_1,res_2 = 0;
	int files_open_error = 0;
	int winner; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
	int reason;
	// Create game variables
	ifstream init_file_player_1(FILE_BOARD_PLAYER_1);
	ifstream init_file_player_2(FILE_BOARD_PLAYER_2);
	ifstream moves_player_1(FILE_MOVES_PLAYER_1);
	ifstream moves_player_2(FILE_MOVES_PLAYER_2);
	ofstream output_file;
	Game* game;
	// Check that all input files opened successfully
	if (!init_file_player_1.is_open()) { // is_open() Return true if the file stream has an associated file, false otherwise
		cout << "Failed to open player 1 board file ('" << FILE_BOARD_PLAYER_1 << "')" << endl;
		files_open_error++;
	}
	if (!init_file_player_2.is_open()) { // is_open() Return true if the file stream has an associated file, false otherwise
		cout << "Failed to open player 2 board file ('" << FILE_BOARD_PLAYER_2 << "')" << endl;
		files_open_error++;
	}
	if (!init_file_player_2.is_open()) { // is_open() Return true if the file stream has an associated file, false otherwise
		cout << "Failed to open player 2 move file ('" << FILE_MOVES_PLAYER_1 << "')" << endl;
		files_open_error++;
	}
	if (!init_file_player_2.is_open()) { // is_open() Return true if the file stream has an associated file, false otherwise
		cout << "Failed to open player 2 move file ('" << FILE_MOVES_PLAYER_2 << "')" << endl;
		files_open_error++;
	}
	if (0 < files_open_error) {
		return EXIT_FAILURE;
	}
	// Positioning part
	output_file.open(FILE_OUTPUT);
	game = new Game();
	res_1 = initGameByFile(game,init_file_player_1); // Return 0 on success or the number of the invalid line, $$The function change the current player before exit$$
	res_2 = initGameByFile(game,init_file_player_2); // Return 0 on success or the number of the invalid line, $$The function change the current player before exit$$
	positioningWinByError(winner,reason,res_1,res_2); // Return -1 if both players are invalid, 0 if both players are valid, 1 if only player 2 have error and 2 if only player 1 have error
	if (winner!=-1) { // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
		printToOutputFile(game,output_file,winner,reason,res_1,res_2);
		cout << "The game ended in failure during positioning" << endl;
		delete game;
		return EXIT_FAILURE;
	}
	game->compareBoards();
	// Move the pieces
	playGame(game,moves_player_1,moves_player_2,winner,reason,counter);
	// Print to the output file the result of the game
	printToOutputFile(game,output_file,winner,reason,counter,0);
	// Cleanup and exit
	init_file_player_1.close();
	init_file_player_2.close();
	moves_player_1.close();
	moves_player_2.close();
	output_file.close();
	delete game;
	cout << "Done, Check the output file for more information" << endl;
	return EXIT_SUCCESS;
}
