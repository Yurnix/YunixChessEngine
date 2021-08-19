#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <algorithm>
#include "moves.h"
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <chrono>

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
	int fromx, fromy, tox, toy;
	system("cls");
	//string command = "play wave1.wav";
	
	//for (int i = 0; i < 10000; i++) { mciSendString(TEXT("play sound26.mp3"), NULL, 0, NULL); Sleep(100); }
	//cin.get();

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
		
		}
		cout << "  o----o----o----o----o----o----o----o----o" << endl;
		cout << "     a |  b |  c |  d |  e |  f |  g |  h" << endl;
		printf("Board evaluation : %4.3f\n", evaluateBoard(turn, currentBoard, gameparams));
		for (int i = 0; i < gameparams.whitePieces.size(); i++) cout << pieceName(gameparams.whitePieces[i].name) << " ";
		cout << endl;
		//cout << "Board evaluation : " << evaluateBoard(turn, currentBoard, gameparams) << endl;
		//cout << "Last moved two was on " << gameparams.lastMovedTwoX << " " << gameparams.lastMovedTwoY << endl;
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
	}
	//thread athread(imanas, ref(depth), ref(val1),ref(val2));
	//athread.join();
}