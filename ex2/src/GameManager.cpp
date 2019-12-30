/*
 * GameManager.cpp
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: The 'GameManager' class manage the game and update the game status for each player.
 * 		This department is responsible for passing relevant information about the status of the game to the 'PlayerAlgorithm'.
 * 		The 'PlayerAlgorithm' decide it's move, which will return to the 'GameManager'.
 * 		This class manages the game at a higher level than the helper class - 'GameBoard'.
 */

#include "GameManager.h"

////////////////////////////////////////////////////////////////////
////	GameManager 						////
////////////////////////////////////////////////////////////////////
GameManager::GameManager() {
	int i,j; // 1<=i<=M 1<=j<=N
	board = GameManagerBoard();
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			board_player1[i-1][j-1] = EMPTY; // 1<=i<=M 1<=j<=N
			board_player2[i-1][j-1] = EMPTY; // 1<=i<=M 1<=j<=N
		}
	}
	board = GameManagerBoard();
	current_player = -1;
	gameover_reason = REASON_UNKNOWN;
	gameover_winner = -1;
}

////////////////////////////////////////////////////////////////////
////	GameManager functions					////
////////////////////////////////////////////////////////////////////
// The function check if we have a winner, Return 1 if game is still on and 0 otherwise // winner = -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
int GameManager::checkGameOver() {
	if (gameover_winner!=-1) {
		return 0;
	}
	int unmovable_pieces_player1 = ((player1_pieces_counters[ROCK]==0)&&(player1_pieces_counters[PAPER]==0)&&
					(player1_pieces_counters[SCISSORS]==0)&&(player1_pieces_counters[JOKER_ROCK]==0)&&
					(player1_pieces_counters[JOKER_PAPER]==0)&&(player1_pieces_counters[JOKER_SCISSORS]==0))?1:0;
	int unmovable_pieces_player2 = ((player2_pieces_counters[ROCK]==0)&&(player2_pieces_counters[PAPER]==0)&&
					(player2_pieces_counters[SCISSORS]==0)&&(player2_pieces_counters[JOKER_ROCK]==0)&&
					(player2_pieces_counters[JOKER_PAPER]==0)&&(player2_pieces_counters[JOKER_SCISSORS]==0))?1:0;
	if ((player1_pieces_counters[FLAG]==0)&&(player2_pieces_counters[FLAG]==0)) { // All flags of the opponent are captured
		gameover_reason = REASON_TIE_ALL_EATEN; // "All moving PIECEs of the opponent are eaten"
		gameover_winner = 0; // Tie
	} else if (player1_pieces_counters[FLAG]==0) {
		gameover_reason = REASON_ALL_CAPTURED; // "All flags of the opponent are captured"
		gameover_winner = 2; // Player 1 win
	} else if (player2_pieces_counters[FLAG]==0) {
		gameover_reason = REASON_ALL_CAPTURED; // "All flags of the opponent are captured"
		gameover_winner = 1; // Player 0 win
	} else if ((unmovable_pieces_player1)&&(unmovable_pieces_player2==1)) { // Check if there are pieces that can move
		std::cout << MSG_NO_MORE_MOVES_BOTH << std::endl;
		gameover_reason = REASON_TIE_NO_MORE_MOVES; // "A tie - both Moves input files done without a winner"
		gameover_winner = 0; // Tie
	} else if (unmovable_pieces_player1==1) {
		gameover_reason = REASON_ALL_EATEN; // "All moving PIECEs of the opponent are eaten"
		gameover_winner = 2; // Player 1 win
	} else if (unmovable_pieces_player2==1) {
		gameover_reason = REASON_ALL_EATEN; // "All moving PIECEs of the opponent are eaten"
		gameover_winner = 1; // Player 0 win
	} else {
		gameover_reason = REASON_UNKNOWN;
		gameover_winner = -1; // Game still on
		return 1;
	}
	return 0;
}

// Compare between the two positioning boards, If there is a fight remove the loser, Set FightInfo vector of the positioning fights
void GameManager::compareBoards(std::vector<std::unique_ptr<FightInfo>>& fights) {
	int i,j; // 1<=i<=M 1<=j<=N
	int loop_fight_winner;
	char player_1,player_2;
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			player_1 = board_player1[i-1][j-1]; // 1<=i<=M 1<=j<=N
			player_2 = board_player2[i-1][j-1]; // 1<=i<=M 1<=j<=N
			if ((player_1!=EMPTY)&&(player_2!=EMPTY)) { // We have a fight
				loop_fight_winner = fightInit(player_1,player_2, i, j); // fightInit() Return 0 if both lost, 1 if first piece win, 2 if second piece win
				unique_ptr<FightInfoRPS> unique_fight = std::make_unique<FightInfoRPS>(PointRPS(i,j), hideJokerTypeRep(player_1), hideJokerTypeRep(player_2), loop_fight_winner); // hideJokerTypeRep() Return R, P, S, B or F
				fights.push_back(std::move(unique_fight));
			}
		}
	}
}

