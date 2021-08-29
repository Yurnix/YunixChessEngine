#include "YunixChessLib.h"


float returnBlackMove() {
	return 0;
}

float returnWhiteMove(short board[][N], gameParams& gp) { //TODO
	bool turn = true;
	short nowBoard[N][N];
	gameParams ngp;
	ngp = gp;
	memcpy(nowBoard, board, N * N * sizeof(short));
	cout << endl;
	traverceX{ traverceY { cout << nowBoard[i][j] << " "; } cout << endl; }
	return 0;
}