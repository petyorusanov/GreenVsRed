#include "GridController.h"


GridController::GridController() : myGrid(), initState()
{
	x = 0;
	y = 0;
	x1 = 0;
	y1 = 0;
	N = 0;
	numberOfGreens = 0;
}

GridController::~GridController()
{

}

void GridController::userInput()
{
	do {
		cout << "Please input the width of the grid(should be an integer in the range [1, 999]): ";
		cin >> x;
	} while (x < 1 || x > 999);

	do {
		cout << "Please input the heigth of grid(should be an integer  in the range [" << x << ", 999]: ";
		cin >> y;
	} while (y < x || y > 999);

	initState.resize(y);
	cout << "Please input initial state of the grid:" << endl;
	for (int i = 0; i < y; i++)
	{
		cin >> initState[i];
		while (initState[i].size() != x)
		{
			cout << "Wrong input! The length of the string should be " << x << ". Please input the row again: " << endl;
			cin >> initState[i];
		}
	}

	do {
		cout << "Please input the x-coordinate of the target cell(should be an integer in the range [0, " << x - 1 << "]):";
		cin >> x1;
	} while (x1 < 0 || x1 >= x);

	do {
		cout << "Please input the y-coordinate of the target cell(should be an integer in the range [0, " << y - 1 << "]):";
		cin >> y1;
	} while (y1 < 0 || y1 >= y);

	do {
		cout << "Please input the desired number of generations(should be an integer greater than or equal to 0): ";
		cin >> N;
	} while (N < 0);
}

void GridController::gridInit()
{
	//build a grid with y rows and x columns
	myGrid.buildGrid(y, x);

	//initializes the grid with the user's initial state input
	myGrid.init(initState);
}

void GridController::updateGrid()
{
	//checks the value of the target cell in generation zero
	numberOfGreens = (myGrid.getValueOf(y1, x1) == 1) ? 1 : 0;
	//go through N generations and counts in how many generations the target cell has been green
	for (int i = 1; i <= N; i++) {
		myGrid.nextGeneration();
		numberOfGreens += myGrid.getValueOf(y1, x1);
	}
}

int GridController::getNumberOfGreens()
{
	return numberOfGreens;
}
