/*By::Cebastian Santiago 
* Leetcode 37
*/
#include<iostream>
#include<vector>
#include<map>
#include<utility>


bool helper(std::vector<std::pair<int,char>> up, std::vector<std::vector<char>>& board,int row , int column) {
	for (auto& i : up){
		if (i.first == column && i.second == board[row][column]) {
			return false;
		}
	}
	return true;
}


bool isValidSudoku(std::vector<std::vector<char>>& board) {
	//variables 
	std::map<char, int> row;
	std::map<char, int> column;
	std::map<char, int> gridone;
	std::map<char, int> gridtwo;
	std::map<char, int> gridthree;
	std::vector<std::pair<int, char>> up;


	//check for the rows
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			if (board[i][j] != '.') {
				if (!up.empty() && !helper(up, board, i, j)) {
					return false;
				}
				
			     up.push_back(std::make_pair(j, board[i][j]));
				
			}
		}
	}



	//loop through the board
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			//check for board that is filled with a number
			if (isalnum(board[i][j])) {
				//2. keep track of the numbers in the column section
				//check if we've seen this value in the columns
				//if not add two the map if we've seen it return false
				//broke one of the rules
				if (column.find(board[i][j]) == column.end()) {
					column.insert({ board[i][j],1 });
				}

				else{
					return false;
				}
			}
		}
		column.clear();
	}


	//3. check every 3x3 subgrid
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			//clear grid one
			if (i == 2 && j > 2 || i == 5 && j > 2 || i == 8 && j > 2){
				gridone.clear();
			}

			//clear grid two 
			if (i == 2 && j > 5 || i == 5 && j > 5 || i == 8 && j >5){
				gridtwo.clear();
			}

			//only care about the numbers
			if (isalnum(board[i][j])){
				//check the first grid
				if (j <= 2){
					//if we havent seen this value go 
					//ahead and insert it
					if (gridone.find(board[i][j]) == gridone.end()) {
						gridone.insert({ board[i][j] ,1 });
					}
					//if we seen this  it brakes the sudoku and return false
					else {
						return false;
					}
				}

				else if (j > 2 && j <= 5) {
					//if we havent seen this value go 
					//ahead and insert it
					if (gridtwo.find(board[i][j]) == gridtwo.end()) {
						gridtwo.insert({ board[i][j] ,1 });
					}
					//if we seen this  it brakes the sudoku and return false
					else {
						return false;
					}
				}

				else if (j >= 6 && j <= 8) {
					//if we havent seen this value go 
					//ahead and insert it
					if (gridthree.find(board[i][j]) == gridthree.end()) {
						gridthree.insert({ board[i][j] ,1 });
					}
					//if we seen this  it brakes the sudoku and return false
					else {
						return false;
					}
				}

			}

			//clear grid three
			if (i == 2 && j == 8 || i == 5 && j == 8 || i == 8 && j == 8) {
				gridthree.clear();
			}


		}
	}
	return true;
}





int main() {
	std::vector<std::vector<char>> board = { {'.','.','.','.','.','.','.','.','.'},
											 {'.','.','.','.','.','.','3','.','.'},
											 {'.','.','.','1','8','.','.','.','.'},
											 {'.','.','.','7','.','.','.','.','.'},
											 {'.','.','.','.','1','.','9','7','.'},
											 {'.','.','.','.','.','.','.','.','.'},
											 {'.','.','.','3','6','.','1','.','.'},
											 {'.','.','.','.','.','.','.','.','.'},
											 {'.','.','.','.','.','.','.','2','.'},
	};



	std::cout << isValidSudoku(board) << std::endl;
	return 0;
}