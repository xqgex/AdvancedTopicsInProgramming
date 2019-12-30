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

#include "PointRPS.h"

class PiecePositionRPS:public PiecePosition {
private:
	char _is_joker;
	char _piece;
	int _player;
	PointRPS _position;
public:
	// Abstract implementation
	virtual const Point& getPosition() const override {return _position;}
	virtual char getPiece() const override {return _piece;} // R, P, S, B, J or F
	virtual char getJokerRep() const override {return _is_joker;} // JOKER_TRUE ONLY for Joker: R, P, S or B -- non-Joker return JOKER_FALSE
	// PiecePositionRPS
	PiecePositionRPS(char piece, PointRPS point, char is_joker, int player) {
		this->_is_joker = is_joker;
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
