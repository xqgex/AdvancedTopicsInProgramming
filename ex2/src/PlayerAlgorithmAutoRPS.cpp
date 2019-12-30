/*
 * PlayerAlgorithmAutoRPS.cpp
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class PlayerAlgorithm.h
 * 		Smart algorithm for the automatic player.
 * 		This class pass to the 'GameManager' the smartest move it can find in order to win the game.
 */

#include "PlayerAlgorithmAutoRPS.h"

////////////////////////////////////////////////////////////////////
////	PlayerAlgorithmAutoRPS 					////
////////////////////////////////////////////////////////////////////
PlayerAlgorithmAutoRPS::PlayerAlgorithmAutoRPS() {
	int i,j; // 1<=i<=M 1<=j<=N
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			board_his[i-1][j-1] = EMPTY; // 1<=i<=M 1<=j<=N
			board_my[i-1][j-1][0] = EMPTY; // 1<=i<=M 1<=j<=N
			board_my[i-1][j-1][1] = EMPTY; // 1<=i<=M 1<=j<=N
		}
	}
	steps_counter = 0; // How many steps we made towards the target
	last_pos = PointRPS(0,0);
	move_from = PointRPS(0,0);
	move_mode = 0; // 0 is toward the target and 1 is toward the victim (opponent known piece)
	move_to = PointRPS(0,0);
	opponent_number = -1;
	target = PointRPS(0,0);
	whoami = -1;
}

////////////////////////////////////////////////////////////////////
////	Abstract implementation					////
////////////////////////////////////////////////////////////////////
void PlayerAlgorithmAutoRPS::getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill) {
	int mapping[4][8][2] = {{{0,0}, {-2,0}, {2,0},  {-1,1},  {1,1},  {-2,2},  {2,2},  {0,2}},	// Top
				{{0,0}, {0,-2}, {0,2}, {-1,-1}, {-1,1}, {-2,-2}, {-2,2}, {-2,0}},	// Right
				{{0,0}, {-2,0}, {2,0}, {-1,-1}, {1,-1}, {-2,-2}, {2,-2}, {0,-2}},	// Bottom
				{{0,0}, {0,-2}, {0,2},  {1,-1},  {1,1},  {2,-2},  {2,2},  {2,0}}};	// Left
	int flag_x, flag_y;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist_1(0,3);
	std::uniform_int_distribution<int> dist_2(3,M_COLS-2);
	std::uniform_int_distribution<int> dist_3(3,N_ROWS-2);
	whoami = player;
	opponent_number = (whoami==1)?2:1;
	// Decide where the flag will be (The position of the defenders is realative to the flag)
	int side = dist_1(mt); // Random in range [0,3]
	if (side==0) {
		flag_x = dist_2(mt); // Random in range [3,M-2]
		flag_y = 1;
	} else if (side==1) {
		flag_x = M_COLS;
		flag_y = dist_3(mt); // Random in range [3,N-2]
	} else if (side==2) {
		flag_x = dist_2(mt); // Random in range [3,M-2]
		flag_y = N_ROWS;
	} else {
		flag_x = 1;
		flag_y = dist_3(mt); // Random in range [3,N-2]
	}
	// Defenders
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(FLAG,PointRPS(flag_x+mapping[side][0][0],flag_y+mapping[side][0][1]),JOKER_FALSE,whoami)); // Flag
	board_my[flag_x+mapping[side][0][0]-1][flag_y+mapping[side][0][1]-1][0] = FLAG;
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(BOMB,PointRPS(flag_x+mapping[side][1][0],flag_y+mapping[side][1][1]),JOKER_FALSE,whoami)); // Bomb 1/2
	board_my[flag_x+mapping[side][1][0]-1][flag_y+mapping[side][1][1]-1][0] = BOMB;
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(BOMB,PointRPS(flag_x+mapping[side][2][0],flag_y+mapping[side][2][1]),JOKER_FALSE,whoami)); // Bomb 2/2
	board_my[flag_x+mapping[side][2][0]-1][flag_y+mapping[side][2][1]-1][0] = BOMB;
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(SCISSORS,PointRPS(flag_x+mapping[side][3][0],flag_y+mapping[side][3][1]),JOKER_TRUE,whoami)); // Joker 1/2 as Scissors
	board_my[flag_x+mapping[side][3][0]-1][flag_y+mapping[side][3][1]-1][0] = JOKER_SCISSORS;
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(SCISSORS,PointRPS(flag_x+mapping[side][4][0],flag_y+mapping[side][4][1]),JOKER_TRUE,whoami)); // Joker 2/2 as Scissors
	board_my[flag_x+mapping[side][4][0]-1][flag_y+mapping[side][4][1]-1][0] = JOKER_SCISSORS;
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(PAPER,PointRPS(flag_x+mapping[side][5][0],flag_y+mapping[side][5][1]),JOKER_FALSE,whoami)); // paper 1/5
	board_my[flag_x+mapping[side][5][0]-1][flag_y+mapping[side][5][1]-1][0] = PAPER;
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(PAPER,PointRPS(flag_x+mapping[side][6][0],flag_y+mapping[side][6][1]),JOKER_FALSE,whoami)); // paper 2/5
	board_my[flag_x+mapping[side][6][0]-1][flag_y+mapping[side][6][1]-1][0] = PAPER;
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(ROCK,PointRPS(flag_x+mapping[side][7][0],flag_y+mapping[side][7][1]),JOKER_FALSE,whoami)); // Rock 1/2
	board_my[flag_x+mapping[side][7][0]-1][flag_y+mapping[side][7][1]-1][0] = ROCK;
	// Fighters
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(PAPER,getAvailablePoint(PAPER),JOKER_FALSE,whoami)); // paper 3/5 // getAvailablePoint() Return available point at the board
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(PAPER,getAvailablePoint(PAPER),JOKER_FALSE,whoami)); // paper 4/5 // getAvailablePoint() Return available point at the board
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(PAPER,getAvailablePoint(PAPER),JOKER_FALSE,whoami)); // paper 5/5 // getAvailablePoint() Return available point at the board
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(ROCK,getAvailablePoint(ROCK),JOKER_FALSE,whoami)); // Rock 2/2 // getAvailablePoint() Return available point at the board
	vectorToFill.push_back(std::make_unique<PiecePositionRPS>(SCISSORS,getAvailablePoint(SCISSORS),JOKER_FALSE,whoami)); // Scissors 1/1 // getAvailablePoint() Return available point at the board
}

