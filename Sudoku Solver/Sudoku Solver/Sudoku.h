// generates a sudoku board and pre fills extries in each sector
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define MAX 81
# define grid 9


struct subgrid {
	int subsection[3][3];
	int sector = 0;
};

class Sudoku {
public:
	int inserted_items = 0;

	// Stack memory for all entries
	vector<int> insertion_stack;
	vector<subgrid> gridList;
	

	// Initialization
	Sudoku();
	~Sudoku();

	void initialize(); // initialize a list of 9 2D matricies with each cell's values initialized.
	void preFill(); // Arbitrarilly choose cells and insert entries in each sector but one.
	void printBoard(); // Represent the board in ASCII symbols.


	// Alloc Memory Clean Up
	void deleteBoard(); // delete all cells in the board.
	void emptyStack(); // empty stack elements.

	int * shuffle();  // shuffle a fixed size array (50 swaps).

	bool crossExamine(int arr[9], int sudoku_grid[9][9], int row);

	int* meticAdd(int sudoku_grid[9][9], int row); // meticulous adding of individual entries
};


Sudoku::Sudoku() {
	cout << "Begin" << endl;
}

Sudoku::~Sudoku() {
	cout << "End" << endl;
}

void Sudoku::initialize() {
	for (int i = 0; i < grid; i++) {
		subgrid temp;
		temp.sector = i;

		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				temp.subsection[j][k] = 0;
			}
		}

		gridList.push_back(temp);
	}
}

void Sudoku::printBoard() {
	
	// loop the vector
	for (int i = 0; i < gridList.size(); i++) {

		cout << "Section: " << i + 1 << endl;

		// print the grid stored in the current vector element.
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cout << gridList[i].subsection[j][k];
			}
			cout << endl;
		}

		cout << endl;
	}
}


void Sudoku::preFill() {

	// create a 2d matrix representative of the entire board. (Will be fore generation and mapping purposes only)

	int sudoku_grid[9][9];
	int * arr;
	bool grid_complete = false;
	int row = 0;
	bool valid = false;

	// per row:
	// if on the first row, shuffle the temp array and append it to the first row then move to next.
	// shuffle temp array. If none of its elements are column repeats, append it to the current row being worked on then move to next row until all 9 rows are complete. otherwise, repeate this step
	// given the nature of the array, there is no need to worry about row repeats.

	
	while (grid_complete == false) {

		//shuffle
		// validate
		// if validation fail, shuffle again
		// else continue to next row and shuffle

		if (row == 0) { // initial row
			arr = shuffle();
			for (int i = 0; i < 9; i++) {
				sudoku_grid[row][i] = arr[i];
			}
			row++;
			continue;
		}


		arr = meticAdd(sudoku_grid, row);

		// debug

		cout << "Current Grid:" << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (sudoku_grid[i][j] != NULL) {
					cout << sudoku_grid[i][j] << " ";
				}
			}
			cout << endl;
		}

		cout << "Meticulous Addition:" << endl;
		for (int i = 0; i < 9; i++) {
			cout << arr[i] << " ";
		}

		cout << endl;

		// validate
		valid = crossExamine(arr, sudoku_grid, row);

		if (valid == true) { // if valid
			// add the new row
			for (int i = 0; i < 9; i++) {
				sudoku_grid[row][i] = arr[i];
			}


			cout << "Grid after adding valid row:" << endl;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (sudoku_grid[i][j] != NULL) {
						cout << sudoku_grid[i][j] << " ";
					}
				}
				cout << endl;
			}

			// increment row
			row++;

			// if row is last row grid_complete = true
			if (row == 9) {
				grid_complete = true;
			}
			else {
				//continue
				continue;
			}
			
		}
		else { // if not valid
			continue;
		}
		
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sudoku_grid[i][j] << " ";
		}
		cout << endl;
	}

}



int* Sudoku::meticAdd(int sudoku_grid[9][9], int row) {
	
	int arr[9] = {1,2,3,4,5,6,7,8,9};
	int agg_arr[9] = { 1,2,3,4,5,6,7,8,9 };
	int append_arr [9];


	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < 9; k++) {
				
				if (sudoku_grid[j][i] == agg_arr[k]) {
					agg_arr[k] = 0;
					break;
				}
			}
		}

		for (int q = 0; q < 9; q++) {
			if (agg_arr[q] != 0) {
				append_arr[i] = agg_arr[q]; // choose non zero value
				arr[q] = 0; // mark array of used values
				break;
			}
		}

		// reset agg but mark 0s in the spots arr have marked.
		for (int q = 0; q < 9; q++) {
			if (arr[q] == 0) {
				agg_arr[q] = 0;
			}
			else {
				agg_arr[q] = q + 1;
			}
		}

	}

	int* pointerArr = new int[9];

	for (int i = 0; i < 9; i++) {
		pointerArr[i] = append_arr[i];
	}

	return pointerArr;

}

bool Sudoku::crossExamine(int arr[9], int sudoku_grid[9][9], int row) {
	// validate - cross examine current random generation vs each row (row 0 to last completed row)
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 9; j++) {
			if (arr[j] == sudoku_grid[i][j]) {
				// there is a column that already has the number. regenerate.
				return false;
			}
		}
	}

	/*
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sudoku_grid[i][j] << " ";
		}
		cout << endl;
	}*/

	return true;
}

int * Sudoku::shuffle() {
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
	}

	int* pointerArr = new int[9];

	for (int i = 0; i < 9; i++) {
		pointerArr[i] = arr[i];
	}

	return pointerArr;
}