// Create the game output file based on 'gameover_reason' and 'gameover_winner'
void GameManager::createOutputFile() {
	std::ofstream output_file;
	output_file.open(FILE_OUTPUT);
	if ((output_file.is_open())&&(gameover_winner>=0)&&(gameover_winner<=2)) { // is_open() Return true if the file stream has an associated file, false otherwise
		output_file << MSG_OUTPUT_WINNER << gameover_winner << std::endl; // Winner equal -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
		switch (gameover_reason) {
			case REASON_ALL_CAPTURED:
				output_file << MSG_OUTPUT_REASON << MSG_ALL_CAPTURED << std::endl; // "All flags of the opponent are captured"
				break;
			case REASON_ALL_EATEN:
				output_file << MSG_OUTPUT_REASON << MSG_ALL_EATEN << std::endl; // "All moving PIECEs of the opponent are eaten"
				break;
			case REASON_TIE_NO_MORE_MOVES:
				output_file << MSG_OUTPUT_REASON << MSG_TIE_NO_MORE_MOVES << std::endl; // "A tie - both Moves input files done without a winner"
				break;
			case REASON_TIE_ALL_EATEN:
				output_file << MSG_OUTPUT_REASON << MSG_TIE_ALL_EATEN << std::endl; // "A tie - all flags are eaten by both players in the position files"
				break;
			case REASON_BAD_POSITION_1:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_POSITION_1 << std::endl; // "Reason: Bad Positioning input file for player 1"
				break;
			case REASON_BAD_POSITION_2:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_POSITION_2 << std::endl; // "Reason: Bad Positioning input file for player 2"
				break;
			case REASON_BAD_POSITION_BOTH:
				output_file << MSG_OUTPUT_REASON << MSG_BAD_POSITION_BOTH << std::endl; // "Bad Positioning input file for both players"
				break;
			case REASON_BAD_MOVES:
				if (gameover_winner==1) {
					output_file << MSG_OUTPUT_REASON << MSG_BAD_MOVES_2 << std::endl; // "Bad Moves input file for player 2"
				} else {
					output_file << MSG_OUTPUT_REASON << MSG_BAD_MOVES_1 << std::endl; // "Bad Moves input file for player 1"
				}
				break;
			default: // Never should happen
				return;
				break;
		}
		output_file << std::endl; // The 3rd line would be: an empty line
		printBoard(output_file); // Print the game board at the end of the output file
		output_file.close();
	}
}

// Decrease the piece counter for the selected player
void GameManager::counterDecrease(char piece, int player) {
	(player==1)?player1_pieces_counters[piece]--:player2_pieces_counters[piece]--;
	if ((piece==JOKER_ROCK)||(piece==JOKER_PAPER)||(piece==JOKER_SCISSORS)||(piece==JOKER_BOMB)) {
		(player==1)?player1_pieces_counters[JOKER]--:player2_pieces_counters[JOKER]--;
	}
}

