#include <iostream>
#include <string>
#include "YunixChessLib.h"

using namespace std;
void playsound() {
	//PlaySound(TEXT("sound26.mp3"), NULL,SND_FILENAME | SND_ASYNC);
	return;
}

int main() {

	gameParams gameparams;
	initBoard(currentBoard, gameparams);
	bool turn = true;
	
	int val1 = 1, val2 = 1, depth = 1;
	string move;
	int fromx, fromy, tox, toy, imove;
	system("cls");

	while (!gameparams.mateOnBoard && gameparams.tillDraw < 40) {
		system("cls");
		
		printf("Board evaluation : %4.3f\n", evaluateBoard(turn, currentBoard, gameparams));

		

		cout << ((turn) ? "White" : "Black") << " moves count: " << gameparams.possibleMoves.size() << endl;
		
		printf("\nMake a move: ");

		/* 
		PLAYER TO PLAY
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
				//thread athread(playsound);
				//Sleep(550);
			}
			else {
				cout << "Can't make this move, press enter" << endl;
				cin.get();
			}
		}
		else {
			cout << "Move not parsed, press enter" << endl;
			cin.get();
		}
		*/
		cout<<returnWhiteMove(currentBoard, gameparams);
		gameparams.blackIsComputer = true;
		gameparams.whiteIsComputer = true;
		imove = rand() % gameparams.possibleMoves.size();
		if (makeAMove(
			gameparams.possibleMoves[imove].fromx,
			gameparams.possibleMoves[imove].fromy,
			gameparams.possibleMoves[imove].tox,
			gameparams.possibleMoves[imove].toy,
			currentBoard,
			gameparams,
			turn)) {
			turn = !turn; cin.get()/*Sleep(500)*/;
		}
	}
	//thread athread(imanas, ref(depth), ref(val1),ref(val2));
	//athread.join();
}