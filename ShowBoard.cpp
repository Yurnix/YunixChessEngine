#include "YunixChessLib.h"

void showBoard(short board[][N], gameParams gameparams) {
	for (int i = 7; i >= 0; i--) {
		cout << "  o----o----o----o----o----o----o----o----o" << endl;
		cout << (i + 1) << ":";
		traverceY{
			cout << "| " << pieceName(currentBoard[i][j]) << " ";
		}
		cout << "|" << endl;
	}
	cout << "  o----o----o----o----o----o----o----o----o" << endl;
	cout << "     a |  b |  c |  d |  e |  f |  g |  h" << endl;

	for (int i = 0; i < gameparams.whitePieces.size(); i++) cout << pieceName(gameparams.whitePieces[i].name) << " ";
	cout << endl << endl;

	for (int i = 0; i < gameparams.blackPieces.size(); i++) cout << pieceName(gameparams.blackPieces[i].name) << " ";
	cout << endl;
}