// Perform a fight between two pieces, Return 0 if both lost, 1 if first piece win, 2 if second piece win
int GameManager::fight(char piece_1, char piece_2) {
	//						Player 0
	//			R	P	S	B	F	J_R	J_P	J_S	J_B
	//		R	B	0	1	B	1	B	0	1	B
	//		P	1	B	0	B	1	1	B	0	B
	//		S	0	1	B	B	1	0	1	B	B
	//		B	B	B	B	B	B	B	B	B	B
	// player 1	F	1	1	1	B	B	1	1	1	B
	//		J_R	B	0	1	B	1	B	0	1	B
	//		J_P	1	B	0	B	1	1	B	0	B
	//		J_S	0	1	B	B	1	0	1	B	B
	//		J_B	B	B	B	B	B	B	B	B	B
	int player_1_lose = 1;
	int player_2_lose = 1;
	switch (piece_1) {
		case ROCK: case JOKER_ROCK: // ROCK can survive only SCISSORS & JOKER_SCISSORS & FLAG
			if ((piece_2==SCISSORS)||(piece_2==JOKER_SCISSORS)||(piece_2==FLAG)) {
				player_1_lose = 0;
			}
			break;
		case PAPER: case JOKER_PAPER: // PAPER can survive only ROCK & JOKER_ROCK & FLAG
			if ((piece_2==ROCK)||(piece_2==JOKER_ROCK)||(piece_2==FLAG)) {
				player_1_lose = 0;
			}
			break;
		case SCISSORS: case JOKER_SCISSORS: // SCISSORS can survive only PAPER & JOKER_PAPER & FLAG
			if ((piece_2==PAPER)||(piece_2==JOKER_PAPER)||(piece_2==FLAG)) {
				player_1_lose = 0;
			}
			break;
	}
	switch (piece_2) {
		case ROCK: case JOKER_ROCK: // ROCK can survive only SCISSORS & JOKER_SCISSORS & FLAG
			if ((piece_1==SCISSORS)||(piece_1==JOKER_SCISSORS)||(piece_1==FLAG)) {
				player_2_lose = 0;
			}
			break;
		case PAPER: case JOKER_PAPER: // PAPER can survive only ROCK & JOKER_ROCK & FLAG
			if ((piece_1==ROCK)||(piece_1==JOKER_ROCK)||(piece_1==FLAG)) {
				player_2_lose = 0;
			}
			break;
		case SCISSORS: case JOKER_SCISSORS: // SCISSORS can survive only PAPER & JOKER_PAPER & FLAG
			if ((piece_1==PAPER)||(piece_1==JOKER_PAPER)||(piece_1==FLAG)) {
				player_2_lose = 0;
			}
			break;
	}
	if ((player_1_lose==0)&&(player_2_lose==1)) {
		return 1; // Return 1 if only player 1 win
	} else if ((player_1_lose==1)&&(player_2_lose==0)) {
		return 2; // Return 2 if only player 2 win
	} else {
		return 0; // Return 0 if both lost
	}
}

// Fight function is called ONLY if (x,y) at both boards isn't empty, Return 0 if both lost, 1 if first piece win, 2 if second piece win
int GameManager::fightInit(char piece_1, char piece_2, int x, int y) {
	int fight_winner = fight(piece_1, piece_2); // fight() Return 0 if both lost, 1 if first piece win, 2 if second piece win
	if (fight_winner!=1) {
		counterDecrease(board_player1[x-1][y-1],1); // counterDecrease() Is decreasing the piece counter for the selected player
		board_player1[x-1][y-1] = EMPTY; // 1<=x<=M 1<=y<=N
	}
	if (fight_winner!=2) {
		counterDecrease(board_player2[x-1][y-1],2); // counterDecrease() Is decreasing the piece counter for the selected player
		board_player2[x-1][y-1] = EMPTY; // 1<=x<=M 1<=y<=N
	}
	return fight_winner;
}

// Fight function is called ONLY if (x,y) at both boards isn't empty, Perform the move and return FightInfo for the fight
std::unique_ptr<FightInfoRPS> GameManager::fightMove(char piece_from, char piece_to, const Point& from, const Point& to) {
	int winner_player;
	int fight_winner = fight(piece_from,piece_to); // fight() Return 0 if both lost, 1 if first piece win, 2 if second piece win
	int player_from = board.getPlayer(from); // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
	int player_to = board.getPlayer(to); // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
	if (fight_winner==1) { // the destination lose the fight
		counterDecrease(piece_to,player_to); // counterDecrease() Is decreasing the piece counter for the selected player
		board.killPiece(to); // GameManagerBoard.killPiece() Remove the piece of the selected player from the board
		board.move(from,to,player_from); // GameManagerBoard.move() Move the piece of the selected player
		winner_player = player_from;
	} else if (fight_winner==2) { // The destination win the fight
		counterDecrease(piece_from,player_from); // counterDecrease() Is decreasing the piece counter for the selected player
		board.killPiece(from); // GameManagerBoard.killPiece() Remove the piece of the selected player from the board
		winner_player = player_to;
	} else { // Tie
		counterDecrease(piece_from,player_from); // counterDecrease() Is decreasing the piece counter for the selected player
		counterDecrease(piece_to,player_to); // counterDecrease() Is decreasing the piece counter for the selected player
		board.killPiece(from); // GameManagerBoard.killPiece() Remove the piece of the selected player from the board
		board.killPiece(to); // GameManagerBoard.killPiece() Remove the piece of the selected player from the board
		winner_player = 0;
	}
	unique_ptr<FightInfoRPS> unique_fight = std::make_unique<FightInfoRPS>(to,hideJokerTypeRep(piece_from),hideJokerTypeRep(piece_to),winner_player); // hideJokerTypeRep() Return R, P, S, B or F
	return unique_fight;
}

