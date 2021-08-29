#include "YunixChessLib.h"

bool makeAMove(int fromx, int fromy, int tox, int toy, short board[][N], gameParams& gp, bool turn) {
	//cout << "makeAMove move called with " << fromx << " " << fromy << " - " << tox << " " << toy << endl;
	bool elPassant = false;
	bool twoMoves = false;
	//cout << "returns: " << isItAValidMove(fromx, fromy, tox, toy, board, gp, turn, elPassant, twoMoves) << endl;
	if (isItAValidMove(fromx, fromy, tox, toy, board, gp, turn, elPassant, twoMoves)) {
		gp.lastMovedTwoX = -1;
		gp.lastMovedTwoY = -1;
		if (turn && fromx == 100) { //white o - o
			gp.canWhiteCastleLong = false;
			gp.canWhiteCastleShort = false;
			board[0][e] = board[0][h] = blank;
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
			board[7][e] = board[7][h] = blank;
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
			if (twoMoves) {
				gp.lastMovedTwoX = tox;
				gp.lastMovedTwoY = toy;
				//cout << tox << " to tttt " << toy << endl;
				//cin.get();
			}
			if (elPassant) {
				for (int i = 0; i < gp.whitePieces.size(); i++)
					if (gp.whitePieces[i].x == tox - 1 && gp.whitePieces[i].y == toy)
						gp.whitePieces.erase(gp.whitePieces.begin() + i);
				board[tox - 1][toy] = blank;
			}
		}
		if (board[fromx][fromy] == bPawn) {
			if (twoMoves) {
				gp.lastMovedTwoX = tox;
				gp.lastMovedTwoY = toy;
			}
			if (elPassant) {
				for (int i = 0; i < gp.blackPieces.size(); i++)
					if (gp.blackPieces[i].x == tox + 1 && gp.blackPieces[i].y == toy)
						gp.blackPieces.erase(gp.blackPieces.begin() + i);
				board[tox + 1][toy] = blank;
			}
		}

		if (turn && fromx == 0 && (fromy == a || fromy == e)) gp.canWhiteCastleLong = false;
		if (turn && fromx == 0 && (fromy == h || fromy == e)) gp.canWhiteCastleShort = false;
		if (!turn && fromx == 7 && (fromy == a || fromy == e)) gp.canBlackCastleLong = false;
		if (!turn && fromx == 7 && (fromy == h || fromy == e)) gp.canBlackCastleShort = false;


		//Delete piece if eaten
		if (board[tox][toy] >= wPawn && board[tox][toy] <= wKing) {
			for (int i = 0; i < gp.whitePieces.size(); i++)
				if (gp.whitePieces[i].x == tox && gp.whitePieces[i].y == toy)
					gp.whitePieces.erase(gp.whitePieces.begin() + i);
		}
		else if (board[tox][toy] >= bPawn && board[tox][toy] <= bKing) {
			for (int i = 0; i < gp.blackPieces.size(); i++)
				if (gp.blackPieces[i].x == tox && gp.blackPieces[i].y == toy)
					gp.blackPieces.erase(gp.blackPieces.begin() + i);
		}

		//Change piece position
		if (board[fromx][fromy] >= wPawn && board[fromx][fromy] <= wKing) {
			for (int i = 0; i < gp.whitePieces.size(); i++)
				if (gp.whitePieces[i].x == fromx && gp.whitePieces[i].y == fromy) {
					gp.whitePieces[i].x = tox;
					gp.whitePieces[i].y = toy;
				}

		}
		else if (board[fromx][fromy] >= bPawn && board[fromx][fromy] <= bKing) {
			for (int i = 0; i < gp.blackPieces.size(); i++)
				if (gp.blackPieces[i].x == fromx && gp.blackPieces[i].y == fromy) {
					gp.blackPieces[i].x = tox;
					gp.blackPieces[i].y = toy;
				}

		}



		board[tox][toy] = board[fromx][fromy];
		board[fromx][fromy] = blank;


		return true;
	}
	return false;
}