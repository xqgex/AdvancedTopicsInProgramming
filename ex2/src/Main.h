/*
 * Main.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Parsing input arguments (auto or file) and play the appropriate 'PlayerAlgorithm'.
 */
#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>	// std::cout, std::endl
#include <memory>	// std::unique_ptr
#include <string.h>	// std::string
#include <vector>	// std::vector

#include "BoardRPS.h"
#include "FightInfoRPS.h"
#include "GameManager.h"
#include "JokerChange.h"
#include "MoveRPS.h"
#include "PiecePositionRPS.h"
#include "PlayerAlgorithmAutoRPS.h"
#include "PlayerAlgorithmFileRPS.h"

void play(GameManager* manager,	PlayerAlgorithm* players[2]); // Play the game (after the initial positioning done)
int validInput(std::string input); // Parse the input args, Return 1=file-file, 2=file-auto, 3=auto-file, 4=auto-auto, -1=invalid input
int main(int argc, char* argv[]); // main

#endif /* MAIN_H_ */
