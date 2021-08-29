#include "YunixChessLib.h"


bool isItAValidMove(int fromx, int fromy, int tox, int toy, short board[][N], gameParams& gp, bool turn, bool& elPassant, bool& twoMove) {
	//while()cout << "Is it valid move called with " << fromx << " " << fromy << " - " << tox << " " << toy << endl;
	if (fromx == 100) {
		if (turn && gp.canWhiteCastleShort) {
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			if (!grid[0][f] && !grid[0][g]) return true;
		}
		else if (!turn && gp.canBlackCastleShort) {
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			if (!grid[7][f] && !grid[7][g]) return true;
		}
		return false;
	}
	if (fromx == 200) {
		if (turn && gp.canWhiteCastleLong) {
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			if (!grid[0][b] && !grid[0][c] && !grid[0][d]) return true;
		}
		else if (!turn && gp.canBlackCastleLong) {
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			if (!grid[7][b] && !grid[7][c] && !grid[7][d]) return true;
		}
		return false;
	}
	if (!inBoard(fromx, fromy) || !inBoard(tox, toy)) return false; //out of board
	if (turn && board[tox][toy] >= wPawn && board[tox][toy] <= wKing) return false; //white can't eat white
	if (!turn && board[tox][toy] >= bPawn && board[tox][toy] <= bKing) return false; //black can't eat black
	int x, y;
	if (turn) {
		switch (board[fromx][fromy]) {
		case wKing: {
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			for (int ii = 0; ii < 8; ii++) {
				x = fromx + kingmoves.horizontalOffset[ii];
				y = fromy + kingmoves.verticalOffset[ii];
				if (inBoard(x, y))
					if (x == tox && y == toy) {
						if (grid[tox][toy]) return false;
						return true;
					}
			}
			return false;
		}
				  break;
		case wQueen:
			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			return false;
			break;
		case wKnight:
			for (int ii = 0; ii < 8; ii++) {
				x = fromx + knightmoves.horizontalOffset[ii];
				y = fromy + knightmoves.verticalOffset[ii];
				if (inBoard(x, y))
					if (x == tox && y == toy)
						return true;
			}

			return false;
			break;
		case wBishop:
			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			return false;
			break;
		case wRook:
			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			return false;
			break;
		case wPawn:

			x = fromx + whitepawnmoves.oneStep;
			y = fromy;
			if (inBoard(x, y))
				if (board[x][y] == blank && x == tox && y == toy)
					return true;

			y = fromy + whitepawnmoves.eatsLeftx;
			if (inBoard(x, y))
				if (board[x][y] >= bPawn && board[x][y] <= bKing && x == tox && y == toy)
					return true;
				else if (board[fromx][y] == bPawn && gp.lastMovedTwoX == fromx && gp.lastMovedTwoY == y) //el passant
				{
					elPassant = true; return true;
				}

			y = fromy + whitepawnmoves.eatsRightx;
			if (inBoard(x, y))
				if (board[x][y] >= bPawn && board[x][y] <= bKing && x == tox && y == toy)
					return true;
				else if (board[fromx][y] == bPawn && gp.lastMovedTwoX == fromx && gp.lastMovedTwoY == y) //el passant
				{
					elPassant = true; return true;
				}

			y = fromy;
			x = fromx + whitepawnmoves.twoStep;
			if (inBoard(x, y))
				if (board[x][y] == blank && board[x - 1][y] == blank && x == tox && y == toy && fromx == 1) {
					twoMove = true;
					return true;
				}


			return false;
			break;
		default: return false;
		}
	}
	else
	{
		switch (board[fromx][fromy]) {
		case bKing: {
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			for (int ii = 0; ii < 8; ii++) {
				x = fromx + kingmoves.horizontalOffset[ii];
				y = fromy + kingmoves.verticalOffset[ii];
				if (inBoard(x, y))
					if (x == tox && y == toy) {
						if (grid[tox][toy]) return false;
						return true;
					}
			}
			return false;
		}
				  break;
		case bQueen:
			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			return false;
			break;
		case bKnight:
			for (int ii = 0; ii < 8; ii++) {
				x = fromx + knightmoves.horizontalOffset[ii];
				y = fromy + knightmoves.verticalOffset[ii];
				if (inBoard(x, y))
					if (x == tox && y == toy)
						return true;
			}

			return false;
			break;
		case bBishop:
			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			return false;
			break;
		case bRook:
			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.leftY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx + qbrmoves.rightY[ii];
				y = fromy;
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.upX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			for (int ii = 0; ii < 7; ii++) {
				x = fromx;
				y = fromy + qbrmoves.downX[ii];
				if (inBoard(x, y)) {
					if (x == tox && y == toy)
						return true;
				}
				else break;
				if (board[x][y] != blank) break;
			}

			return false;
			break;
		case bPawn:
			x = fromx + blackpawnmoves.oneStep;
			y = fromy;
			if (inBoard(x, y))
				if (board[x][y] == blank && x == tox && y == toy)
					return true;

			y = fromy + blackpawnmoves.eatsLeftx;
			if (inBoard(x, y))
				if (board[x][y] >= wPawn && board[x][y] <= wKing && x == tox && y == toy)
					return true;
				else if (board[fromx][y] == wPawn && gp.lastMovedTwoX == fromx && gp.lastMovedTwoY == y) //el passant
				{
					elPassant = true; return true;
				}

			y = fromy + blackpawnmoves.eatsRightx;
			if (inBoard(x, y))
				if (board[x][y] >= wPawn && board[x][y] <= wKing && x == tox && y == toy)
					return true;
				else if (board[fromx][y] == wPawn && gp.lastMovedTwoX == fromx && gp.lastMovedTwoY == y) //el passant
				{
					elPassant = true; return true;
				}
			y = fromy;
			x = fromx + blackpawnmoves.twoStep;
			if (inBoard(x, y))
				if (board[x][y] == blank && board[x + 1][y] == blank && x == tox && y == toy && fromx == 6) {
					twoMove = true;
					return true;
				}

			return false;
			break;
		default: return false;
		}
	}
	return false;
}

