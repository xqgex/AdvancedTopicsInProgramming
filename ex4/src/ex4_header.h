#ifndef EX4_H_
#define EX4_H_

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include <utility>

#define ALL					0
#define PIECES_OF_PLAYER			1
#define OCCURENECE_OF_PIECE			2
#define OCCURENECE_OF_PIECE_FOR_PLAYER		3

template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS=2>
class GameBoard {
public:
	typedef std::unique_ptr<const std::pair<int,GAME_PIECE>> ElementType; //ElementType=PieceInfo
	typedef ElementType RowType[COLS];
	typedef RowType MatrixType[ROWS];
private:
	MatrixType _matrix;
public:
	GameBoard() {
		for (int i=0;i<ROWS;++i) {
			for (int j=0;j<COLS;++j) {
				_matrix[i][j] = nullptr;
			}
		}
	}
	std::unique_ptr<const std::pair<int,GAME_PIECE> > getPiece(int row, int col) {
		return _matrix[row][col];
	}
	std::unique_ptr<const std::pair<int,GAME_PIECE> > setPiece(int row, int col, GAME_PIECE piece, int player) {
		std::unique_ptr<const std::pair<int,GAME_PIECE> > pieceInfo = std::move(_matrix[row][col]);
		std::pair<int, GAME_PIECE> new_pair = std::make_pair(player,piece);
		_matrix[row][col] = std::make_unique<std::pair<int, GAME_PIECE>>(new_pair);
		return pieceInfo;
	}
	class iterator {
		MatrixType* _itr_matrix;
		int _itr_pos_x, _itr_pos_y;
		int _flag;
		int _search_player;
		GAME_PIECE _search_piece;
	public:
		// iterator traits
		using difference_type = long;
		using value_type = long;
		using pointer = const long*;
		using reference = const long&;
		using iterator_category = std::bidirectional_iterator_tag;
		// end of iterator traits
		iterator(int flag, int search_player, MatrixType* itr_matrix = nullptr, int itr_pos_x = 0, int itr_pos_y = 0) {
			_flag = flag;
			_itr_matrix = itr_matrix;
			_itr_pos_x = itr_pos_x;
			_itr_pos_y = itr_pos_y;
			_search_player = search_player;
		}
		iterator(int flag, int search_player, GAME_PIECE search_piece, MatrixType* itr_matrix = nullptr, int itr_pos_x = 0, int itr_pos_y = 0) {
			_flag = flag;
			_itr_matrix = itr_matrix;
			_itr_pos_x = itr_pos_x;
			_itr_pos_y = itr_pos_y;
			_search_player = search_player;
			_search_piece = search_piece;
		}
		std::tuple<int,int,GAME_PIECE,int> operator*() {
			if ((*_itr_matrix)[_itr_pos_x][_itr_pos_y]==nullptr) {
				std::cout << "Error: operator*() got nullptr" << std::endl;
				exit(1);
			} else {
				return std::make_tuple(_itr_pos_x,_itr_pos_y,(*_itr_matrix)[_itr_pos_x][_itr_pos_y]->second,(*_itr_matrix)[_itr_pos_x][_itr_pos_y]->first);
			}
		}
		void incPointer() {
			_itr_pos_x++;
			if (_itr_pos_x==ROWS) {
				_itr_pos_y++;
				if (_itr_pos_y!=COLS) {
					_itr_pos_x = 0;
				}
			}
		}
		iterator operator++() {
			switch (_flag) {
				case ALL:
					incPointer();
					break;
				case PIECES_OF_PLAYER:
					do {
						incPointer();
					} while (	(_itr_pos_x!=ROWS)&&
							(_itr_pos_y!=COLS)&&
								(((*_itr_matrix)[_itr_pos_x][_itr_pos_y]==nullptr)||
								((*_itr_matrix)[_itr_pos_x][_itr_pos_y]->first!=_search_player)
							)
						);
					break;
				case OCCURENECE_OF_PIECE:
					do {
						incPointer();
					} while (	(_itr_pos_x!=ROWS)&&
							(_itr_pos_y!=COLS)&&
								(((*_itr_matrix)[_itr_pos_x][_itr_pos_y]==nullptr)||
								((*_itr_matrix)[_itr_pos_x][_itr_pos_y]->second!=_search_piece)
							)
						);
					break;
				case OCCURENECE_OF_PIECE_FOR_PLAYER:
					do {
						incPointer();
					} while (	(_itr_pos_x!=ROWS)&&
							(_itr_pos_y!=COLS)&&
								(((*_itr_matrix)[_itr_pos_x][_itr_pos_y]==nullptr)||
								((*_itr_matrix)[_itr_pos_x][_itr_pos_y]->first!=_search_player)||
								((*_itr_matrix)[_itr_pos_x][_itr_pos_y]->second!=_search_piece)
							)
						);
					break;
			}
			return *this;
		}
		bool operator!=(iterator other) {
			return ((_itr_pos_x!=other._itr_pos_x)&&(_itr_pos_y!=other._itr_pos_y));
		}
	};
	class AllPiecesOfPlayerIterator {
		MatrixType* _itr_matrix;
		int _playerNum;
	public:
		AllPiecesOfPlayerIterator(MatrixType* itr_matrix, int playerNum) {
			_itr_matrix = itr_matrix;
			_playerNum = playerNum;
		}
		iterator begin() {
			int x = 0;
			int y = 0;
			while ((x!=ROWS)&&(y!=COLS)) {
				if (((*_itr_matrix)[x][y]!=nullptr)&&((*_itr_matrix)[x][y]->first==_playerNum)) {
					break;
				}
				x++;
				if (x==ROWS) {
					y++;
					if (y!=COLS) {
						x = 0;
					}
				}
			}
			if ((x==ROWS)&&(y==COLS)) {
				return end();
			} else {
				return iterator(PIECES_OF_PLAYER, _playerNum, _itr_matrix, x, y);
			}
		}
		iterator end() {
			return iterator(PIECES_OF_PLAYER, _playerNum, _itr_matrix, ROWS, COLS);
		}
	};
	class AllOccureneceOfPieceIterator {
		MatrixType* _itr_matrix;
		GAME_PIECE _piece;
	public:
		AllOccureneceOfPieceIterator(MatrixType* itr_matrix, GAME_PIECE piece) {
			_itr_matrix = itr_matrix;
			_piece = piece;
		}
		iterator begin() {
			int x = 0;
			int y = 0;
			while ((x!=ROWS)&&(y!=COLS)) {
				if (((*_itr_matrix)[x][y]!=nullptr)&&((*_itr_matrix)[x][y]->second==_piece)) {
					break;
				}
				x++;
				if (x==ROWS) {
					y++;
					if (y!=COLS) {
						x = 0;
					}
				}
			}
			if ((x==ROWS)&&(y==COLS)) {
				return end();
			} else {
				return iterator(OCCURENECE_OF_PIECE, -1, _piece, _itr_matrix, x, y);
			}
		}
		iterator end() {
			return iterator(OCCURENECE_OF_PIECE, -1, _piece, _itr_matrix, ROWS, COLS);
		}
	};
	class AllOccureneceOfPieceForPlayerIterator {
		MatrixType* _itr_matrix;
		int _playerNum;
		GAME_PIECE _piece;
	public:
		AllOccureneceOfPieceForPlayerIterator(MatrixType* itr_matrix, int playerNum, GAME_PIECE piece) {
			_itr_matrix = itr_matrix;
			_playerNum = playerNum;
			_piece = piece;
		}
		iterator begin() {
			int x = 0;
			int y = 0;
			while ((x!=ROWS)&&(y!=COLS)) {
				if (((*_itr_matrix)[x][y]!=nullptr)&&((*_itr_matrix)[x][y]->first==_playerNum)&&((*_itr_matrix)[x][y]->second==_piece)) {
					break;
				}
				x++;
				if (x==ROWS) {
					y++;
					if (y!=COLS) {
						x = 0;
					}
				}
			}
			if ((x==ROWS)&&(y==COLS)) {
				return end();
			} else {
				return iterator(OCCURENECE_OF_PIECE_FOR_PLAYER, _playerNum, _piece, _itr_matrix, x, y);
			}
		}
		iterator end() {
			return iterator(OCCURENECE_OF_PIECE_FOR_PLAYER, _playerNum, _piece, _itr_matrix, ROWS, COLS);
		}
	};
	iterator begin() {
		int x = 0;
		int y = 0;
		while (((x!=ROWS)&&(y!=COLS))&&(_matrix[x][y]==nullptr)) {
			x++;
			if (x==ROWS) {
				y++;
				if (y!=COLS) {
					x = 0;
				}
			}
		}
		if ((x==ROWS)&&(y==COLS)) {
			return end();
		} else {
			return iterator(ALL, -1, &_matrix, x, y);
		}
	}
	iterator end() {
		return iterator(ALL, -1, &_matrix, ROWS, COLS);
	}
	AllPiecesOfPlayerIterator allPiecesOfPlayer(int playerNum) {
		return AllPiecesOfPlayerIterator(&_matrix,playerNum); // 3.b
	}
	AllOccureneceOfPieceIterator allOccureneceOfPiece(GAME_PIECE piece) {
		return AllOccureneceOfPieceIterator(&_matrix,piece); // 3.c
	}
	AllOccureneceOfPieceForPlayerIterator allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum) {
		return AllOccureneceOfPieceForPlayerIterator(&_matrix,playerNum,piece); // 3.d
	}
};

#endif /* EX4_H_ */