// Create Board object based on the current game board
std::unique_ptr<BoardRPS> GameManager::getBoard() {
	int i,j; // 1<=i<=M 1<=j<=N
	int current_board[M_COLS][N_ROWS];
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			PointRPS loop_point = PointRPS(i,j);
			current_board[i-1][j-1] = board.getPlayer(loop_point); // 1<=i<=M 1<=j<=N // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
		}
	}
	return std::make_unique<BoardRPS>(current_board);
}

// Return the type of the piece while hiding joker representation, Return R, P, S, B, F or J
char GameManager::hideJokerTypeJ(char piece) {
	if ((piece==JOKER_ROCK)||(piece==JOKER_PAPER)||(piece==JOKER_SCISSORS)||(piece==JOKER_BOMB)) {
		return JOKER;
	} else {
		return piece;
	}
}

// Return the type of the piece while hiding jokers, Return R, P, S, B or F
char GameManager::hideJokerTypeRep(char piece) {
	switch (piece) {
		case JOKER_ROCK: return ROCK;
			break;
		case JOKER_PAPER: return PAPER;
			break;
		case JOKER_SCISSORS: return SCISSORS;
			break;
		case JOKER_BOMB: return BOMB;
			break;
		default: return piece;
	}
}

// Init the game with two positioning vectors, Set ret to 0 if success and 1 otherwise, Return FightInfo vector of all the positioning fights
std::vector<std::unique_ptr<FightInfo>> GameManager::initialize(int& ret, std::vector<std::unique_ptr<PiecePosition>>& player1_locations, std::vector<std::unique_ptr<PiecePosition>>& player2_locations) {
	int i,j; // 1<=i<=M 1<=j<=N
	int res1=0,res2=0;
	std::vector<std::unique_ptr<FightInfo>> fights;
	for (auto& obj : player1_locations) {
		if ((res1 = positioning(*obj.get(), 1))==1) { // positioning() Return 0 if success and 1 otherwise
			break;
		}
	}
	for (auto& obj : player2_locations) {
		if ((res2 = positioning(*obj.get(), 2))==1) { // positioning() Return 0 if success and 1 otherwise
			break;
		}
	}
	if (player1_pieces_counters[FLAG]==0) { // Count how many flags player 1 have
		std::cout << ERROR_PLAYER_NUM << 1 << ERROR_NO_FLAGS_B << std::endl; // "ERROR: Player 1 - There must be at least one flag"
		res1=1;
	}
	if (player2_pieces_counters[FLAG]==0) { // Count how many flags player 2 have
		std::cout << ERROR_PLAYER_NUM << 2 << ERROR_NO_FLAGS_B << std::endl; // "ERROR: Player 2 - There must be at least one flag"
		res2=1;
	}
	if ((res1==0)&&(res2==0)) {
		compareBoards(fights); // compareBoards() Set FightInfo vector of the positioning fights
		for (i=1;i<=M_COLS;++i) { // M_COLS is x
			for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
				if (board_player1[i-1][j-1]!=EMPTY) { // 1<=i<=M 1<=j<=N
					unique_ptr<PiecePositionRPS> unique_piece = std::make_unique<PiecePositionRPS>(board_player1[i-1][j-1],PointRPS(i, j),pieceIsJoker(board_player1[i-1][j-1]),1); // pieceIsJoker() Return JOKER_TRUE if piece is joker and JOKER_FALSE otherwise
					board.addPiecePosition(unique_piece,1);
				} else if (board_player2[i-1][j-1]!=EMPTY) { // 1<=i<=M 1<=j<=N
					unique_ptr<PiecePositionRPS> unique_piece = std::make_unique<PiecePositionRPS>(board_player2[i-1][j-1],PointRPS(i, j),pieceIsJoker(board_player2[i-1][j-1]),2); // pieceIsJoker() Return JOKER_TRUE if piece is joker and JOKER_FALSE otherwise
					board.addPiecePosition(unique_piece,2);
				}
			}
		}
		ret = 0;
	} else {
		if ((res1!=0)&&(res2!=0)) { // Both players are invalid
			gameover_winner = 0; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
			gameover_reason = REASON_BAD_POSITION_BOTH; // "Bad Positioning input file for both players"
		} else if (res2!=0) { // Only player 2 have error
			gameover_winner = 1; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
			gameover_reason = REASON_BAD_POSITION_2; // "Bad Positioning input file for player 2"
		} else if (res1!=0) { // Only player 1 have error
			gameover_winner = 2; // -1 game is on, 0 tie, 1 if player 1 win and 2 if player 2 win
			gameover_reason = REASON_BAD_POSITION_1; // "Bad Positioning input file for player 1"
		}
		ret = 1;
	}
	return fights;
}

