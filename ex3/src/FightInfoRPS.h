/*
 * FightInfoRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class FightInfo.h
 * 		The 'FightInfo' class saves the fight result.
 * 		We reveal the piece of the winner, and the 'PlayerAlgorithm' can use this information to decide his next moves.
 */
#ifndef FIGHTINFORPS_H_
#define FIGHTINFORPS_H_

#include "FightInfo.h"

#include "PointRPS.h"

class FightInfoRPS:public FightInfo {
private:
	char _piece_1; // R, P, S, B or F (but NOT J)
	char _piece_2; // R, P, S, B or F (but NOT J)
	PointRPS _position;
	int _winner; // 0 - both lost, 1 - playet 1 won, 2 - player 2 won
public:
	// Abstract implementation
	virtual const Point& getPosition() const override {return _position;}
	virtual char getPiece(int player) const override {return (player==1)?_piece_1:_piece_2;} // R, P, S, B or F (but NOT J)
	virtual int getWinner() const override {return _winner;} // 0 - both lost, 1 - playet 1 won, 2 - player 2 won
	// FightInfoRPS
	FightInfoRPS(const Point& pos, char piece_1, char piece_2, int winner) {
		this->_piece_1 = piece_1; // R, P, S, B or F (but NOT J)
		this->_piece_2 = piece_2; // R, P, S, B or F (but NOT J)
		this->_position = PointRPS(pos.getX(),pos.getY());
		this->_winner = winner; // 0 - both lost, 1 - playet 1 won, 2 - player 2 won
	}
};

#endif /* FIGHTINFORPS_H_ */
