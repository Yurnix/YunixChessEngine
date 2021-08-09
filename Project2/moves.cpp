#include <iostream>


#define traverceX for(int i = 0; i < 8; i++)
#define traverceY for(int j = 0; j < 8; j++)

using namespace std;
const int N = 8;
enum Piece {
	blank, 
	wPawn, wRook, wKnight, wBishop, wQueen, wKing,
	bPawn, bRook, bKnight, bBishop, bQueen, bKing
};

static float vals[] = { 0, 1, 5, 3, 3, 8, 100, -1, -5, -3, -3, -8, -100 };
enum boardName { a, b, c, d, e, f, g, h };

inline bool white(short x) {
	if (x == wPawn ||
		x == wRook ||
		x == wKnight ||
		x == wQueen ||
		x == wKing)
		return true;
	return false;
}

static struct KnightMoves {
	int verticalOffset[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	int horizontalOffset[8] = { 2, 1, -1, -2, 2, 1, -1, -2 };
} knightmoves;

static struct QBRMoves {

	int leftY[7] = { -1, -2, -3, -4, -5, -6, -7 };

	int rightY[7] = { 1, 2, 3, 4, 5, 6, 7 };

	int upX[7] = { 1, 2, 3, 4, 5, 6, 7 };

	int downX[7] = { -1, -2, -3, -4, -5, -6, -7 };
} qbrmoves;

static struct KingMoves {
	int verticalOffset[8] = { 0, 0 ,1, -1, 1, -1, 1, -1 };
	int horizontalOffset[8] = { 1, -1, 0, 0, 1, -1, -1, 1 };
} kingmoves;

static struct WhitePawnMoves {
	int eatsLeftx = -1;
	int oneStep = 1;
	int twoStep = 2;
	int eatsRightx = 1;
} whitepawnmoves;

static struct BlackPawnMoves {
	int eatsLeftx = 1;
	int oneStep = -1;
	int twoStep = -2;
	int eatsRightx = -1;
} blackpawnmoves;

struct gameParams {
	bool canWhiteCastleShort = false, canWhiteCastleLong = false, canBlackCastleShort = false, canBlackCastleLong = false;
	int lastMovedTwoX = -1;
	int lastMovedTwoY = -1;
	int tillDraw = 0;
	bool whiteUnderCheck = false;
	bool blacckUnderCheck = false;
	bool mateOnBoard = false;
	bool draw = false;
};


static short currentBoard[8][8];

inline bool inBoard(int x, int y) {
	if (x < 0 || y < 0 || x >= N || y >= 8)
		return false;
	return true;
}

inline float evaluateBoard(bool turn, short* board[]) {
	float all = 0;
	all += (turn ? 0.3 : -0.3);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			all += vals[board[i][j]];
		}
	}
	return all;
}

inline float returnBlackMove() {
	return 0;
}

inline float returnWhiteMove() {
	return 0;
}

inline void initBoard(short board[][N], gameParams& gp) {
	gp.canWhiteCastleShort = gp.canWhiteCastleLong = gp.canBlackCastleShort = gp.canBlackCastleLong = true;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			currentBoard[i][j] = 0;
	for (int i = 0; i < N; i++) {
		currentBoard[1][i] = wPawn;
		currentBoard[6][i] = bPawn;
	}

	board[0][a] = board[0][h] = wRook;
	board[0][b] = board[0][g] = wKnight;
	board[0][c] = board[0][f] = wBishop;
	board[0][e] = wKing;
	board[0][d] = wQueen;

	board[7][a] = board[7][h] = bRook;
	board[7][b] = board[7][g] = bKnight;
	board[7][c] = board[7][f] = bBishop;
	board[7][e] = bKing;
	board[7][d] = bQueen;
}


