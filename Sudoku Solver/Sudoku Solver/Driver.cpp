#include <iostream>
#include <ctime>
//#include <vector>
//#include "SudokuSolver.h"

#include "Sudoku.h" // debug
using namespace std;

int main() {

	Sudoku game;

	//bool test_validate = game.validate();
	//cout << "Status of validate: " << test_validate << endl;

	game.generate();
	game.printBoard();

	/*for (int i = 0; i < 80; i++) {
		game.generate();
		game.printBoard();
	}*/

	while (game.inserted_items != MAX) {
		game.generate();
		game.printBoard();
	}

	//game.board[8][7]->value = 1;
	//game.board[8][8]->value = 2;
	//game.printBoard();
	//game.validate(7, 6, 2);
	

	// similate outer while loop by putting a for loop here 
}