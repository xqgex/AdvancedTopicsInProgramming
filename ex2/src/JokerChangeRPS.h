/*
 * JokerChangeRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class JokerChange.h
 * 		This class save the representation of player jokers.
 * 		The 'PlayerAlgorithm' use this class to pass his 'joker changing' decisions.
 */
#ifndef JOKERCHANGERPS_H_
#define JOKERCHANGERPS_H_

#include "JokerChange.h"

#include "PointRPS.h"

class JokerChangeRPS:public JokerChange {
private:
	PointRPS _position;
	char _rep;
public:
	// Abstract implementation
	virtual const Point& getJokerChangePosition() const override {return _position;}
	virtual char getJokerNewRep() const override {return _rep;} // R, P, S or B (but NOT J and NOT F)
	// JokerChangeRPS
	JokerChangeRPS(PointRPS position, char rep) {
		this->_position = position;
		this->_rep = rep; // R, P, S or B (but NOT J and NOT F)
	}
};

#endif /* JOKERCHANGERPS_H_ */
