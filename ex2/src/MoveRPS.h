/*
 * MoveRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class Move.h
 * 		The 'MoveRPS' class save information about move request, it hold from where and to where the player wants to go.
 * 		The 'PlayerAlgorithm' use this class to pass his move decisions.
 */
#ifndef MOVERPS_H_
#define MOVERPS_H_

#include "Move.h"

#include "PointRPS.h"

class MoveRPS:public Move {
private:
	PointRPS _from;
	PointRPS _to;
public:
	// Abstract implementation
	virtual const Point& getFrom() const override {return _from;}
	virtual const Point& getTo() const override {return _to;}
	// MoveRPS
	MoveRPS(PointRPS from, PointRPS to) {
		this->_from = from;
		this->_to = to;
	}
};

#endif /* MOVERPS_H_ */