// Change the selected joker representation, Return 0 on success and 1 otherwise
int GameManager::jokerCommand(JokerChange& joker_change) {
	char new_piece = joker_change.getJokerNewRep(); // JokerChange.getJokerNewRep() Return R, P, S or B (but NOT J and NOT F)
	int x = joker_change.getJokerChangePosition().getX();
	int y = joker_change.getJokerChangePosition().getY();
	char old_piece = board.getPiece(PointRPS(x,y)); // GameManagerBoard.getPiece() Return R, P, S, B, J, F or EMPTY
	if ((x<1)||(x>M_COLS)) {
		std::cout << ERROR_X << x << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: X coordinate '?' is out of range"
		return 1;
	}
	if ((y<1)||(y>N_ROWS)) {
		std::cout << ERROR_Y << y << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: Y coordinate '?' is out of range"
		return 1;
	}
	if (old_piece!=JOKER_ROCK&&old_piece!=JOKER_PAPER&&old_piece!=JOKER_SCISSORS&&old_piece!=JOKER_BOMB) {
		std::cout << ERROR_CHANGE_JOKER << old_piece << std::endl; // "ERROR: You cannot change piece of type "
		return 1; // Invalid piece
	}
	switch (new_piece) {
		case ROCK: new_piece = JOKER_ROCK;
			break;
		case PAPER: new_piece = JOKER_PAPER;
			break;
		case SCISSORS: new_piece = JOKER_SCISSORS;
			break;
		case BOMB: new_piece = JOKER_BOMB;
			break;
		default: std::cout << ERROR_CHANGE_PIECE << new_piece << std::endl; // "ERROR: You cannot change your joker to be "
			return 1; // Invalid piece
			break;
	}
	PointRPS temp_point = PointRPS(x,y);
	if (board.changeJoker(new_piece,temp_point,current_player)==1) { // GameManagerBoard.changeJoker() Return 0 on success and 1 otherwise
		std::cout << ERROR_NO_JOKER <<std::endl; // "ERROR: You don't have joker at the selected destination"
		return 1; // Position doesn't exist.
	}
	if (current_player==1) {
		player1_pieces_counters[old_piece]--;
		player1_pieces_counters[new_piece]++;
	} else {
		player2_pieces_counters[old_piece]--;
		player2_pieces_counters[new_piece]++;
	}
	return 0;
}

// Perform a move, Return FightInfo if there was a fight and nullptr otherwise, Set ret to 0 if success and 1 otherwise
std::unique_ptr<FightInfoRPS> GameManager::move(Move& player_move, int& ret) {
	std::unique_ptr<FightInfoRPS> fight = nullptr;
	int res = validateMove(player_move.getFrom(), player_move.getTo()); // validateMove() Return 0 if he can't move, 1 if he can and 2 if there is opponent piece at the destination
	if (res==0) { // Invalid move
		ret = 1;
		std::cout << ERROR_MOVE_FROM << "(" << player_move.getFrom().getX() << "," << player_move.getFrom().getY() << ")" << ERROR_MOVE_TO << "(" << player_move.getTo().getX() << "," << player_move.getTo().getY() << ")" << std::endl; // "ERROR: You cannot move your piece from (?,?) to (?,?)"
		return std::move(fight);
	} else if (res==1) { // The destination is empty
		board.move(player_move.getFrom(), player_move.getTo(), current_player); // GameManagerBoard.move() Move the piece of the selected player
	} else { // There is opponent piece at the destination
		fight = fightMove(board.getPiece(player_move.getFrom()), board.getPiece(player_move.getTo()), player_move.getFrom(), player_move.getTo()); // fightMove() Perform the move and return FightInfo for the fight
	}
	ret = 0;
	return std::move(fight); // Success
}

// Return JOKER_TRUE if piece is joker and JOKER_FALSE otherwise
char GameManager::pieceIsJoker(char piece) {
	switch (piece) {
		case JOKER: return JOKER_TRUE;
			break;
		case JOKER_ROCK: return JOKER_TRUE;
			break;
		case JOKER_PAPER: return JOKER_TRUE;
			break;
		case JOKER_SCISSORS: return JOKER_TRUE;
			break;
		case JOKER_BOMB: return JOKER_TRUE;
			break;
		default: return JOKER_FALSE;
			break;
	}
}

