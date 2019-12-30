/*
 * Main.cpp
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: The tournament manager is responsible to load the players, generate the matches and run all the games
 */

#include "TournamentManager.h"

TournamentManager TournamentManager::theTournamentManager;

void TournamentManager::CreateMatches() {
	int curr_player;
	int op_player;
	int total_games = 0;
	for (curr_player=0;curr_player<size();++curr_player) {
		while (gamesPerPlayer[curr_player]<NUMBER_OF_GAMES) {
			op_player = total_games%size();
			if ((curr_player!=op_player)&&(gamesPerPlayer[op_player]<NUMBER_OF_GAMES)) {
				gamesArray.push_back(std::make_pair(curr_player,op_player));
				gamesPerPlayer[curr_player]++;
				gamesPerPlayer[op_player]++;
			}
			total_games++;
		}
	}
}

int TournamentManager::go(long unsigned max_thread, std::string path) {
	int i;
	long unsigned j;
	if (loadSO(path)==1) {
		return 1;
	}
	if (size()<2) {
		std::cout << ERROR_MISSING_SO_FILES << std::endl; // "ERROR: Add more .so files and then run the program again."
		return 1;
	}
	CreateMatches();
	updateAlgorithmNames();
	for (i=0;i<size();++i) {
		gamesPerPlayer[i] = 0;
	}
	if (1<max_thread) { // If the user ask for threads
		if (gamesArray.size()<max_thread) { // If the user ask for too many threads
			max_thread = gamesArray.size();
		}
		std::vector<std::thread> my_threads;
		for (j=0;j<max_thread-1;++j) {
			my_threads.emplace_back(&TournamentManager::worker, this);
		}
		for (auto& t: my_threads) {
			t.join();
		}
	} else {
		worker();
	}
	print_results();
	return 0;
}

int TournamentManager::loadSO(std::string path) {
	int i;
	int loop_size;
	void* handle;
	DIR* dirp;
	struct dirent* dp;
	std::string filename;
	if ( (dirp = opendir(path.c_str()))==NULL) {
		std::cout << "Can't open directory: " << path << std::endl;
		return 1;
	}
	while ((dp = readdir(dirp))!=NULL) {
		filename = std::string(dp->d_name);
		if (3<filename.length()) { // Name length is more then the length of ".so"
			if (filename.compare(filename.length()-3,3,".so")==0) {
				loop_size = size();
				if ((handle = dlopen((path + "/" + filename).c_str(), RTLD_LAZY))==NULL) { // If dlopen() fails for any reason, it returns NULL
					std::cout << ERROR_FAILED_LOAD_SO << dlerror() << std::endl; // "ERROR: Failed to load .so file - ?"
					continue;
				}
				handles.push_back(handle);
				dlerror(); // Clear any existing error
				if (loop_size==size()) { // If .so load failed
					std::cout << ERROR_FAILED_LOAD_SO << filename << std::endl; // "ERROR: Failed to load .so file - ?"
					continue;
				}
			}
		}
	}
	closedir(dirp);
	for (i=0;i<size();++i) {
		gamesPerPlayer.push_back(0);
	}
	return 0;
}

void TournamentManager::print_results() { // http://thispointer.com/how-to-sort-a-map-by-value-in-c/
	// Declaring the type of Predicate that accepts 2 pairs and return a bool
	typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor = [](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2) {
		return elem1.second>=elem2.second;
	};
	// Declaring a set that will store the pairs using above comparision logic
	std::set<std::pair<std::string, int>, Comparator> setOfScores(id2score.begin(), id2score.end(), compFunctor);
	// Iterate over a set using range base for loop, It will display the items in sorted order of values
	for (std::pair<std::string, int> element : setOfScores) {
		std::cout << "The score of " << element.first << " is " << element.second << std::endl;
	}
}

void TournamentManager::worker() {
	int thread_ret;
	GameManager gamemanager;
	std::unique_ptr<PlayerAlgorithm> players[2];
	while (1) {
		gamemanager = GameManager();
		match_mutex.lock();
		if (gamesArray.size()<=next_game) {
			break;
		}
		int player_1_index = gamesArray[next_game].first;
		int player_2_index = gamesArray[next_game].second;
		players[0] = std::move(id2factory[getAlgorithmName(player_1_index)]());
		players[1] = std::move(id2factory[getAlgorithmName(player_2_index)]());
		gamesPerPlayer[player_1_index]++;
		gamesPerPlayer[player_2_index]++;
		next_game++;
		match_mutex.unlock();
		thread_ret = -1; // thread_ret = 0 tie, 1 if player 1 win and 2 if player 2 win
		gamemanager.play(players, thread_ret);
		score_mutex.lock();
		if (thread_ret==0) {
			updateScore(getAlgorithmName(player_1_index),1);
			updateScore(getAlgorithmName(player_2_index),1);
		} else if (thread_ret==1) {
			updateScore(getAlgorithmName(player_1_index),3);
		} else if (thread_ret==2) {
			updateScore(getAlgorithmName(player_2_index),3);
		}
		score_mutex.unlock();
	}
	match_mutex.unlock();
}

bool is_number(const std::string& s) { // https://stackoverflow.com/a/4654718
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) {return !std::isdigit(c);})==s.end();
}

int main(int argc, char* argv[]) {
	// Check correct call structure
	int f_t = 0;
	int f_p = 0;
	long unsigned max_threads = 4;
	std::string path = "./";
	if (argc>5) {
		std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
		return EXIT_FAILURE;
	}
	if (argc>=3) {
		if (strcmp(argv[1],"-threads")==0) { // strcmp() functions return an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
			if (!is_number(std::string(argv[2]))) {
				std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
				return EXIT_FAILURE;
			}
			max_threads = atol(argv[2]); // atol() Return the converted value.
			f_t = 1;
		} else if (strcmp(argv[1],"-path")==0) { // strcmp() functions return an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
			path = argv[2];
			f_p = 1;
		} else {
			std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
			return EXIT_FAILURE;
		}
	}
	if (argc==5) {
		if ((strcmp(argv[3],"-threads")==0)&&(f_t==0)) { // strcmp() functions return an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
			if (!is_number(std::string(argv[4]))) {
				std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
				return EXIT_FAILURE;
			}
			max_threads = atol(argv[4]); // atol() Return the converted value.
		} else if ((strcmp(argv[3],"-path")==0)&&(f_p==0)) { // strcmp() functions return an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
			path = argv[4];
		} else {
			std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
			return EXIT_FAILURE;
		}
	}
	if ((0==max_threads)||(LONG_MAX<=max_threads)) {
		std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
		return EXIT_FAILURE;
	}
	TournamentManager& manager = TournamentManager::getTournamentManager();
	if (manager.go(max_threads, path)==1) {
		std::cout << ERROR_INVALID_ARGS << std::endl << ERROR_USAGE << std::endl; // "ERROR: Invalid arguments" "Usage: ex3 [-threads <num_threads>] [-path <location_of_algorithms>]"
		return EXIT_FAILURE;
	} else {
		manager.id2factoryClear();
		return EXIT_SUCCESS;
	}
}
