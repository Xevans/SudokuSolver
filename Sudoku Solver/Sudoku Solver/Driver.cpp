#include <iostream>
#include <ctime>
//#include <vector>
//#include "SudokuSolver.h"

#include "Sudoku.h" // debug
using namespace std;

int main() {

	Sudoku game;

	bool test_validate = game.validate();

	cout << "Status of validate: " << test_validate << endl;
}