/*
 * Main.cpp
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Parsing input arguments (auto or file) and play the appropriate 'PlayerAlgorithm'.
 */

#include "Main.h"

////////////////////////////////////////////////////////////////////
////	Main							////
////////////////////////////////////////////////////////////////////
// Play the game (after the initial positioning done)
void play(GameManager& manager,	PlayerAlgorithm* players[2]) {
	int res;
	int no_fight_counter = 0;
	int last_player_EOF = 0;
	std::unique_ptr<Move> turn_move;
	std::unique_ptr<FightInfoRPS> turn_fight;
	std::unique_ptr<JokerChange> turn_jokerchange;
	manager.setCurrentPlayer(1);
	while ((manager.checkGameOver()==1)&&(no_fight_counter<NO_FIGHTS)) { // checkGameOver() Return 1 if game is still on and 0 otherwise
		no_fight_counter++;
		turn_move = players[manager.getCurrentPlayer()-1]->getMove();
		if (turn_move!=nullptr) {
			turn_fight = manager.move(*(turn_move.get()),res); // move() Return FightInfo if there was a fight and nullptr otherwise, Set res to 0 if success and 1 otherwise
		}
		if (last_player_EOF==1) { //  Last player does not have any more moves
			if (turn_move==nullptr) { // Tie, Both players does not have any more moves
				manager.setGameOver(0,REASON_TIE_NO_MORE_MOVES); // "A tie - both Moves input files done without a winner"
			} else { // Current player win, Last player does not have any more moves
				std::cout << ERROR_PLAYER_NUM << manager.getCurrentPlayer() << ERROR_NO_MORE_MOVES_B << std::endl; // "ERROR: Player ? don't have any more moves"
				manager.setGameOver(manager.getCurrentPlayer(),REASON_BAD_MOVES); // "Bad Moves input file for player ?"
			}
		} else if (turn_move==nullptr) { // Current player does not have any more moves
			last_player_EOF = 1;
		} else if (res==1) { // Last player win, Current player did invalid move
			std::cout << ERROR_PLAYER_NUM << manager.getCurrentPlayer() << ERROR_BAD_MOVE_B << std::endl; // "ERROR: Player ? did invalid move"
			manager.setGameOver(manager.getOtherPlayer(),REASON_BAD_MOVES); // "Bad Moves input file for player ?"
		} else { // Player 1 move was fine
			last_player_EOF = 0;
			if (turn_fight!=nullptr) {
				players[manager.getCurrentPlayer()-1]->notifyFightResult(*(turn_fight.get())); // notifyFightResult() Called only if there was a fight
				no_fight_counter = 0;
			}
			turn_jokerchange = players[manager.getCurrentPlayer()-1]->getJokerChange(); // getJokerChange() Return nullptr if no change is requested
			if (turn_jokerchange!=nullptr) {
				if (manager.jokerCommand(*(turn_jokerchange.get()))==1) { // jokerCommand() Return 0 on success and 1 otherwise
					std::cout << ERROR_INVALID_JOKER_COMMAND << std::endl; // "ERROR: Invalid joker command"
					manager.setGameOver(manager.getOtherPlayer(),REASON_BAD_MOVES); // "Bad Moves input file for player ?"
					continue; // We set GameOver so the loop will finish gracefully
				}
			}
			players[1-(manager.getCurrentPlayer()-1)]->notifyOnOpponentMove(*(turn_move.get()));
			if (turn_fight!=nullptr) {
				players[1-(manager.getCurrentPlayer()-1)]->notifyFightResult(*(turn_fight.get())); // notifyFightResult() Called only if there was a fight
			}
		}
		manager.changePlayer();
	}
	if (no_fight_counter==NO_FIGHTS) {
		std::cout << ERROR_NO_FIGHT << std::endl; // "ERROR: Game ended after 100 moves without a fight"
		manager.setGameOver(0,REASON_TIE_NO_MORE_MOVES); // "A tie - both Moves input files done without a winner"
	}
}

// Parse the input args, Return 1=file-file, 2=file-auto, 3=auto-file, 4=auto-auto, -1=invalid input
int validInput(std::string input) {
	if (input.length()==0) {
		return -1;
	}
	std::string delimeter = "-vs-";
	std::string player1;
	std::string player2;
	int pos = input.find(delimeter);
	player1 = input.substr(0,pos);
	player2 = input.substr(pos+4,input.length());
	if (player1=="file" && player2=="file") {
		return 1;
	} else if (player1=="file" && player2=="auto") {
		return 2;
	} else if (player1=="auto" && player2=="file") {
		return 3;
	} else if (player1=="auto" && player2=="auto") {
		return 4;
	} else {
		return -1;
	}
}

int main(int argc, char* argv[]) {
	if (argc!=2) {
		std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex2 (file-vs-file | file-vs-auto | auto-vs-file | auto-vs-auto)"
		return EXIT_FAILURE;
	}
	std::string input = std::string(argv[1]);
	int res;
	GameManager manager;
	// Positioning variables
	std::vector<std::unique_ptr<FightInfo>> init_fights;
	std::vector<std::unique_ptr<PiecePosition>> init_player1;
	std::vector<std::unique_ptr<PiecePosition>> init_player2;
	// Parse command line args
	PlayerAlgorithm* players[2];
	__attribute__((unused)) PlayerAlgorithmFileRPS player1_file;
	__attribute__((unused)) PlayerAlgorithmFileRPS player2_file;
	__attribute__((unused)) PlayerAlgorithmAutoRPS player1_auto;
	__attribute__((unused)) PlayerAlgorithmAutoRPS player2_auto;
	int res_input = validInput(input); // validInput() Return 1=file-file, 2=file-auto, 3=auto-file, 4=auto-auto, -1=invalid input
	if (res_input==1) {
		players[0] = &player1_file;
		players[1] = &player2_file;
	} else if (res_input==2) {
		players[0] = &player1_file;
		players[1] = &player2_auto;
	} else if (res_input==3) {
		players[0] = &player1_auto;
		players[1] = &player2_file;
	} else if (res_input==4) {
		players[0] = &player1_auto;
		players[1] = &player2_auto;
	} else {
		std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex2 (file-vs-file | file-vs-auto | auto-vs-file | auto-vs-auto)"
		return EXIT_FAILURE;
	}
	// Positioning
	players[0]->getInitialPositions(1, init_player1);
	players[1]->getInitialPositions(2, init_player2);
	init_fights = manager.initialize(res,init_player1,init_player2); // initialize() Set ret to 0 if success and 1 otherwise, Return FightInfo vector of all the positioning fights
	if (res==1) { // Error message already been set by initialize()
		std::cout << ERROR_GAME_ENDED_POSITIONING << std::endl; // The game ended in failure during positioning
		manager.createOutputFile(); // Create the game output file based on 'gameover_reason' and 'gameover_winner'
		return EXIT_FAILURE;
	}
	BoardRPS init_board = *(manager.getBoard().get()); // getBoard() Create Board object based on the current game board
	players[0]->notifyOnInitialBoard(init_board,init_fights);
	players[1]->notifyOnInitialBoard(init_board,init_fights);
	// Moves
	play(manager,players);
	manager.createOutputFile(); // Create the game output file based on 'gameover_reason' and 'gameover_winner'
	std::cout << MSG_DONE << std::endl; // "Done, Check the output file for more information"
	return EXIT_SUCCESS;
}
