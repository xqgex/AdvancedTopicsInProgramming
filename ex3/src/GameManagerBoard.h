/*
 * GameManagerBoard.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Helper class for the game manager.
 * 		This class does not check input integrity or logic.
 * 		This class just do the requests (assuming they are already validated).
 */
#ifndef GAMEMANAGERBOARD_H_
#define GAMEMANAGERBOARD_H_

#include <memory>	// std::unique_ptr
#include <vector>	// std::vector

#include "BoardRPS.h"
#include "GameParameters.h"
#include "PiecePositionRPS.h"
#include "PointRPS.h"

class GameManagerBoard {
private:
	std::vector<std::unique_ptr<PiecePositionRPS>> player1_pieces;
	std::vector<std::unique_ptr<PiecePositionRPS>> player2_pieces;
public:
	// GameManagerBoard
	GameManagerBoard() {}
	// GameManagerBoard functions
	void addPiecePosition(std::unique_ptr<PiecePositionRPS>& piece, int player) {
		(player==1)?player1_pieces.push_back(std::move(piece)):player2_pieces.push_back(std::move(piece));
	}
	int changeJoker(char new_piece, Point& pos, int player); // Change the representation of the selected joker, Return 0 on success and 1 otherwise
	char getPiece(const Point& pos); // Check what piece is at the selected location, Return R, P, S, B, Joker type, F or EMPTY
	int getPlayer(const Point& pos) const; // Get the player number at the selected location, Return 1 for player 1's piece, 2 for 2, 0 if empty
	void killPiece(const Point& pos); // Remove the piece of the selected player from the board
	void move(const Point& from, const Point& to, int player); // Move the piece of the selected player
	PiecePositionRPS* searchPiece(int& ret, const Point& pos, int player) const; // Search the pieces for the selected player, Return piece and his position at the vector on success or -1 otherwise
};

#endif /* GAMEMANAGERBOARD_H_ */