void PlayerAlgorithmAutoRPS::notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) {
	int i,j; // 1<=i<=M 1<=j<=N
	int player_at;
	// Get all the location of the opponent pieces
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			PointRPS loop_point = PointRPS(i,j);
			player_at = b.getPlayer(loop_point); // Board.getPlayer() Return 1 for player 1's piece, 2 for 2, 0 if empty
			if (player_at==opponent_number) {
				board_his[i-1][j-1] = UNKNOWN; // 1<=i<=M 1<=j<=N
			}
		}
	}
	// If there was fights, We can learn what pieces we lost and uncover opponent pieces type
	for (auto& obj : fights) {
		notifyFightResult(*obj.get());
	}
	// Guess what is the opponent's flag
	findTarget();
}

void PlayerAlgorithmAutoRPS::notifyOnOpponentMove(const Move& move) { // Called only on opponent's move
	int from_x,from_y,to_x,to_y;
	from_x = move.getFrom().getX();
	from_y = move.getFrom().getY();
	to_x = move.getTo().getX();
	to_y = move.getTo().getY();
	if (board_his[from_x-1][from_y-1]==UNKNOWN) { // If this is the first time the player move this piece
		board_his[to_x-1][to_y-1] = MOVABLE; // Mark the piece as moveable - This is not his flag
	} else {
		board_his[to_x-1][to_y-1] = board_his[from_x-1][from_y-1]; // Keep track on the piece type
	}
	board_his[from_x-1][from_y-1] = EMPTY;
	if ((from_x==target.getX())&&(from_y==target.getY())) { // If the opponent moved with a piece we thought was his flag,
		findTarget(); // Guess what is the opponent's flag
	}
}

