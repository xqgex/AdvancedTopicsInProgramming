/*
 * TournamentManager.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: The header file of the tournament manager code
 */
#ifndef TOURNAMENTMANAGER_H_
#define TOURNAMENTMANAGER_H_

#include <cmath>	// std::abs
#include <iostream>	// std::cout, std::endl
#include <map>		// std::map
#include <memory>	// std::unique_ptr, std::make_unique
#include <random>	// std::random_device, std::mt19937, std::uniform_int_distribution
#include <string.h>	// std::string
#include <utility>	// std::move
#include <vector>	// std::vector
#include <mutex>
#include <climits>
#include <set>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <typeinfo>
#include <stdlib.h>
#include <thread>
#include <list>
#include <errno.h>
#include <dirent.h>
#include <algorithm>

#include "BoardRPS.h"
#include "FightInfoRPS.h"
#include "GameManager.h"
#include "JokerChange.h"
#include "MoveRPS.h"
#include "PiecePositionRPS.h"
#include "PlayerAlgorithm.h"
#include "AlgorithmRegistration.h"

#define BUF_SIZE 1024

class TournamentManager {
	static TournamentManager theTournamentManager;
	long unsigned next_game;
	std::vector<std::string> algorithmNames;
	std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
	std::map<std::string, int> id2score;
	std::mutex score_mutex;
	std::mutex match_mutex;
	std::vector<int> gamesPerPlayer;
	std::vector<std::pair<int, int>> gamesArray;
	std::vector<void*> handles;
	// private ctor
	TournamentManager() {
		next_game = 0;
	}
	void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
		if (theTournamentManager.id2factory.find(id)==theTournamentManager.id2factory.end()) { // ID doesn't exist
			theTournamentManager.id2factory[id] = factoryMethod;
			theTournamentManager.id2score[id] = 0;
		} else {
			std::cout << ERROR_SHARED_LIB << id << ERROR_SHARED_LIB_B << std::endl; // "ERROR: RSPPlayer '?' already been loaded"
		}
	}
public:
	friend class AlgorithmRegistration;
	void CreateMatches();
	std::string getAlgorithmName(int index) {
		return algorithmNames[index];
	}
	static TournamentManager& getTournamentManager() {
		return theTournamentManager;
	}
	int go(long unsigned max_thread, std::string path);
	void id2factoryClear() {
		long unsigned i;
		id2factory.clear();
		for (i=0;i<handles.size();++i) { // Close all the shared object files
			dlclose(handles[i]);
		}
	}
	void initGamesPerPlayer() {
		int i;
		for (i=0;i<size();++i) {
			gamesPerPlayer.push_back(0);
		}
	}
	int loadSO(std::string path);
	void print_results();
	int size() {
		return id2factory.size();
	}
	void updateAlgorithmNames() {
		for (auto algorithmFactoryFunc : id2factory) {
			algorithmNames.push_back(algorithmFactoryFunc.first);
		}
	}
	void updateScore(std::string id, int value) {
		id2score[id] += value;
	}
	void worker();
};

bool is_number(const std::string& s);
int main(int argc, char* argv[]); // main

#endif /* TOURNAMENTMANAGER_H_ */
