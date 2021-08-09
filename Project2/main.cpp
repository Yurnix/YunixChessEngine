#include <iostream>
#include <map>
#include <string>
#include <thread>
#include "moves.cpp"
#include<vector>
using namespace std;

int main() {
	
	gameParams gameparams;
	initBoard(currentBoard, gameparams);
	traverceX{
		traverceY {
			printf("|%2d |", currentBoard[i][j]);
		}
		printf("\n");
	}
	int val1 = 1, val2 = 1, depth = 1;
	bool turn = true;
	

	/*while (gameparams.mateOnBoard || gameparams.tillDraw > 40) {

	}*/

	//thread athread(imanas, ref(depth), ref(val1),ref(val2));
	//athread.join();
	//cout << endl << depth << endl << val1 << endl << val2 <<  endl;
}