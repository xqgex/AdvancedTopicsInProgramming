/*
 * BoardRPS.h
 *
 *      Course: Advanced Topics In Programming
 *    Exercise: 2
 * Description: Implement the abstract class Board.h
 *		The 'BoardRPS' class save for each board position if there is a player there and if so who (saved the number of the player, or 0 if it's empty).
 *		The 'PlayerAlgorithm' use this class to decide his next move
 */
#ifndef BOARDRPS_H_
#define BOARDRPS_H_

#include "Board.h"

#include "GameParameters.h"
#include "PointRPS.h"

class BoardRPS:public Board {
private:
	int _board[M_COLS][N_ROWS] = {{0}};
public:
	// Abstract implementation
	virtual int getPlayer(const Point& pos) const override {return _board[pos.getX()-1][pos.getY()-1];} // 1 for player 1's piece, 2 for 2, 0 if empty
	// BoardRPS
	BoardRPS(int current_board[M_COLS][N_ROWS]) {
		int i,j; // 1<=i<=M 1<=j<=N
		for (i=1;i<=M_COLS;++i) { // M_COLS is x
			for (j=1;j<=N_ROWS;++j) { // N_ROWS is y
				this->_board[i-1][j-1] = current_board[i-1][j-1]; // 1<=i<=M 1<=j<=N
			}
		}
	}
};

#endif /* BOARDRPS_H_ */
