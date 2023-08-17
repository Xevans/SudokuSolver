// generates a sudoku board and pre fills extries in each sector
#include <iostream>
#include <vector>
#include <random>
using namespace std;

#define MAX 81 // total Cells that exist on a 9x9 Sudoku board
# define grid 9 // number of cells in a subset of a grid


// structure for subgrid object. [3x3 grid with a sector number to indicate its relative position to other subgrids.]
struct cell {
	int cell_number = 0;
	int value = 0;
	int sector = 0;
	bool status = false;
	//cell* next_cell;
};




class Sudoku {
public:
	// Attributes
	int inserted_items = 0; // count of currently uccupied cells on the grid. 
	cell* board[9][9]; // 3 by 3 of 3 by 3s
	//vector<cell*> board;
	int reference_points[9]{11, 14, 17, 38, 41, 44, 65, 68, 71}; // list of every subsection's central identifier

	vector<int> occupied_cells;

	// Opertations
	Sudoku();
	~Sudoku();

	void initialize(); // initialize a list of 9 2D matricies with each cell's values initialized.
	void generate(); // Randomly choose a cell and insert a single digit.
	bool validate(int, int, int); // verify that the board follows the rules of sudoku. Two step process.
	bool subset_validate(int, int, int); // checks if the current entry already exists in that sector.
	bool cross_validate(int, int, int); // Checks if the current entry already exists in the row and column it was placed in.
	


	// printing
	void printBoard(); // print a visual representation of the board

	// Alloc Memory Clean Up
	void deleteBoard(); // delete all cells in the board.

	// Utility ops
	int* shuffle();  // shuffle a fixed size array (50 swaps).
};


Sudoku::Sudoku() {
	cout << "Begin" << endl;
	initialize();
}

Sudoku::~Sudoku() {
	cout << "End" << endl;
	//destroy()
}



void Sudoku::initialize() {
	// initialize each index in sudokuGrid with a cell pointer.
	int counter = 1;

	for (int i = 0; i < grid; i++) {
		for (int j = 0; j < grid; j++) {
			cell* temp = new cell;
			temp->cell_number = counter;
			temp->value = 0;
			temp->status = false;
			board[i][j] = temp;
			counter++;
		}
	}
/*
	for (int i = 0; i < grid; i++) {
		for (int j = 0; j < grid; j++) {
			cout << board[i][j]->value << endl;
		}
	}
	*/

	// initialize reference points

	cout << "Reference points" << endl;
	for (int i = 0; i < grid; i++) {
		cout << "[" << reference_points[i] << "]" << endl;
	}
}



void Sudoku::generate() {
	
	bool existing = false;
	bool valid = false;
	int row = -1;
	int col = -1;
	int entry = -1;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 81); // inclusive

	// !!!(parent loop)!!! loop until inserted_items == 81 // remember to modify inserted items when debugging with existing values.

	int random_number = dis(gen);

	// if random number does not exist in array of occupied_cells (a list of cell numbers)
	for (int i = 0; i < grid; i++) {
		for (int j = 0; j < grid; j++) {
			if (board[i][j]->cell_number == random_number) {
				row = i;
				col = j;
				break;
			}
		}

		if (row > -1 && col > -1) {
			break;
		}
	}

	// if chosen cell is not occupied, go to next step, otherwise loop
	if (board[row][col]->status != true) {

		// choose a number from the list in order until 1 or none satisfy
		for (int i = 0; i < grid; i++) {

			if (validate(row, col, i+1) == true) {
				entry = i+1;
				valid = true;
				break;
			}
		}


		//if entry is valid, write entry to cell coordinates.
		if (valid) {

			cout << "adding new entry: " << entry << " at " << row << "," << col << endl;

			board[row][col]->value = entry;
			board[row][col]->status = true;
			inserted_items++;
		}

		
	}
	

	// reset
	existing = false;
	row = -1;
	col = -1;
	entry = -1;

	/*while (inserted_items < MAX) {
		
	}*/

}



bool Sudoku::validate(int row, int col, int entry) {

	cout << "Validating... " << entry << " at " << row << "," << col << endl;

	// call subset validation that returns true or false, store the value
	bool subset_check = subset_validate(row, col, entry);

	// call cross validation that returns true or false, store the value
	bool cross_check = cross_validate(row, col, entry);

	cout << "subset-check status: " << subset_check << endl;
	cout << "cross-check status:" << cross_check << endl;


	// if subset_check == true AND cross_check == true, return true otherwise return false
	if (subset_check == true && cross_check == true) {
		return true; // board is valid!
	}
	
	return false;
}

void Sudoku::printBoard() {

	cout << endl;

	for (int i = 0; i < grid; i++) {
		for (int j = 0; j < grid; j++) {
			cout << board[i][j]->value << " ";

			if ((j + 1) % 9 == 0) { // if the current col iteration is divisible by 9, end line
				cout << endl;
			} 
			else if ((j + 1) % 3 == 0) { // if the current col iteration is not divisible by 9 but 3, add a bar
				cout << "| ";
			}
		}

		if ((i + 1) % 3 == 0) { // if the current row iteration is divisible by 3, display a divider
			cout << "---------------------" << endl;
		}
	}

	/*cout << "cell nums" << endl;

	for (int i = 0; i < grid; i++) {
		for (int j = 0; j < grid; j++) {
			cout << board[i][j]->cell_number << " ";

			if ((j + 1) % 9 == 0) { // if the current col iteration is divisible by 9, end line
				cout << endl;
			}
			else if ((j + 1) % 3 == 0) { // if the current col iteration is not divisible by 9 but 3, add a bar
				cout << "| ";
			}
		}

		if ((i + 1) % 3 == 0) { // if the current row iteration is divisible by 3, display a divider
			cout << "---------------------" << endl;
		}
	}*/
}

bool Sudoku::subset_validate(int row, int col, int entry) {

	// determine center point of sector

	// center point's coordinates
	int reference_row = 0;
	int reference_col = 0;
	bool found = false; // When subset's center is found, mark true.

	// box neighbor check for reference point coordinates
	for (int i = row - 1; i <= row + 1; i++) {
		//if the current row is out of bounds, skip current iteration
		if (i < 0 || i > 8) {
			continue;
		}

		for (int j = col - 1; j <= col + 1; j++) {
			//if the current col is out of bounds, skip current iteration
			if (j < 0 || j > 8) {
				continue;
			}

			for (int k = 0; k < grid; k++) {
				if (board[i][j]->cell_number == reference_points[k]) {
					reference_row = i;
					reference_col = j;
					found = true;
					break;
				}
			}

			if (found == true) {
				break;
			}
		}

		if (found == true) {
			break;
		}
	}

	// box neighbor check for identical entry to current arbitrary entry.
	for (int i = reference_row - 1; i <= reference_row + 1; i++) {
		for (int j = reference_col - 1; j <= reference_col + 1; j++) {

			// if the value of the the current cell is the same as the entry AND the coordinates are NOT the same
			if (board[i][j]->value == entry && i != row && j != col) {
				return false;
			}
		}
	}

	return true;
}


bool Sudoku::cross_validate(int row, int col, int entry) {
	// check every cell in the same row as the entry
	// if an entry is the same as the current arbitrary entry and the coordiantes are not the same, return false.

	for (int j = 0; j < grid; j++) {
		if (board[row][j]->value == entry && j != col) {
			return false;
		}
	}

	// check every cell in the same col as the entry
	// if an entry is the same as the current arbitrary entry and the coordiantes are not the same, return false.
	for (int i = 0; i < grid; i++) {
		if (board[i][col]->value == entry && i != row) {
			return false;
		}
	}

	return true;
}