/*
 * PiecePositionRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class PiecePosition.h
 * 		The 'PiecePositionRPS' class save information about one piece at the board.
 * 		the 'GameMangerBoard' save the status of the game using two vectors of pieces.
 */
#ifndef PIECEPOSITIONRPS_H_
#define PIECEPOSITIONRPS_H_

#include "PiecePosition.h"

#include "GameParameters.h"
#include "PointRPS.h"

class PiecePositionRPS:public PiecePosition {
private:
	char _piece;
	int _player;
	PointRPS _position;
public:
	// Abstract implementation
	virtual const Point& getPosition() const override {return _position;}
	virtual char getPiece() const override { // R, P, S, B, J or F
		if ((_piece==JOKER_ROCK)||(_piece==JOKER_PAPER)||(_piece==JOKER_SCISSORS)||(_piece==JOKER_BOMB)) {
			return JOKER;
		} else {
			return _piece;
		}

	}
	virtual char getJokerRep() const override { // ONLY for Joker: R, P, S or B -- non-Joker return #
		switch (_piece) {
			case JOKER_ROCK: return ROCK;
						break;
			case JOKER_PAPER: return PAPER;
						break;
			case JOKER_SCISSORS: return SCISSORS;
						break;
			case JOKER_BOMB: return BOMB;
						break;
			default: return NOT_JOKER;
		}
	}
	// PiecePositionRPS
	PiecePositionRPS(char piece, PointRPS point, int player) {
		this->_piece = piece;
		this->_player = player;
		this->_position = point;
	}
	// PiecePositionRPS functions
	int getPlayer() const {return _player;}
	void setPiece(char new_piece) {_piece = new_piece;}
	void setPossition(const Point& new_pos) {
		this->_position.setX(new_pos.getX());
		this->_position.setY(new_pos.getY());
	}
};

#endif /* PIECEPOSITIONRPS_H_ */
