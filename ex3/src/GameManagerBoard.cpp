/*
 * GameManagerBoard.cpp
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Helper class for the game manager.
 * 		This class does not check input integrity or logic.
 * 		This class just do the requests (assuming they are already validated).
 */

#include "GameManagerBoard.h"

////////////////////////////////////////////////////////////////////
////	GameManagerBoard functions				////
////////////////////////////////////////////////////////////////////
// Change the representation of the selected joker, Return 0 on success and 1 otherwise
int GameManagerBoard::changeJoker(char new_piece, Point& pos, int player) {
	int vector_location = -1;
	PiecePositionRPS* piece = searchPiece(vector_location,pos,player); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		piece->setPiece(new_piece);
		return 0;
	}
	return 1;
}

// Check what piece is at the selected location, Return R, P, S, B, Joker type, F or EMPTY
char GameManagerBoard::getPiece(const Point& pos) {
	int vector_location = -1;
	PiecePositionRPS* piece = searchPiece(vector_location,pos,1); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		if (piece->getPiece()==JOKER) {
			switch (piece->getJokerRep()) { // ONLY for Joker: R, P, S or B -- non-Joker return #
				case ROCK: return JOKER_ROCK;
							break;
				case PAPER: return JOKER_PAPER;
							break;
				case SCISSORS: return JOKER_SCISSORS;
							break;
				case BOMB: return JOKER_BOMB;
							break;
				default: return NOT_JOKER;
			}
		} else {
			return piece->getPiece(); // PiecePosition.getPiece() Return R, P, S, B, J or F
		}
	}
	piece = searchPiece(vector_location,pos,2); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		if (piece->getPiece()==JOKER) {
			switch (piece->getJokerRep()) { // ONLY for Joker: R, P, S or B -- non-Joker return #
				case ROCK: return JOKER_ROCK;
							break;
				case PAPER: return JOKER_PAPER;
							break;
				case SCISSORS: return JOKER_SCISSORS;
							break;
				case BOMB: return JOKER_BOMB;
							break;
				default: return NOT_JOKER;
			}
		} else {
			return piece->getPiece(); // PiecePosition.getPiece() Return R, P, S, B, J or F
		}
	}
	return EMPTY;
}

// Get the player number at the selected location, Return 1 for player 1's piece, 2 for 2, 0 if empty
int GameManagerBoard::getPlayer(const Point& pos) const {
	int vector_location = -1;
	searchPiece(vector_location,pos,1); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		return 1;
	}
	searchPiece(vector_location,pos,2); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		return 2;
	}
	return 0;
}

// Remove the piece of the selected player from the board
void GameManagerBoard::killPiece(const Point& pos) {
	int vector_location = -1;
	searchPiece(vector_location,pos,1); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		player1_pieces.erase(player1_pieces.begin()+vector_location,player1_pieces.begin()+vector_location+1);
		return;
	}
	searchPiece(vector_location,pos,2); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		player2_pieces.erase(player2_pieces.begin()+vector_location,player2_pieces.begin()+vector_location+1);
	}
}

// Move the piece of the selected player
void GameManagerBoard::move(const Point& from, const Point& to, int player) {
	int vector_location = -1;
	PiecePositionRPS* piece = searchPiece(vector_location,from,player); // searchPiece() Return piece and his position at the vector on success or -1 otherwise
	if (0<=vector_location) {
		piece->setPossition(to);
	}
}

// Search the pieces for the selected player, Return piece and his position at the vector on success or -1 otherwise
PiecePositionRPS* GameManagerBoard::searchPiece(int& ret, const Point& pos, int player) const {
	int counter = 0;
	if (player==1) {
		for (auto& obj : player1_pieces) {
			if (obj) {
				if ((obj.get()->getPosition().getX()==pos.getX())&&(obj.get()->getPosition().getY()==pos.getY())) {
					ret = counter;
					return obj.get();
				}
				counter++;
			}
		}
	} else if (player==2) {
		for (auto& obj : player2_pieces) {
			if (obj) {
				if ((obj.get()->getPosition().getX()==pos.getX())&&(obj.get()->getPosition().getY()==pos.getY())) {
					ret = counter;
					return obj.get();
				}
				counter++;
			}
		}
	}
	ret = -1;
	return nullptr;
}
