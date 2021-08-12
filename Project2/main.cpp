#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <algorithm>
#include "moves.cpp"
#include <vector>
using namespace std;

int main() {
	
	gameParams gameparams;
	initBoard(currentBoard, gameparams);
	bool turn = true;
	
	int val1 = 1, val2 = 1, depth = 1;
	string move;
	int fromx, fromy, tox, toy;
	system("cls");
	while (!gameparams.mateOnBoard && gameparams.tillDraw < 40) {
		system("cls");
		for(int i = 7; i >= 0; i--) {
			cout << "  o----o----o----o----o----o----o----o----o" << endl;
			cout << (i + 1) << ":";
			//printf("%d:",(i+1));
			traverceY{
				cout << "| " << pieceName(currentBoard[i][j]) << " ";
			//printf("|%s ", pieceName(currentBoard[i][j]));
			}
			cout << "|" << endl;
		//printf("|\n");
		}
		cout << "  o----o----o----o----o----o----o----o----o" << endl;
		cout << "     a |  b |  c |  d |  e |  f |  g |  h" << endl;
		cout << "Last moved two was on " << gameparams.lastMovedTwoX << " " << gameparams.lastMovedTwoY << endl;
		printf("\nMake a move: ");
		getline(cin, move);
		if (move == "clear") {
			initBoard(currentBoard, gameparams);
			turn = true;
			continue;
		}
		//cout <<endl<< move << endl;
		if (parseMove(move, fromx, fromy, tox, toy)) {
			if (makeAMove(fromx, fromy, tox, toy, currentBoard, gameparams, turn)) {
				turn = !turn;
				
			}
			else {
				cout << "Can't make this move, press enter" << endl;
				cin.get();
			}
		}
		else {
			cout << "Move not recognized, press enter" << endl;
			cin.get();
		}
	}

	//thread athread(imanas, ref(depth), ref(val1),ref(val2));
	//athread.join();
	//cout << endl << depth << endl << val1 << endl << val2 <<  endl;
}