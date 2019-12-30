/*
 * GameManager.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: The 'GameManager' class manage the game and update the game status for each player.
 * 		This department is responsible for passing relevant information about the status of the game to the 'PlayerAlgorithm'.
 * 		The 'PlayerAlgorithm' decide it's move, which will return to the 'GameManager'.
 * 		This class manages the game at a higher level than the helper class - 'GameBoard'.
 */
#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <iomanip>	// std::setw
#include <iostream>	// std::cout, std::endl, tolower, toupper
#include <memory>	// std::unique_ptr, std::make_unique
#include <utility>	// std::move
#include <vector>	// std::vector

#include "BoardRPS.h"
#include "FightInfoRPS.h"
#include "GameManagerBoard.h"
#include "GameParameters.h"
#include "JokerChange.h"
#include "MoveRPS.h"
#include "PiecePositionRPS.h"
#include "PlayerAlgorithmAutoRPS.h"
#include "PlayerAlgorithmFileRPS.h"

class GameManager {
private:
	GameManagerBoard board;
	char board_player1[N_ROWS][M_COLS];
	char board_player2[N_ROWS][M_COLS];
	int current_player; // 1=first player, 2=second player
	int gameover_reason;
	int gameover_winner; // winner = -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
	std::map<char, int> player1_pieces_counters; // key - the piece(Rock, Paper...), value - (pieces counter)
	std::map<char, int> player2_pieces_counters; // key - the piece(Rock, Paper...), value - (pieces counter)
public:
	// GameManager
	GameManager();
	// GameManager functions
	void changePlayer() {current_player = (current_player==1)?2:1;}
	int checkGameOver(); // The function check if we have a winner, Return 1 if game is still on and 0 otherwise // winner = -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
	void compareBoards(std::vector<std::unique_ptr<FightInfo>>& fights); // Compare between the two positioning boards, If there is a fight remove the loser, Set FightInfo vector of the positioning fights
	void createOutputFile(); // Create the game output file based on 'gameover_reason' and 'gameover_winner'
	void counterDecrease(char piece, int player); // Decrease the piece counter for the selected player
	void counterIncrease(char piece, int player) {(player==1)?player1_pieces_counters[piece]++:player2_pieces_counters[piece]++;} // Increase the piece counter for the selected player
	int fight(char piece_1, char piece_2); // Perform a fight between two pieces, Return 0 if both lost, 1 if first piece win, 2 if second piece win
	int fightInit(char piece_1, char piece_2, int x, int y); // Fight function is called ONLY if (x,y) at both boards isn't empty, Return 0 if both lost, 1 if first piece win, 2 if second piece win
	 // fightMove() Fight function is called ONLY if (x,y) at both boards isn't empty, Perform the move and return FightInfo for the fight
	std::unique_ptr<FightInfoRPS> fightMove(char piece_from, char piece_to, const Point& pos1, const Point& pos2);
	std::unique_ptr<BoardRPS> getBoard(); // Create Board object based on the current game board
	int getCounter(char piece, int player) {
		int counter = (player==1)?player1_pieces_counters[piece]:player2_pieces_counters[piece];
		return counter;
	}
	int getCurrentPlayer() {return current_player;}
	int getOtherPlayer() {return (2-(current_player-1));}
	char hideJokerTypeJ(char piece); // Return the type of the piece while hiding joker representation, Return R, P, S, B, F or J
	char hideJokerTypeRep(char piece); // Return the type of the piece while hiding jokers, Return R, P, S, B or F
	// initialize() Init the game with two positioning vectors, Set ret to 0 if success and 1 otherwise, Return FightInfo vector of all the positioning fights
	std::vector<std::unique_ptr<FightInfo>> initialize(int& ret, std::vector<std::unique_ptr<PiecePosition>>& player1_locations, std::vector<std::unique_ptr<PiecePosition>>& player2_locations);
	int jokerCommand(JokerChange& joker_change); // Change the selected joker representation, Return 0 on success and 1 otherwise
	std::unique_ptr<FightInfoRPS> move(Move& player_move, int& ret); // // Perform a move, Return FightInfo if there was a fight and nullptr otherwise, Set ret to 0 if success and 1 otherwise
	char pieceIsJoker(char piece); // Return JOKER_TRUE if piece is joker and JOKER_FALSE otherwise
	int positioning(PiecePosition& piece_position, int player); // Put a new piece to the board, Return 0 if success and 1 otherwise
	void printBoard(std::ofstream& output_file); // Print the game board at the end of the output file
	void printBoardExtra(); // This is a support function that print to the screen the status of both boards and the pieces counters
	void setCurrentPlayer(int player) {current_player = player;}
	void setGameOver(int winner, int reason) {
		gameover_reason = reason;
		gameover_winner = winner;
	}
	int validateMove(const Point& from, const Point& to); // Check if the player can move, Return 0 if he can't move, 1 if he can and 2 if there is opponent piece at the destination
	int validation(PiecePosition& piece_position, int player); // The function validate that the piece can be entered to the board, Return 0 if valid and 1 otherwise
};

#endif /* GAMEMANAGER_H_ */
