

// Задача 1а. Дадена е квадратна двумерна матрица с размерност n2 x n2. Да се провери дали тя е решение на задача Судоку.
// Ако разбирам правилно, това означава, че за всички полета от судоку се предоставят. Задачата е да се провери дали
// предоставена та матрица е решение на судоку. Т.е. матрицата отговаря на изискванията за неповторение на числата в редовете, колоните и квадратите.
// Входни данни: На първия ред се въвежда едно цяло число n (1 ≤ n ≤ 10), което определя размерността на квадратната матрица.
// След това се въвеждат n2 реда, всеки от които съдържа n2 цели числа, разделени с интервал, които представляват елементите на матрицата.

#include <iostream>
#include <vector>
#include <map>

class Sudoku{
	int n;
	int size;
	std::vector<std::vector<int>> sudoku;

public:
	Sudoku(int& n) {
		this->n = n;
		size = n * n;
		sudoku = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
		std::cout << "Enter the Sudoku matrix (n^2 x n^2):" << std::endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++) {
				std::cin >> sudoku[i][j];
				if (sudoku[i][j] < 1 || sudoku[i][j] > size) {
					std::cout << "Invalid input. Numbers must be between 1 and " << size << "." << std::endl;
					break;
				}
			}
		}
	}

	// валидира цялото судоку
	bool isValid(){
	    // check rows
	    for(int i = 0; i < size; i++){
            if(!checkRow(i))
                return false;
	    }

	    // check columns
	    for(int i = 0; i < size; i++){
            if(!checkColumn(i))
                return false;
	    }

	    // check boxes
	    for(int i = 0; i < size; i += n){
            for(int j = 0; j < size; j += n){
                if(!checkBox(i, j)) return false;
            }
	    }

        return true;
	}

	// проверява ред за това дали има повторения на числа
	bool checkRow(int row){
        std::map<int, int> element;

		for (int i = 0; i < size; i++) {
			if (element.find(sudoku[row][i]) != element.end())
				element[sudoku[row][i]] += 1;
			else
				element[sudoku[row][i]] = 1;

			if (element[sudoku[row][i]] > 1) return false;
		}

        if(element.size() != size)
            return false;

        return true;
    }

	// проверява колона за това дали има повторения на числа
	bool checkColumn(int col) {
		std::map<int, int> element;

		for (int i = 0; i < size; i++) {
			if (element.find(sudoku[i][col]) != element.end())
				element[sudoku[i][col]] += 1;
			else
				element[sudoku[i][col]] = 1;

			if (element[sudoku[i][col]] > 1) return false;
		}

		if (element.size() != size)
			return false;
		return true;
	}

	// проверява 3х3 кутия за това дали има повторения на числа
	bool checkBox(int x, int y){
		std::map<int, int> element;

		for (int i = x; i < x + n; i++) {
            for(int j = y; j < y + n; j++){
                if (element.find(sudoku[i][j]) != element.end())
                    element[sudoku[i][j]] += 1;
                else
                    element[sudoku[i][j]] = 1;

                if (element[sudoku[i][j]] > 1) return false;
            }
		}

		if (element.size() != size)
			return false;
		return true;
	}

};

int main() {
	int n = 0;

	std::cout << "Enter the size of the Sudoku (n): ";
	std::cin >> n;

	if(std::cin.fail() || n <= 0){
		std::cout << "Invalid input. n must be greater than 0." << std::endl;
		return 1;
	}

	Sudoku sudoku(n);

    std::cout << (sudoku.isValid() ? "Sudoku is valid." : "Sudoku not valid!");
}
