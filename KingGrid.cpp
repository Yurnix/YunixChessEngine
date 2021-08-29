#include "YunixChessLib.h"


void kingGrid(bool grid[][N], short board[][N], gameParams gp, bool turn) {

	int x, y;
	if (turn) {
		traverceX{
			traverceY{

				switch (board[i][j]) {
					case bKing:
						for (int ii = 0; ii < 8; ii++)
							if (inBoard(i + kingmoves.horizontalOffset[ii],j + kingmoves.verticalOffset[ii]))
								grid[i + kingmoves.horizontalOffset[ii]][j + kingmoves.verticalOffset[ii]] = true;
						break;
					case bKnight:
						for (int ii = 0; ii < 8; ii++)
							if (inBoard(i + knightmoves.horizontalOffset[ii], j + knightmoves.verticalOffset[ii]))
								grid[i + knightmoves.horizontalOffset[ii]][j + knightmoves.verticalOffset[ii]] = true;
						break;
					case bQueen:
						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						break;
					case bBishop:
						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}
						break;
					case bRook:
						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}
						break;
					case bPawn:
						y = j + blackpawnmoves.oneStep;
						x = i + blackpawnmoves.eatsLeftx;
						if (inBoard(x, y))
							grid[x][y] = true;
						x = i + blackpawnmoves.eatsRightx;
						if (inBoard(x, y))
							grid[x][y] = true;
						break;
					case wKing: case wQueen: case wKnight: case wBishop: case wRook: case wPawn:
						grid[i][j] = true;
						break;
				}
			}
		}
	}
	else {
		traverceX{
			traverceY{

				switch (board[i][j]) {
					case wKing:
						for (int ii = 0; ii < 8; ii++)
							if (inBoard(i + kingmoves.horizontalOffset[ii],j + kingmoves.verticalOffset[ii]))
								grid[i + kingmoves.horizontalOffset[ii]][j + kingmoves.verticalOffset[ii]] = true;
						break;
					case wKnight:
						for (int ii = 0; ii < 8; ii++)
							if (inBoard(i + knightmoves.horizontalOffset[ii], j + knightmoves.verticalOffset[ii]))
								grid[i + knightmoves.horizontalOffset[ii]][j + knightmoves.verticalOffset[ii]] = true;
						break;
					case wQueen:
						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						break;
					case wBishop:
						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}
						break;
					case wRook:
						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.leftY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i + qbrmoves.rightY[ii];
							y = j;
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.downX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}

						for (int ii = 0; ii < 7; ii++) {
							x = i;
							y = j + qbrmoves.upX[ii];
							if (inBoard(x, y)) {
								grid[x][y] = true;
								if (board[x][y] != blank)
									break;
							}
							else break;
						}
						break;
					case wPawn:
						y = j + whitepawnmoves.oneStep;
						x = i + whitepawnmoves.eatsLeftx;
						if (inBoard(x, y))
							grid[x][y] = true;
						x = i + blackpawnmoves.eatsRightx;
						if (inBoard(x, y))
							grid[x][y] = true;
						break;
					case bKing: case bQueen: case bKnight: case bBishop: case bRook: case bPawn:
						grid[i][j] = true;
						break;
				}
			}
		}
	}
	return;
}