// Put a new piece to the board, Return 0 if success and 1 otherwise
int GameManager::positioning(PiecePosition& piece_position, int player) {
	int x = piece_position.getPosition().getX();
	int y = piece_position.getPosition().getY();
	char piece = piece_position.getPiece(); // PiecePosition.getPiece() Return R, P, S, B, J or F
	char is_joker = piece_position.getJokerRep(); // PiecePosition.getJokerRep() Return JOKER_TRUE ONLY for Joker: R, P, S or B -- non-Joker return JOKER_FALSE
	if (validation(piece_position,player)==0) { // validation() Return 0 if valid and 1 otherwise
		if (is_joker==JOKER_FALSE) {
			(player==1)?board_player1[x-1][y-1]=piece:board_player2[x-1][y-1]=piece;
			counterIncrease(piece, player); // counterIncrease() Is increasing the piece counter for the selected player
		} else {
			counterIncrease(JOKER, player); // counterIncrease() Is increasing the piece counter for the selected player
			switch (piece) {
				case ROCK: (player==1)?board_player1[x-1][y-1]=JOKER_ROCK:board_player2[x-1][y-1]=JOKER_ROCK;
					counterIncrease(JOKER_ROCK, player); // counterIncrease() Is increasing the piece counter for the selected player
					break;
				case PAPER: (player==1)?board_player1[x-1][y-1]=JOKER_PAPER:board_player2[x-1][y-1]=JOKER_PAPER;
					counterIncrease(JOKER_PAPER, player); // counterIncrease() Is increasing the piece counter for the selected player
					break;
				case SCISSORS: (player==1)?board_player1[x-1][y-1]=JOKER_SCISSORS:board_player2[x-1][y-1]=JOKER_SCISSORS;
					counterIncrease(JOKER_SCISSORS, player); // counterIncrease() Is increasing the piece counter for the selected player
					break;
				case BOMB: (player==1)?board_player1[x-1][y-1]=JOKER_BOMB:board_player2[x-1][y-1]=JOKER_BOMB;
					counterIncrease(JOKER_BOMB, player); // counterIncrease() Is increasing the piece counter for the selected player
					break;
			}
		}
		return 0;
	} else {
		std::cout << ERROR_PLAYER_NUM << player << ERROR_POSITIONING_FAILED_B << piece << ERROR_AT << "(" << x << "," << y << ")" << std::endl; // "ERROR: Player ? - Couldn't put the piece '?' at (?,?)"
		return 1;
	}
}

// Print the game board at the end of the output file
void GameManager::printBoard(std::ofstream& output_file) {
	int i,j; // 1<=i<=M 1<=j<=N
	char piece_at;
	for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
		for (i=1;i<=M_COLS;++i) { // M_COLS is x
			PointRPS loop_point = PointRPS(i,j); // 1<=i<=M 1<=j<=N
			piece_at = board.getPiece(loop_point); // GameManagerBoard.getPiece() Return R, P, S, B, J, F or EMPTY
			piece_at = hideJokerTypeJ(piece_at); // hideJokerTypeJ() Return R, P, S, B, F or J
			if (board.getPlayer(loop_point)==1) { // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
				piece_at = toupper(piece_at);
				output_file << piece_at; // 1<=i<=M 1<=j<=N
			} else if (board.getPlayer(loop_point)==2) { // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
				piece_at = tolower(piece_at);
				output_file << piece_at; // 1<=i<=M 1<=j<=N
			} else {
				output_file << EMPTY;
			}
		}
		output_file << std::endl;
	}
}

