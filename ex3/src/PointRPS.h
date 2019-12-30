/*
 * PointRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class Point.h
 * 		This class represents a location on the game board.
 */
#ifndef POINTRPS_H_
#define POINTRPS_H_

#include "Point.h"

class PointRPS:public Point {
private:
	int _x;
	int _y;
public:
	// Abstract implementation
	virtual int getX() const override {return _x;}
	virtual int getY() const override {return _y;}
	// PointRPS
	PointRPS() {
		this->_x = -1;
		this->_y = -1;
	}
	PointRPS(int x, int y) {
		this->_x = x;
		this->_y = y;
	}
	// PointRPS functions
	void setX(int x) {this->_x = x;}
	void setY(int y) {this->_y = y;}
};

#endif /* POINTRPS_H_ */
