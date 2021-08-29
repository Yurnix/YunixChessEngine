#include "YunixChessLib.h"

float evaluateBoard(bool turn, short board[][N], gameParams& gp) {
	float all = 0;
	int tox, toy;
	all += (turn ? 0.1 : -0.1);

	amove imove;
	gp.possibleMoves.clear();

	if (turn) {
		if (gp.canWhiteCastleShort) {
			bool s1, s2;
			if (isItAValidMove(100, 0, 0, 0, board, gp, turn, s1, s2)) {
				imove.fromx = 100;
				all += castleValue;
				gp.possibleMoves.push_back(imove);
			}
		}
		if (gp.canWhiteCastleLong) {
			bool s1, s2;
			if (isItAValidMove(200, 0, 0, 0, board, gp, turn, s1, s2)) {
				imove.fromx = 200;
				all += castleValue;
				gp.possibleMoves.push_back(imove);
			}
		}
	}
	else {
		if (gp.canBlackCastleShort) {
			bool s1, s2;
			if (isItAValidMove(100, 0, 0, 0, board, gp, turn, s1, s2)) {
				imove.fromx = 100;
				all -= castleValue;
				gp.possibleMoves.push_back(imove);
			}
		}
		if (gp.canBlackCastleLong) {
			bool s1, s2;
			if (isItAValidMove(200, 0, 0, 0, board, gp, turn, s1, s2)) {
				imove.fromx = 200;
				all -= castleValue;
				gp.possibleMoves.push_back(imove);
			}
		}
	}

	// All moves
	for (int i = 0; i < gp.whitePieces.size(); i++) {
		switch (gp.whitePieces[i].name) {
		case wPawn:
			imove.fromx = gp.whitePieces[i].x;
			imove.fromy = gp.whitePieces[i].y;

			all += vals[wPawn];
			tox = gp.whitePieces[i].x + whitepawnmoves.oneStep;
			toy = gp.whitePieces[i].y;
			if (inBoard(tox, toy))
				if (board[tox][toy] == blank) {
					all += blankValue;
					inswhite
				}
			toy = gp.whitePieces[i].y + whitepawnmoves.eatsLeftx;
			if (inBoard(tox, toy))
				if (board[tox][toy] != blank) {
					all += threatValue;
					inswhite
				}
				else if (board[gp.whitePieces[i].x][toy] == bPawn && gp.lastMovedTwoX == gp.whitePieces[i].x && gp.lastMovedTwoY == toy) //el passant
				{
					all += threatValue;
					inswhite
				}

			toy = gp.whitePieces[i].y + whitepawnmoves.eatsRightx;
			if (inBoard(tox, toy))
				if (board[tox][toy] != blank) {
					all += threatValue;
					inswhite
				}
				else if (board[gp.whitePieces[i].x][toy] == bPawn && gp.lastMovedTwoX == gp.whitePieces[i].x && gp.lastMovedTwoY == toy) //el passant
				{
					all += threatValue;
					inswhite
				}

			toy = gp.whitePieces[i].y;
			tox = gp.whitePieces[i].x + whitepawnmoves.twoStep;
			if (inBoard(tox, toy))
				if (board[tox][toy] == blank && board[tox - 1][toy] == blank && gp.whitePieces[i].x == 1) { //Two step
					all += blankValue;
					inswhite
				}

			break;
		case wKnight:
			imove.fromx = gp.whitePieces[i].x;
			imove.fromy = gp.whitePieces[i].y;

			all += vals[wKnight];
			for (int ii = 0; ii < 8; ii++) {
				tox = gp.whitePieces[i].x + knightmoves.horizontalOffset[ii];
				toy = gp.whitePieces[i].y + knightmoves.verticalOffset[ii];
				if (inBoard(tox, toy))
					if (board[tox][toy] == blank) {
						all += blankValue;
						inswhite
					}
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) {
						all += threatValue;
						inswhite
					}
			}
			break;
		case wKing:
		{
			imove.fromx = gp.whitePieces[i].x;
			imove.fromy = gp.whitePieces[i].y;

			all += vals[wKing];
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			for (int ii = 0; ii < 8; ii++) {
				tox = gp.whitePieces[i].x + kingmoves.horizontalOffset[ii];
				toy = gp.whitePieces[i].y + kingmoves.verticalOffset[ii];
				if (inBoard(tox, toy)) {
					if (grid[tox][toy] && board[tox][toy] == blank) {
						all += blankValue;
						inswhite
					}
				}
			}
		}
		break;
		case wQueen:
			imove.fromx = gp.whitePieces[i].x;
			imove.fromy = gp.whitePieces[i].y;

			all += vals[wQueen];
			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.leftY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.rightY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.rightY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.leftY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.leftY[ii];
				toy = gp.whitePieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.rightY[ii];
				toy = gp.whitePieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x;
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x;
				toy = gp.whitePieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}
			break;

		case wBishop:
			imove.fromx = gp.whitePieces[i].x;
			imove.fromy = gp.whitePieces[i].y;

			all += vals[wBishop];
			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.leftY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.rightY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.rightY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.leftY[ii];
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}
			break;
		case wRook:
			imove.fromx = gp.whitePieces[i].x;
			imove.fromy = gp.whitePieces[i].y;

			all += vals[wRook];
			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.leftY[ii];
				toy = gp.whitePieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x + qbrmoves.rightY[ii];
				toy = gp.whitePieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x;
				toy = gp.whitePieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.whitePieces[i].x;
				toy = gp.whitePieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all += blankValue; inswhite }
					else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) { all += threatValue; inswhite }
					else break;
				}
				else break;
			}

			break;
		}
	}

	/*
	*
	Black Pieces Moves
	*
	*/
	for (int i = 0; i < gp.blackPieces.size(); i++) {
		switch (gp.blackPieces[i].name) {
		case bPawn:
			imove.fromx = gp.blackPieces[i].x;
			imove.fromy = gp.blackPieces[i].y;

			all += vals[bPawn];
			tox = gp.blackPieces[i].x + blackpawnmoves.oneStep;
			toy = gp.blackPieces[i].y;
			if (inBoard(tox, toy))
				if (board[tox][toy] == blank) {
					all -= blankValue;
					insblack
				}
			toy = gp.blackPieces[i].y + blackpawnmoves.eatsLeftx;
			if (inBoard(tox, toy))
				if (board[tox][toy] != blank) {
					all -= threatValue;
					insblack
				}
				else if (board[gp.blackPieces[i].x][toy] == bPawn && gp.lastMovedTwoX == gp.blackPieces[i].x && gp.lastMovedTwoY == toy) //el passant
				{
					all -= threatValue;
					insblack
				}
			toy = gp.blackPieces[i].y + blackpawnmoves.eatsRightx;
			if (inBoard(tox, toy))
				if (board[tox][toy] != blank) {
					all -= threatValue;
					insblack
				}
				else if (board[gp.blackPieces[i].x][toy] == bPawn && gp.lastMovedTwoX == gp.blackPieces[i].x && gp.lastMovedTwoY == toy) //el passant
				{
					all -= threatValue;
					insblack
				}

			toy = gp.blackPieces[i].y;
			tox = gp.blackPieces[i].x + blackpawnmoves.twoStep;
			if (inBoard(tox, toy))
				if (board[tox][toy] == blank && board[tox + 1][toy] == blank && gp.blackPieces[i].x == 6) { //Two step
					all -= blankValue;
					insblack
				}

			break;
		case bKnight:
			imove.fromx = gp.blackPieces[i].x;
			imove.fromy = gp.blackPieces[i].y;

			all += vals[bKnight];
			for (int ii = 0; ii < 8; ii++) {
				tox = gp.blackPieces[i].x + knightmoves.horizontalOffset[ii];
				toy = gp.blackPieces[i].y + knightmoves.verticalOffset[ii];
				if (inBoard(tox, toy))
					if (board[tox][toy] == blank) {
						all -= blankValue;
						insblack
					}
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) {
						all -= threatValue;
						insblack
					}
			}
			break;
		case bKing:
		{
			imove.fromx = gp.blackPieces[i].x;
			imove.fromy = gp.blackPieces[i].y;

			all += vals[bKing];
			bool grid[N][N] = {};
			kingGrid(grid, board, gp, turn);
			for (int ii = 0; ii < 8; ii++) {
				tox = gp.blackPieces[i].x + kingmoves.horizontalOffset[ii];
				toy = gp.blackPieces[i].y + kingmoves.verticalOffset[ii];
				if (inBoard(tox, toy)) {

					if (grid[tox][toy] && board[tox][toy] == blank) {
						all -= blankValue;
						insblack
					}
				}
			}
		}
		break;
		case bQueen:
			imove.fromx = gp.blackPieces[i].x;
			imove.fromy = gp.blackPieces[i].y;

			all += vals[bQueen];
			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.leftY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.rightY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.rightY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.leftY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.leftY[ii];
				toy = gp.blackPieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.rightY[ii];
				toy = gp.blackPieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x;
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x;
				toy = gp.blackPieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}
			break;

		case bBishop:
			imove.fromx = gp.blackPieces[i].x;
			imove.fromy = gp.blackPieces[i].y;

			all += vals[bBishop];
			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.leftY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.rightY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.rightY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.leftY[ii];
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}
			break;
		case bRook:
			imove.fromx = gp.blackPieces[i].x;
			imove.fromy = gp.blackPieces[i].y;

			all += vals[bRook];
			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.leftY[ii];
				toy = gp.blackPieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x + qbrmoves.rightY[ii];
				toy = gp.blackPieces[i].y;
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x;
				toy = gp.blackPieces[i].y + qbrmoves.upX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			for (int ii = 0; ii < 7; ii++) {
				tox = gp.blackPieces[i].x;
				toy = gp.blackPieces[i].y + qbrmoves.downX[ii];
				if (inBoard(tox, toy)) {
					if (board[tox][toy] == blank) { all -= blankValue; insblack }
					else if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) { all -= threatValue; insblack }
					else break;
				}
				else break;
			}

			break;
		}
	}

	return all;
}