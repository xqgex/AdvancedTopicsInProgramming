/*
 * PlayerAlgorithmFileRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class PlayerAlgorithm.h
 * 		That's the implementation of assignment 1.
 * 		This class read the moves pieces using input files.
 */
#ifndef PLAYERALGORITHMFILERPS_H_
#define PLAYERALGORITHMFILERPS_H_

#include <fstream>	// std::ifstream, getline
#include <iostream>	// std::cout, std::endl
#include <memory>	// std::unique_ptr, std::make_unique
#include <sstream>	// std::istringstring
#include <string>	// std::string
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

class PlayerAlgorithmFileRPS:public PlayerAlgorithm {
private:
	int do_joker_change; // 0 = False, 1 = True
	char joker_rep;
	int joker_x,joker_y;
	std::ifstream moves_file;
	int whoami;
public:
	// Abstract implementation
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
	virtual void notifyOnInitialBoard(__attribute__((unused)) const Board& b, __attribute__((unused)) const std::vector<unique_ptr<FightInfo>>& fights) override {}; // I don't have anything to do with it
	virtual void notifyOnOpponentMove(__attribute__((unused)) const Move& move) override {}; // Called only on opponent's move // I don't have anything to do with it
	virtual void notifyFightResult(__attribute__((unused)) const FightInfo& fightInfo) override {}; // Called only if there was a fight // I don't have anything to do with it
	virtual unique_ptr<Move> getMove() override;
	virtual unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
	// PlayerAlgorithmFileRPS
	PlayerAlgorithmFileRPS();
	// PlayerAlgorithmFileRPS functions
	int openMoveFile(); // Open the move files, Return 0 on success and 1 otherwise
	int parseMoveLine(std::string& line, PointRPS& from, PointRPS& to); // The function parse move line, Return 0 if valid and 1 otherwise
	int parsePositionLine(std::string& line, char& piece, int& x, int& y, int& is_joker); // The function parse an initial board line, Return 0 if valid, 1 if invalid and -1 if the line is empty
	int strToInt(std::string& source, int& destination); // Convert string to int, Return 0 on success and 1 otherwise
};

#endif /* PLAYERALGORITHMFILERPS_H_ */
