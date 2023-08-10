#include <iostream>
#include <ctime>
//#include <vector>
//#include "SudokuSolver.h"

#include "Sudoku.h" // debug
using namespace std;

int main() {

	Sudoku game;

	game.initialize();
	game.preFill();
	//game.printBoard();

	// test
	/*
	bool lock = true;
	int temp_size = 9;
	int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	for (int i = 0; i < 50; i++) {
		// shuffle temporary array (consider making its own function that accepts and returns an array by reference)
		int pick_1;
		int pick_2;

		pick_1 = (rand() % temp_size);// randomly choose an index

		while (lock == true) {
			pick_2 = (rand() % temp_size);

			if (pick_2 != pick_1) {
				lock = false;
			}
		}

		lock = true;

		int temp_item = arr[pick_2];
		arr[pick_2] = arr[pick_1];
		arr[pick_1] = temp_item;

		cout << "Picks" << endl;
		cout << pick_1 << endl;
		cout << pick_2 << endl;
	}

	for (int i = 0; i < 9; i++) {
		cout << arr[i] << endl;
	}

	cout << "Done" << endl;

	*/
}