// This is a support function that print to the screen the status of both boards and the pieces counters
void GameManager::printBoardExtra() {
	int i,j; // 1<=i<=M 1<=j<=N
	char piece_at;
	std::cout << "  |1234567890|                     +----------+----------+" << std::endl;
	std::cout << "--+----------+--                   | Player 1 | Player 2 |" << std::endl;
	for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
		std::cout << std::setw(2) << j << "|";
		for (i=1;i<=M_COLS;++i) { // M_COLS is x
			PointRPS loop_point = PointRPS(i,j); // 1<=i<=M 1<=j<=N
			piece_at = board.getPiece(loop_point); // GameManagerBoard.getPiece() Return R, P, S, B, J, F or EMPTY
			piece_at = hideJokerTypeJ(piece_at); // hideJokerTypeJ() Return R, P, S, B, F or J
			if (board.getPlayer(loop_point)==1) { // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
				piece_at = toupper(piece_at);
				std::cout << piece_at; // 1<=i<=M 1<=j<=N
			} else if (board.getPlayer(loop_point)==2) { // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
				piece_at = tolower(piece_at);
				std::cout << piece_at; // 1<=i<=M 1<=j<=N
			} else {
				std::cout << EMPTY;
			}
		}
		std::cout << "|" << std::setw(2) << j << "  ";
		switch (j) {
			case 1: std::cout << "+----------------+----------+----------+" << std::endl;
				break;
			case 2: std::cout << "| ROCK           | " << std::setw(8) << getCounter(ROCK,1) << " | " << std::setw(8) << getCounter(ROCK,2) << " |" << std::endl;
				break;
			case 3: std::cout << "| PAPER          | " << std::setw(8) << getCounter(PAPER,1) << " | " << std::setw(8) << getCounter(PAPER,2) << " |" << std::endl;
				break;
			case 4: std::cout << "| SCISSORS       | " << std::setw(8) << getCounter(SCISSORS,1) << " | " << std::setw(8) << getCounter(SCISSORS,2) << " |" << std::endl;
				break;
			case 5: std::cout << "| BOMB           | " << std::setw(8) << getCounter(BOMB,1) << " | " << std::setw(8) << getCounter(BOMB,2) << " |" << std::endl;
				break;
			case 6: std::cout << "| FLAG           | " << std::setw(8) << getCounter(FLAG,1) << " | " << std::setw(8) << getCounter(FLAG,2) << " |" << std::endl;
				break;
			case 7: std::cout << "| JOKER          | " << std::setw(8) << getCounter(JOKER,1) << " | " << std::setw(8) << getCounter(JOKER,2) << " |" << std::endl;
				break;
			case 8: std::cout << "| JOKER_ROCK     | " << std::setw(8) << getCounter(JOKER_ROCK,1) << " | " << std::setw(8) << getCounter(JOKER_ROCK,2) << " |" << std::endl;
				break;
			case 9: std::cout << "| JOKER_PAPER    | " << std::setw(8) << getCounter(JOKER_PAPER,1) << " | " << std::setw(8) << getCounter(JOKER_PAPER,2) << " |" << std::endl;
				break;
			case 10: std::cout << "| JOKER_SCISSORS | " << std::setw(8) << getCounter(JOKER_SCISSORS,1) << " | " << std::setw(8) << getCounter(JOKER_SCISSORS,2) << " |" << std::endl;
				break;
		}
	}
	std::cout << "--+----------+--  | JOKER_BOMB     | " << std::setw(8) << getCounter(JOKER_BOMB,1) << " | " << std::setw(8) << getCounter(JOKER_BOMB,1) << " |" << std::endl;
	std::cout << "  |1234567890|    *----------------*----------*----------*" << std::endl;
	std::cout << "=============================================================" << std::endl;
}

// Check if the player can move, Return 0 if he can't move, 1 if he can and 2 if there is opponent piece at the destination
int GameManager::validateMove(const Point& from, const Point& to) {
	if ((from.getX()<1)||(from.getX()>M_COLS)) {
		std::cout << ERROR_X_SOURCE << from.getX() << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: Source X coordinate '?' is out of range"
		return 0;
	} else if ((to.getX()<1)||(to.getX()>M_COLS)) {
		std::cout << ERROR_X_DESTINATION << to.getX() << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: Destination X coordinate '?' is out of range"
		return 0;
	} else if ((from.getY()<1)||(from.getY()>N_ROWS)) {
		std::cout << ERROR_Y_SOURCE << from.getY() << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: Source Y coordinate '?' is out of range"
		return 0;
	} else if ((to.getY()<1)||(to.getY()>N_ROWS)) {
		std::cout << ERROR_Y_DESTINATION << to.getY() << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: Destination Y coordinate '?' is out of range"
		return 0;
	}
	if ((to.getY()==from.getY()+1)||(to.getY()==from.getY()-1)) {
		if (to.getX()!=from.getX()) {
			std::cout << ERROR_MOVE_LIMITATION << std::endl; // "ERROR: You can only move left, right, up and down"
			return 0;
		}
	} else if ((to.getX()==from.getX()+1)||(to.getX()==from.getX()-1)) {
		if (to.getY()!=from.getY()) {
			std::cout << ERROR_MOVE_LIMITATION << std::endl; // "ERROR: You can only move left, right, up and down"
			return 0;
		}
	} else { // This will also catch if ((x_from==x_to)&&(y_from==y_to))
		std::cout << ERROR_MOVE_LIMITATION << std::endl; // "ERROR: You can only move left, right, up and down"
		return 0;
	}
	char from_piece = board.getPiece(from); // GameManagerBoard.getPiece() Return R, P, S, B, J, F or EMPTY
	int from_player = board.getPlayer(from); // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
	int to_player = board.getPlayer(to); // GameManagerBoard.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
	if (from_player==0) {
		std::cout << ERROR_MOVE_EMPTY << std::endl; // "ERROR: You don't have any piece at your selected start location"
		return 0;
	} else if (from_player!=current_player) {
		std::cout << ERROR_MOVE_OPPONENT_A << current_player << ERROR_MOVE_OPPONENT_B << from_player << std::endl; // "ERROR: You cannot move your opponent, You are ? and he is ?"
		return 0;
	} else if ((from_piece==FLAG)||(from_piece==BOMB)||(from_piece==JOKER_BOMB)) {
		std::cout << ERROR_MOVE_FLAGS_BOMBS << std::endl; // "ERROR: You can't move flag or bomb pieces"
		return 0;
	} else if (to_player==current_player) {
		std::cout << ERROR_DESTINATION_TAKEN << std::endl; // "ERROR: You already have piece at the destination"
		return 0;
	} else if (to_player==0) {
		return 1; //move
	} else {
		return 2;//fight
	}
}