void PlayerAlgorithmAutoRPS::notifyFightResult(const FightInfo& fightInfo) { // Called only if there was a fight
	int x,y,winner;
	x = fightInfo.getPosition().getX();
	y = fightInfo.getPosition().getY();
	winner = fightInfo.getWinner(); // FightInfo.getWinner() Return 0 - both lost, 1 - playet 1 won, 2 - player 2 won
	if (winner==whoami) { // If I was the winner of the fight
		board_his[x-1][y-1] = EMPTY;
		opponent_died_pieces_counters[fightInfo.getPiece(opponent_number)] += 1; // FightInfo.getPiece() Return R, P, S, B or F (but NOT J)
	} else if (winner==0) { // If there was a tie and we both died
		board_my[x-1][y-1][0] = EMPTY;
		board_my[x-1][y-1][1] = EMPTY;
		board_his[x-1][y-1] = EMPTY;
		opponent_died_pieces_counters[fightInfo.getPiece(opponent_number)] += 1; // FightInfo.getPiece() Return R, P, S, B or F (but NOT J)
	} else { // If the opponent win the fight and my piece died
		board_my[x-1][y-1][0] = EMPTY;
		board_my[x-1][y-1][1] = EMPTY;
		board_his[x-1][y-1] = fightInfo.getPiece(opponent_number); // FightInfo.getPiece() Return R, P, S, B or F (but NOT J)
	}
	if ((x==target.getX())&&(y==target.getY())) { // If the fight was involved with a piece we thought was his flag,
		if (checkGameOver()==1) { // checkGameOver() Return 0 if game is over for us and 1 otherwise
			findTarget(); // Guess what is the opponent's flag
		}
	}
}

unique_ptr<Move> PlayerAlgorithmAutoRPS::getMove() {
	if (steps_counter>bias) { // The 'bias' ia after how many steps to the target we switch to attack mode (against opponent victim)
		steps_counter = 0;
		move_mode = 0; // 0 is toward the target and 1 is toward the victim (opponent known piece)
	} else {
		steps_counter++;
		move_mode = 1; // 0 is toward the target and 1 is toward the victim (opponent known piece)
	}
	// Choose which piece will go where
	minMax(); // Find the most atractive piece we can move and calculate where to move him, Update the info at 'move_from' and 'move_to'
	board_my[move_to.getX()-1][move_to.getY()-1][0] = board_my[move_from.getX()-1][move_from.getY()-1][0];
	board_my[move_from.getX()-1][move_from.getY()-1][0] = EMPTY;
	board_my[move_to.getX()-1][move_to.getY()-1][1] = MOVABLE;
	board_my[move_from.getX()-1][move_from.getY()-1][1] = EMPTY;
	// Save the last position (This is done so we dont do the same two steps over and over)
	last_pos.setX(move_from.getX());
	last_pos.setY(move_from.getY());
	// Return our move
	return std::move(std::make_unique<MoveRPS>(PointRPS(move_from.getX(),move_from.getY()),PointRPS(move_to.getX(),move_to.getY())));
}

////////////////////////////////////////////////////////////////////
////	PlayerAlgorithmAutoRPS functions 			////
////////////////////////////////////////////////////////////////////
// Return 0 if game is over for us and 1 otherwise
int PlayerAlgorithmAutoRPS::checkGameOver() {
	int i,j; // 1<=i<=M 1<=j<=N
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			if (board_his[i-1][j-1]==UNKNOWN) { // 1<=i<=M 1<=j<=N
				return 1;
			}
		}
	}
	return 0;
}

