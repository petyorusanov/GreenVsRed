#include "GenerationsGrid.h"


GenerationsGrid::GenerationsGrid() : mainGrid(nullptr), cellsToBeUpdated()
{
	rows = 0;
	columns = 0;
}

GenerationsGrid::~GenerationsGrid()
{
	clear();
}

void GenerationsGrid::clear()
{
	for (int i = 0; i < rows; i++) {
		delete[] mainGrid[i];
	}
	delete[] mainGrid;
}

int GenerationsGrid::countSurroundingGreens(int i, int j)
{
	int count = 0;
	if (i > 0 && i < rows - 1 && j > 0 && j < columns - 1) {
		//inside the borders
		count = mainGrid[i - 1][j - 1] + mainGrid[i - 1][j] + mainGrid[i - 1][j + 1] + mainGrid[i][j + 1] + mainGrid[i + 1][j + 1] + mainGrid[i + 1][j] + mainGrid[i + 1][j - 1] + mainGrid[i][j - 1];
	}
	else if (i == 0) {
		if (j > 0 && j < columns - 1) {
			//top border
			count = mainGrid[i][j + 1] + mainGrid[i + 1][j + 1] + mainGrid[i + 1][j] + mainGrid[i + 1][j - 1] + mainGrid[i][j - 1];
		}
		else if (j == 0) {
			//[0][0]
			count = mainGrid[i][j + 1] + mainGrid[i + 1][j + 1] + mainGrid[i + 1][j];
		}
		else if (j == columns - 1) {
			//[0][columns - 1]
			count = mainGrid[i][j - 1] + mainGrid[i + 1][j - 1] + mainGrid[i + 1][j];
		}
	}
	else if (i == rows - 1) {
		if (j > 0 && j < columns - 1) {
			//bottom border
			count = mainGrid[i][j - 1] + mainGrid[i - 1][j - 1] + mainGrid[i - 1][j] + mainGrid[i - 1][j + 1] + mainGrid[i][j + 1];
		}
		else if (j == 0) {
			//[rows - 1][0]
			count = mainGrid[i - 1][j] + mainGrid[i - 1][j + 1] + mainGrid[i][j + 1];
		}
		else if (j == columns - 1) {
			//[rows - 1][columns - 1]
			count = mainGrid[i - 1][j] + mainGrid[i - 1][j - 1] + mainGrid[i][j - 1];
		}
	}
	else if (j == 0) {
		//left border
		count = mainGrid[i - 1][j] + mainGrid[i - 1][j + 1] + mainGrid[i][j + 1] + mainGrid[i + 1][j + 1] + mainGrid[i + 1][j];
	}
	else if (j == columns - 1) {
		//right border
		count = mainGrid[i + 1][j] + mainGrid[i + 1][j - 1] + mainGrid[i][j - 1] + mainGrid[i - 1][j - 1] + mainGrid[i - 1][j];
	}
	return count;
}

void GenerationsGrid::changeValues()
{
	while (!cellsToBeUpdated.empty()) {
		int key, i, j;
		key = cellsToBeUpdated.front();
		cellsToBeUpdated.pop();
		//decoding value to two integers representing position
		j = key % 10;
		key /= 10;
		i = key;

		//changing value of given cell in current generation
		mainGrid[i][j] = (mainGrid[i][j] == 0) ? 1 : 0;
	}
}

void GenerationsGrid::buildGrid(int y, int x) //y being the heigth and x being the width
{
	rows = y;
	columns = x;
	mainGrid = new int* [y];
	for (int i = 0; i < y; i++)
	{
		mainGrid[i] = new int[x];
	}
}

void GenerationsGrid::init(vector<string> initState)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mainGrid[i][j] = initState[i][j] - '0';
		}
	}
}

int GenerationsGrid::getValueOf(int i, int j)
{
	return mainGrid[i][j];
}

void GenerationsGrid::nextGeneration()
{
	int surroundingGreens = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			//stores the number of surrounding cells that are green
			surroundingGreens = countSurroundingGreens(i, j);
			//check if the cell is red, else it's green
			if (mainGrid[i][j] == 0) {
				if (surroundingGreens == 3 || surroundingGreens == 6) {
					//encoding position to a single integer
					//and stores it to change its value
					cellsToBeUpdated.push(i * 10 + j);
				}
			}
			else {
				//mainGrid[i][j] == 1
				if (surroundingGreens == 0 || surroundingGreens == 1 || surroundingGreens == 4 || surroundingGreens == 5 || surroundingGreens == 7 || surroundingGreens == 8) {
					//encoding position to a single integer
					//and stores it to change its value
					cellsToBeUpdated.push(i * 10 + j);
				}
			}
			surroundingGreens = 0;
		}
	}
	changeValues();
}
