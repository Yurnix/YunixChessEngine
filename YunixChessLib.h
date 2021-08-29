#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <chrono>
#include <random>

#define traverceX for(int i = 0; i < 8; i++)
#define traverceY for(int j = 0; j < 8; j++)
#define inswhite if (turn) { imove.tox = tox; imove.toy = toy; gp.possibleMoves.push_back(imove); }
#define insblack if (!turn) { imove.tox = tox; imove.toy = toy; gp.possibleMoves.push_back(imove); }
using namespace std;

const int N = 8;
const float blankValue = 0.01;
const float threatValue = 0.015;
const float castleValue = 0.2;
static  float tillLastRow[] = { 0, 0 , 0.1, 0.12 , 0.16 , 0.4, 1, 3 };
static float vals[] = { 0, 1, 5, 3, 3, 8, 1000, -1, -5, -3, -3, -8, -1000 };

enum boardName { a, b, c, d, e, f, g, h };

enum Piece {
	blank,
	wPawn, wRook, wKnight, wBishop, wQueen, wKing,
	bPawn, bRook, bKnight, bBishop, bQueen, bKing
};

struct amove {
	int fromx; int fromy; int tox; int toy;
};

struct KnightMoves {
	int verticalOffset[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };
	int horizontalOffset[8] = { 2, 1, -1, -2,  2,  1, -1, -2 };
};

struct QBRMoves {

	int leftY[7] = { -1, -2, -3, -4, -5, -6, -7 };
	int rightY[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int upX[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int downX[7] = { -1, -2, -3, -4, -5, -6, -7 };
};

struct KingMoves {
	int verticalOffset[8] = { 0, 0 ,1, -1, 1, -1, 1, -1 };
	int horizontalOffset[8] = { 1, -1, 0, 0, 1, -1, -1, 1 };
};

struct WhitePawnMoves {
	int eatsLeftx = -1;
	int oneStep = 1;
	int twoStep = 2;
	int eatsRightx = 1;
};

struct BlackPawnMoves {
	int eatsLeftx = 1;
	int oneStep = -1;
	int twoStep = -2;
	int eatsRightx = -1;
};

struct chessPiece {
	short name;
	int x, y;
};

struct gameParams {
	bool canWhiteCastleShort = false, canWhiteCastleLong = false, canBlackCastleShort = false, canBlackCastleLong = false;
	int lastMovedTwoX = -1;
	int lastMovedTwoY = -1;
	int tillDraw = 0;
	bool whiteUnderCheck = false;
	bool blacckUnderCheck = false;
	bool mateOnBoard = false;
	bool draw = false;
	bool whiteIsComputer = false;
	bool blackIsComputer = false;
	int transformPawnTo = -1;
	vector <chessPiece> whitePieces;
	vector <chessPiece> blackPieces;
	vector <amove> possibleMoves;
};

static short currentBoard[8][8];
static KnightMoves  knightmoves;
static QBRMoves  qbrmoves; // Queen Bishop Rook moves
static KingMoves kingmoves;
static WhitePawnMoves whitepawnmoves;
static BlackPawnMoves blackpawnmoves;

static string pieceName(int p) {
	switch (p) {
	case blank: return "  ";
	case wPawn: return "wp";
	case wRook: return "wR";
	case wKnight: return "wN";
	case wBishop: return "wB";
	case wQueen: return "wQ";
	case wKing: return "wK";
	case bPawn: return "bp";
	case bRook: return "bR";
	case bKnight: return "bN";
	case bBishop: return "bB";
	case bQueen: return "bQ";
	case bKing: return "bK";
	}
	return "NN";
}

void kingGrid(bool grid[][N], short board[][N], gameParams gp, bool turn);
bool isItAValidMove(int fromx, int fromy, int tox, int toy, short board[][N], gameParams& gp, bool turn, bool& elPassant, bool& twoMove);
void kingGrid(bool grid[][N], short board[][N], gameParams gp, bool turn);
bool makeAMove(int fromx, int fromy, int tox, int toy, short board[][N], gameParams& gp, bool turn);
float evaluateBoard(bool turn, short board[][N], gameParams& gp);
bool isItAValidMove(int fromx, int fromy, int tox, int toy, short board[][N], gameParams& gp, bool turn, bool& elPassant, bool& twoMove);
void fillGP(short board[][N], gameParams& gp);
void initBoard(short board[][N], gameParams& gp);
bool inBoard(int x, int y);
float returnWhiteMove(short board[][N], gameParams& gp);
float returnBlackMove(short board[][N], gameParams& gp);