// Simulate a fight between two pieces, Return 0 if both lost, 1 if only player 1 win, 2 if only player 2 win
int PlayerAlgorithmAutoRPS::fightSimulate(char piece_1, char piece_2) {
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

// Guess what is the opponent's flag
void PlayerAlgorithmAutoRPS::findTarget() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist_1(1,M_COLS); // M_COLS is x
	std::uniform_int_distribution<int> dist_2(1,N_ROWS); // N_ROWS is y
	int random_y = dist_2(mt); // Random in range [1,N]
	int random_x = dist_1(mt); // Random in range [1,M]
	while (board_his[random_x-1][random_y-1]!=UNKNOWN) {
		random_y = dist_2(mt); // Random in range [1,N]
		random_x = dist_1(mt); // Random in range [1,M]
	}
	this->target.setX(random_x);
	this->target.setY(random_y);
}

// Search if there is a known opponent piece that the ours selected piece can win, Return the location of a piece we can win or invalid point otherwise
PointRPS PlayerAlgorithmAutoRPS::findVictim(PointRPS my_piece) {
	int i,j; // 1<=i<=M 1<=j<=N
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			if ((board_his[i-1][j-1]!=UNKNOWN)&&(board_his[i-1][j-1]!=EMPTY)&&(board_his[i-1][j-1]!=MOVABLE)) { // 1<=i<=M 1<=j<=N
				if (fightSimulate(board_my[my_piece.getX()-1][my_piece.getY()-1][0],board_his[i-1][j-1])==1) { // fightSimulate() Return 0 if both lost, 1 if only player 1 win, 2 if only player 2 win
					return PointRPS(i,j); // Return the first piece we found
				}
			}
		}
	}
	return PointRPS(0,0);
}

// Search for avilable point for the fighters, Return available point at the board
PointRPS PlayerAlgorithmAutoRPS::getAvailablePoint(char piece) {
	int fighter_x,fighter_y;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist_1(4,M_COLS-3); // M_COLS is x
	std::uniform_int_distribution<int> dist_2(4,N_ROWS-3); // N_ROWS is y
	while (1) { // This loop MUST end eventually
		fighter_x = dist_1(mt); // Random in range [4,M-3]
		fighter_y = dist_2(mt); // Random in range [4,N-3]
		if (board_my[fighter_x-1][fighter_y-1][0]==EMPTY) {
			board_my[fighter_x-1][fighter_y-1][0] = piece;
			return PointRPS(fighter_x,fighter_y);
		}
	}
}

// Find the most atractive piece we can move and calculate where to move him, Update the info at 'move_from' and 'move_to'
void PlayerAlgorithmAutoRPS::minMax() {
	int i,j; // 1<=i<=M 1<=j<=N
	int left,right,down,up;
	int max_score = 0;
	PointRPS pos_source = PointRPS(0,0);;
	PointRPS pos_direction = PointRPS(0,0);;
	for (i=1;i<=M_COLS;++i) { // M_COLS is x
		for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
			if (board_my[i-1][j-1][0]!=EMPTY&&board_my[i-1][j-1][0]!=FLAG&&board_my[i-1][j-1][0]!=BOMB&&board_my[i-1][j-1][0]!=JOKER_BOMB) { // 1<=i<=M 1<=j<=N
				if (i>=2) { // Left
					left = scoring(PointRPS(i,j),PointRPS(i-1,j)); // scoring() Return a score for the selected move
					if (left>max_score) { // If this move has the highest score so far
						pos_source.setX(i);
						pos_source.setY(j);
						pos_direction.setX(i-1);
						pos_direction.setY(j);
						max_score = left;
					}
				}
				if (i<=9) { // Right
					right = scoring(PointRPS(i,j),PointRPS(i+1,j)); // scoring() Return a score for the selected move
					if (right>max_score) { // If this move has the highest score so far
						pos_source.setX(i);
						pos_source.setY(j);
						pos_direction.setX(i+1);
						pos_direction.setY(j);
						max_score = right;
					}
				}
				if (j>=2) { // Down
					down = scoring(PointRPS(i,j),PointRPS(i,j-1)); // scoring() Return a score for the selected move
					if (down>max_score) { // If this move has the highest score so far
						pos_source.setX(i);
						pos_source.setY(j);
						pos_direction.setX(i);
						pos_direction.setY(j-1);
						max_score = down;
					}
				}
				if (j<=9) { // Up
					up = scoring(PointRPS(i,j),PointRPS(i,j+1)); // scoring() Return a score for the selected move
					if (up>max_score) { // If this move has the highest score so far
						pos_source.setX(i);
						pos_source.setY(j);
						pos_direction.setX(i);
						pos_direction.setY(j+1);
						max_score = up;
					}
				}
			}
		}
	}
	move_from.setX(pos_source.getX());
	move_from.setY(pos_source.getY());
	move_to.setX(pos_direction.getX());
	move_to.setY(pos_direction.getY());
}

