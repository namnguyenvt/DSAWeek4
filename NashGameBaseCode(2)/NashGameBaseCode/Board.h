/*
 * BaseBoard.h
 *
 *  Created on: 1/03/2025
 *      Author: dongmo
 */
#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

struct Cell {
public:
  	int x;
  	int y;
	Cell(int x, int y) : x(x), y(y) {}
};

class Board {
private:
	int boardSize;
	int turn;
	int **grid;
public:
	Board(int bs) {
		boardSize = bs;
		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = 0;
			}
		turn = 1;
	}

	virtual ~Board() {

		for (int i = 0; i < boardSize; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(Board &cboard) {
		boardSize = cboard.getBoardSize();

		grid = new int*[boardSize];
		for (int i = 0; i < boardSize; i++)
			grid[i] = new int[boardSize];

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				grid[i][j] = 0;

		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				grid[i][j] = cboard.getGrid(i, j);
			}

		turn = cboard.getTurn();
	}

	int getBoardSize() {
		return boardSize;
	}

	int getGrid(int x, int y) {
		return grid[x][y];
	}

	int getTurn() {
		return turn;
	}

	bool validInput(int, int);

    stack<int> checkNeighbours(int player, int x, int y);

	bool isBoardFull();

	void getRandomMove(int &row, int &col);

	bool addMove(int playerType, int x, int y);

    // Task 2.3
    int getIndex(int x, int y) const;

    int getRow(int index) const;

    int getCol(int index) const;
	//

    void setCell(int x, int y, int player);

	int checkWinningStatus(int playerType) {
		//To be implemented
		return 0;
	}

	void printBoard();
};

void Board::setCell(int x, int y, int player) {
	grid[x][y] = player;
}

// Task 2.3
int Board::getIndex(int x, int y) const {
	return x * boardSize + y;
}

int Board::getRow(int index) const {
	return index / boardSize;
}

int Board::getCol(int index) const {
	return index % boardSize;
}
//

// Task 3.3
stack<int> Board::checkNeighbours(int player, int x, int y) {
	stack<int> neighbours;

	// Hexagonal neighbors (down-left, down-right, left, right, up-left, up-right)
	int dx[] = {1, 1, 0, 0, -1, -1};
	int dy[] = {-1, 0, -1, 1, 0, 1};

	for (int i = 0; i < 6; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize && grid[nx][ny] == player) {
			int index = nx * boardSize + ny;  // Convert (x, y) to 1D index
			neighbours.push(index);
		}
	}

  	return neighbours;
}

// Overloaded function to return stack<Cell> instead
vector<Cell> checkNeighboursCells(int player, int x, int y) {
	vector<Cell> neighbors;

	int dx[] = {1, 1, 0, 0, -1, -1};
	int dy[] = {-1, 0, -1, 1, 0, 1};

	for (int i = 0; i < 6; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx >= 0 && nx < boardSize && ny >= 0 && ny < boardSize && grid[nx][ny] == player) {
			neighbors.push_back(Cell(nx, ny));
		}
	}

	return neighbors;
}

// Task 3.1
// void Board::getRandomMove(int &row, int &col) {
// 	do {
// 		row = rand() % boardSize;
// 		col = rand() % boardSize;
// 	} while (!validInput(row, col)); //This condition to check the loop will work until the empty cell is found
// }

// Task 3.2
void Board::getRandomMove(int &row, int &col) {
	if (grid[row][col] == 0) {
		row = rand() % boardSize;
		col = rand() % boardSize;
	}
}

bool Board::isBoardFull() {
	int sumOfCells = boardSize * boardSize;
	for (int row = 0; row < boardSize; row++) {
		for (int col = 0; col < boardSize; col++) {
			if (grid[row][col] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool Board::validInput(int x, int y) {
	if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
		cout << "Move (" << x + 1 << ", " << y + 1 << ") out of range!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	return true;
}

bool Board::addMove(int playerType, int x, int y) {

	if (playerType != turn) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (grid[x][y] != 0) {
		cout << "Invalid move. The cell has been occupied." << endl;
		return false;
	}

	grid[x][y] = playerType;

	turn = -1 * turn;
	return true;
}

void Board::printBoard() {
	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		if (j < 9)
			cout << j + 1 << "   ";
		else
			cout << j + 1 << "  ";
	}
	cout << endl;

	cout << "   ";
	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}
	cout << endl;

	for (int i = 0; i < boardSize; i++) {
		for (int k = 0; k < i; k++)
			cout << "  ";

		if (i < 9)
			cout << " " << i + 1 << " ";
		else
			cout << i + 1 << " ";

		for (int j = 0; j < boardSize; j++) {
			if (grid[i][j] == 0) {
				if (j == 0) {
					cout << "|   |";
				} else {
					cout << "   |";
				}
			} else if (grid[i][j] == 1) {
				if (j == 0) {
					cout << "| B |";
				} else {
					cout << " B |";
				}
			} else {
				if (j == 0) {
					cout << "| W |";
				} else {
					cout << " W |";
				}
			}
		}
		cout << endl;
	}

	for (int k = 0; k <= boardSize; k++)
		cout << "  ";

	for (int j = 0; j < boardSize; j++) {
		cout << "----";
	}

	cout << endl;
	cout << endl;
}

#endif /* BOARD_H_ */
