/*
 * PlayerAlgorithmAutoRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class PlayerAlgorithm.h
 * 		Smart algorithm for the automatic player.
 * 		This class pass to the 'GameManager' the smartest move it can find in order to win the game.
 */
#ifndef PLAYERALGORITHMAUTORPS_H_
#define PLAYERALGORITHMAUTORPS_H_

#include <cmath>	// std::abs
#include <map>		// std::map
#include <memory>	// std::unique_ptr, std::make_unique
#include <random>	// std::random_device, std::mt19937, std::uniform_int_distribution
#include <utility>	// std::move
#include <vector>	// std::vector

#include "PlayerAlgorithm.h"

#include "BoardRPS.h"
#include "FightInfoRPS.h"
#include "GameParameters.h"
#include "JokerChangeRPS.h"
#include "MoveRPS.h"
#include "PiecePositionRPS.h"
#include "PointRPS.h"

class PlayerAlgorithmAutoRPS:public PlayerAlgorithm {
private:
	const int bias = 3; // After how many steps to the target switch to attack mode (against opponent victim)
	char board_his[N_ROWS][M_COLS];
	char board_my[N_ROWS][M_COLS][2];
	int steps_counter; // How many steps we made towards the target
	PointRPS last_pos;
	PointRPS move_from;
	int move_mode; // 0 is toward the target and 1 is toward the victim (opponent known piece)
	PointRPS move_to;
	std::map<char, int> opponent_died_pieces_counters;
	int opponent_number;
	PointRPS target;
	int whoami;
public:
	// Abstract implementation
	virtual void getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill) override;
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) override;
	virtual void notifyOnOpponentMove(const Move& move) override; // Called only on opponent's move
	virtual void notifyFightResult(const FightInfo& fightInfo) override; // Called only if there was a fight
	virtual unique_ptr<Move> getMove() override;
	virtual unique_ptr<JokerChange> getJokerChange() override {return nullptr;}; // nullptr if no change is requested // Will be implemebted at Ex3
	// PlayerAlgorithmAutoRPS
	PlayerAlgorithmAutoRPS();
	// PlayerAlgorithmAutoRPS functions
	int checkGameOver(); // Return 0 if game is over for us and 1 otherwise
	int fightSimulate(char piece_1, char piece_2); // Simulate a fight between two pieces, Return 0 if both lost, 1 if only player 1 win, 2 if only player 2 win
	void findTarget(); // Guess what is the opponent's flag
	PointRPS findVictim(PointRPS my_piece); // Search if there is a known opponent piece that the ours selected piece can win, Return the location of a piece we can win or invalid point otherwise
	PointRPS getAvailablePoint(char piece); // Search for avilable point for the fighters, Return available point at the board
	void minMax(); // Find the most atractive piece we can move and calculate where to move him, Update the info at 'move_from' and 'move_to'
	double scoring(PointRPS source_piece, PointRPS next_step); // Calculate a score for moving 'source_piece' to 'next_step', Return a score for the selected move
};

#endif /* PLAYERALGORITHMAUTORPS_H_ */
