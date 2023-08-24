#include <iostream>
//#include <vector>
//#include "SudokuSolver.h"

#include "Sudoku.h" // debug
using namespace std;

int main() {

	Sudoku game;

	//bool test_validate = game.validate();
	//cout << "Status of validate: " << test_validate << endl;

	//game.generate();
	//game.printBoard();

	int current_total = game.inserted_items;
	int last_total = current_total;

	


	// test drivers

	/*for (int i = 0; i < 20; i++) {
		game.generate();
		current_total = game.inserted_items;

		if (current_total != last_total) {
			game.printBoard();
		}

		last_total = current_total;

	}*/

	while (game.inserted_items != MAX) {
		game.generate();
		current_total = game.inserted_items;

		if (current_total != last_total) {
			game.printBoard();
		}

		last_total = current_total;
	}

	//game.board[8][7]->value = 1;
	//game.board[8][8]->value = 2;
	//game.printBoard();
	//game.validate(7, 6, 2);
	

	// similate outer while loop by putting a for loop here 
}