// Calculate a score for moving 'source_piece' to 'next_step', Return a score for the selected move
double PlayerAlgorithmAutoRPS::scoring(PointRPS source_piece, PointRPS next_step) {
	int score_map[2][10] = {{10,1,1,10,1,5, 5,5,10,1},	// Against the target
				{10,1,1,10,6,4,10,1, 5,5}};	// Against the victim
	// Position 0: The piece at the next step is known, We can win, Should we fight?
	// Position 1: The piece at the next step is known, We can win, Should we run?
	// Position 2: The piece at the next step is known, We will lose, Should we fight?
	// Position 3: The piece at the next step is known, We will lose, Should we run?
	// Position 4: The piece at the next step is known, There will be a tie, Should we fight?
	// Position 5: The piece at the next step is known, There will be a tie, Should we run?
	// Position 6: The piece at the next step is unknown, Should we fight?
	// Position 7: The piece at the next step is unknown, Should we run?
	// Position 8: I have already moved once with this piece
	// Position 9: I never moved this piece before
	//
	int empty,escape,fight,move;
	double distance;
	int x_source = source_piece.getX();
	int y_source = source_piece.getY();
	int x_next = next_step.getX();
	int y_next = next_step.getY();
	int x_target = target.getX();
	int y_target = target.getY();
	if (move_mode==1) { // 0 is toward the target and 1 is toward the victim (opponent known piece)
		PointRPS victim = findVictim(source_piece); // findVictim() Return the location of a piece we can win or invalid point otherwise
		if (victim.getX()>0) {
			x_target = victim.getX();
			y_target = victim.getY();
		}
	}
	// We cannot move to a location that we already have piece at
	if (board_my[x_next-1][y_next-1][0]!=EMPTY) {
		empty = 0;
	} else {
		empty = 10;
	}
	// Calculate the distance score, Linear function based on the maximum distance at the board
	distance = std::abs(x_next-x_target) + std::abs(y_next-y_target);
	distance = ((N_ROWS+M_COLS-distance)*10)/(N_ROWS+M_COLS);
	// Calculate the fight and escape scores based on the oponnent piece at the next step and the game 'move_mode'
	if ((board_his[x_next-1][y_next-1]!=UNKNOWN)&&(board_his[x_next-1][y_next-1]!=EMPTY)&&(board_his[x_next-1][y_next-1]!=MOVABLE)) {
		int winner = fightSimulate(board_my[x_source-1][y_source-1][0],board_his[x_next-1][y_next-1]); // fightSimulate() Return 0 if both lost, 1 if only player 1 win, 2 if only player 2 win
		if (winner==1) {
			fight = score_map[move_mode][0];
			escape = score_map[move_mode][1];
		} else if (winner==2) {
			fight = score_map[move_mode][2];
			escape = score_map[move_mode][3];
		} else {
			fight = score_map[move_mode][4];
			escape = score_map[move_mode][5];
		}
	} else {
		fight = score_map[move_mode][6];
		escape = score_map[move_mode][7];
	}
	// If the piece has never moved before, do we really want to move it and give more information to our opponent?
	if (board_my[x_source-1][y_source-1][1]==MOVABLE) {
		move = score_map[move_mode][8];
	} else {
		move = score_map[move_mode][9];
	}
	// if this move will bring us back to where we was in the previous step, Avoid it
	if ((last_pos.getX()==x_next)&&(last_pos.getY()==y_next)) { // Avoid loops
		return (escape*fight*empty*distance*move)/2;
	} else {
		return escape*fight*empty*distance*move;
	}
}