// The function validate that the piece can be entered to the board, Return 0 if valid and 1 otherwise
int GameManager::validation(PiecePosition& piece_position, int player) {
	int x = piece_position.getPosition().getX();
	int y = piece_position.getPosition().getY();
	char piece = piece_position.getPiece(); // PiecePosition.getPiece() Return R, P, S, B, J or F
	char is_joker = piece_position.getJokerRep(); // PiecePosition.getJokerRep() Return JOKER_TRUE ONLY for Joker: R, P, S or B -- non-Joker return JOKER_FALSE
	if ((x<1)||(x>M_COLS)) {
		std::cout << ERROR_X << x << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: X coordinate '?' is out of range"
		return 1;
	}
	if ((y<1)||(y>N_ROWS)) {
		std::cout << ERROR_Y << y << ERROR_OUT_OF_RANGE << std::endl; // "ERROR: Y coordinate '?' is out of range"
		return 1;
	}
	if (player==1) {
		if (board_player1[x-1][y-1]!=EMPTY) {
			std::cout << ERROR_SAME_POSITION << std::endl; // "ERROR: Two or more PIECEs (of same player) are positioned at the same location"
			return 1;
		}
	} else {
		if (board_player2[x-1][y-1]!=EMPTY) {
			std::cout << ERROR_SAME_POSITION << std::endl; // "ERROR: Two or more PIECEs (of same player) are positioned at the same location"
			return 1;
		}
	}
	if (is_joker==JOKER_TRUE) {
		if ((piece!=ROCK)&&(piece!=PAPER)&&(piece!=SCISSORS)&&(piece!=BOMB)) {
			std::cout << ERROR_INVALID_JOKER << piece << std::endl; // "ERROR: Invalid joker type "
			return 1;
		}
		if (getCounter(JOKER,player)>=J_JOKER) {
			std::cout << ERROR_COUNT_JOKER << std::endl; // "ERROR: There are too many jokers"
			return 1;
		}
	} else {
		switch (piece) {
			case ROCK: if (getCounter(ROCK,player)>=R_ROCK) {
					std::cout << ERROR_COUNT_ROCK << std::endl; // "ERROR: There are too many rocks"
					return 1;
				}
				break;
			case PAPER: if (getCounter(PAPER,player)>=P_PAPER) {
					std::cout << ERROR_COUNT_PAPER << std::endl; // "ERROR: There are too many papers"
					return 1;
				}
				break;
			case SCISSORS: if (getCounter(SCISSORS,player)>=S_SCISSORS) {
					std::cout << ERROR_COUNT_SCISSORS << std::endl; // "ERROR: There are too many scissors"
					return 1;
				}
				break;
			case BOMB: if (getCounter(BOMB,player)>=B_BOMB) {
					std::cout << ERROR_COUNT_BOMB << std::endl; // "ERROR: There are too many bombs"
					return 1;
				}
				break;
			case FLAG: if (getCounter(FLAG,player)>=F_FLAG) {
					std::cout << ERROR_COUNT_FLAG << std::endl; // "ERROR: There are too many flags"
					return 1;
				}
				break;
			default: std::cout << ERROR_INVALID_PIECE << piece << std::endl; // "ERROR: Invalid piece type "
				return 1;
				break;
		}
	}
	return 0;
}
