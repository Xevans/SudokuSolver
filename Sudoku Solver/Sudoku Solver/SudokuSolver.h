// solves a given sudoku board obtained from a Sudoku class
#include <iostream>
#include <vector>
#include "Sudoku.h"
using namespace std;

class SudokuSolver : public Sudoku {

	void PushEntry(); // push entry into insertion stack.
	void popEntry(); // pop entry from insertion stack.

	void makeEntry();  // Add/Map an entry to a chosen cell (add entry to stack).
	void removeEntry(); // Remove/Unmap an entry to a chosen cell (remove entry from stack).

	bool Solve(); // Calls the Solve operations and returns true if the board is solved.

	void showStep(); // prints descr of current move and calls printBoard.

	bool verifyBoard(); // checks to see if board is a winning board.


};