inline void kingGrid(bool grid[][N], short board[][N], gameParams gp, bool turn) {
	
	int x, y;
	if (turn) {
		traverceX{
			traverceY{

				switch (board[i][j]) {
					case bKing:
						for(int ii = 0; ii < 8; ii++)
							if(inBoard(i + kingmoves.horizontalOffset[ii],j + kingmoves.verticalOffset[ii]))
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
inline bool makeAMove(int fromx, int fromy, int tox, int toy, short board[][N], gameParams& gp, bool turn) {
	bool elPassant = false;
	if (isItAValidMove(fromx, fromy, tox, toy, board, gp, turn, elPassant)) {
		gp.lastMovedTwoX = -1;
		gp.lastMovedTwoY = -1;
		if (turn && fromx == 100) { //white o - o
			gp.canWhiteCastleLong = false;
			gp.canWhiteCastleShort = false;
			board[0][e] = board[0][g] = blank;
			board[0][f] = wRook;
			board[0][g] = wKing;
			return true;
		}
		if (turn && fromx == 200) { //white o - o - o
			gp.canWhiteCastleLong = false;
			gp.canWhiteCastleShort = false;
			board[0][a] = board[0][e] = blank;
			board[0][d] = wRook;
			board[0][c] = wKing;
			return true;
		}
		if (!turn && fromx == 100) { //black o - o
			gp.canBlackCastleLong = false;
			gp.canBlackCastleShort = false;
			board[7][e] = board[7][g] = blank;
			board[7][f] = bRook;
			board[7][g] = bKing;
			return true;
		}
		if (!turn && fromx == 200) { //black o - o - o
			gp.canBlackCastleLong = false;
			gp.canBlackCastleShort = false;
			board[7][a] = board[7][e] = blank;
			board[7][d] = bRook;
			board[7][c] = bKing;
			return true;
		}
		if (board[fromx][fromy] == wPawn) {
			if (tox - fromx == 2) {
				gp.lastMovedTwoX = tox;
				gp.lastMovedTwoX = toy;
			}
			if (elPassant) {
				board[tox][toy - 1] = blank;
			}
		}
		if (board[fromx][fromy] == bPawn) {
			if (tox - fromx == 2) {
				gp.lastMovedTwoX = tox;
				gp.lastMovedTwoX = toy;
			}
			if (elPassant) {
				board[tox][toy + 1] = blank;
			}
		}

		if (turn && fromx == 0 && (fromy == a || fromy == e)) gp.canWhiteCastleLong = false;
		if (turn && fromx == 0 && (fromy == h || fromy == e)) gp.canWhiteCastleLong = false;
		if (!turn && fromx == 7 && (fromy == a || fromy == e)) gp.canBlackCastleLong = false;
		if (!turn && fromx == 7 && (fromy == h || fromy == e)) gp.canBlackCastleLong = false;
		board[tox][toy] = board[fromx][fromy];
		board[fromx][fromy] = blank;
		return true;
	}
	return false;
}

inline bool isItAValidMove(int fromx, int fromy, int tox, int toy, short board[][N], gameParams& gp, bool turn, bool &elPassant) {
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
	if (!turn && board[tox][toy] >= bPawn) return false; //black can't eat black
	int x, y;
	if (turn) {
		switch (board[fromx][fromy]) {
		case wKing: //TODO castelings
			for (int ii = 0; ii < 8; ii++) {
				x = fromx + kingmoves.horizontalOffset[ii];
				y = fromy + kingmoves.verticalOffset[ii];
				if (inBoard(x,y))
					if (x == tox && y == toy) {
						bool grid[N][N] = {};
						kingGrid(grid, board, gp, turn);
						if (grid[tox][toy]) return false;
						return true;
					}
			}
			return false;
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
			y = fromy + whitepawnmoves.oneStep;
			x = fromx;
			if (inBoard(x, y))
				if (board[x][y] == blank && x == tox && y == toy)
					return true;

			x = fromx + whitepawnmoves.eatsLeftx;
			if (inBoard(x, y))
				if (board[x][y] >= bPawn && board[x][y] <= bKing && x == tox && y == toy)
					return true;
				else if (board[x][fromy] == bPawn && gp.lastMovedTwoX == x && gp.lastMovedTwoY == fromy) //el passant
				{
					elPassant = true; return true;
				}

			x = fromx + whitepawnmoves.eatsRightx;
			if (inBoard(x, y))
				if (board[x][y] >= bPawn && board[x][y] <= bKing && x == tox && y == toy)
					return true;
				else if (board[x][fromy] == bPawn && gp.lastMovedTwoX == x && gp.lastMovedTwoY == fromy) //el passant
				{
					elPassant = true; return true;
				}

			x = fromx;
			y = fromy + whitepawnmoves.twoStep;
			if (inBoard(x, y))
				if (board[x][y] == blank && x == tox && y == toy && fromx == 1)
					return true;

			return false;
			break;
		default: return false;
		}
	}
	else
	{
		switch (board[fromx][fromy]) {
		case bKing:
			for (int ii = 0; ii < 8; ii++) {
				x = fromx + kingmoves.horizontalOffset[ii];
				y = fromy + kingmoves.verticalOffset[ii];
				if (inBoard(x, y))
					if (x == tox && y == toy) {
						bool grid[N][N] = {};
						kingGrid(grid, board, gp, turn);
						if (grid[tox][toy]) return false;
						return true;
					}
			}
			return false;
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
			y = fromy + blackpawnmoves.oneStep;
			x = fromx;
			if (inBoard(x, y))
				if (board[x][y] == blank && x == tox && y == toy)
					return true;

			x = fromx + blackpawnmoves.eatsLeftx;
			if (inBoard(x, y))
				if (board[x][y] >= wPawn && board[x][y] <= wKing && x == tox && y == toy)
					return true;
				else if (board[x][fromy] == wPawn && gp.lastMovedTwoX == x && gp.lastMovedTwoY == fromy) //el passant
				{
					elPassant = true; return true;
				}

			x = fromx + blackpawnmoves.eatsRightx;
			if (inBoard(x, y))
				if (board[x][y] >= wPawn && board[x][y] <= wKing && x == tox && y == toy)
					return true;
				else if (board[x][fromy] == wPawn && gp.lastMovedTwoX == x && gp.lastMovedTwoY == fromy) //el passant
				{
					elPassant = true; return true;
				}

			x = fromx;
			y = fromy + blackpawnmoves.twoStep;
			if (inBoard(x, y))
				if (board[x][y] == blank && x == tox && y == toy && fromx == 6)
					return true;

			return false;
			break;
		default: return false;
		}
	}
	return false;
}