#include "YunixChessLib.h"

bool inBoard(int x, int y) {
	if (x < 0 || y < 0 || x >= N || y >= N)
		return false;
	return true;
}

void fillGP(short board[][N], gameParams& gp) {
	chessPiece aPiece;
	traverceX
		traverceY{
		if (board[i][j] != blank) {
		aPiece.x = i;
		aPiece.y = j;
		aPiece.name = board[i][j];
		(aPiece.name >= wPawn && aPiece.name <= wKing) ? gp.whitePieces.push_back(aPiece) : gp.blackPieces.push_back(aPiece);
		}
	}
}

void initBoard(short board[][N], gameParams& gp) {
	gp.canWhiteCastleShort = gp.canWhiteCastleLong = gp.canBlackCastleShort = gp.canBlackCastleLong = true;
	gp.mateOnBoard = false;
	gp.tillDraw = 0;

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

	fillGP(board, gp);
}
