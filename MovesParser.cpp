#include "YunixChessLib.h"

bool parseMove(string move, int& fromx, int& fromy, int& tox, int& toy) {
	int cords[4], s = 0, countO = 0;
	for (int i = 0; i < move.size(); i++) {
		if (s == 4)
			break;
		if (move[i] >= 'a' && move[i] <= 'h') {
			cords[s] = int(move[i] - 'a');
			s++;
		}
		else if (move[i] >= 'A' && move[i] <= 'H') {
			cords[s] = int(move[i] - 'a');
			s++;
		}
		else if (move[i] >= '1' && move[i] <= '8') {
			cords[s] = int(move[i] - '1');
			s++;
		}
		else if (move[i] == 'o' || move[i] == 'O') {
			countO++;
		}
	}
	if (s == 0) {
		if (countO == 2) {
			fromx = 100;
			//cout << "Short casteling" << endl;
			return true;
		}
		if (countO == 3) {
			fromx = 200;
			//cout << "Long casteling" << endl;
			return true;
		}
		return false;
	}
	if (s == 4) {
		fromy = cords[0];
		fromx = cords[1];
		toy = cords[2];
		tox = cords[3];
		//cout << endl << move << endl << "Move : " << fromy << " " << fromx << " " << toy << " " << tox << endl;
		return true;
	}
	//cout << move << " not recognized" << endl;
	return false;
}