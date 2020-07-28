#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "GenerationsGrid.h"
using namespace std;


class GridController
{
private:
	GenerationsGrid myGrid;
	//width of the grid
	int x;
	//heigth of the grid
	int y;
	//initial values of the cells in the grid
	vector<string> initState;
	//coordinates of the target cell(y1 being the x-coordinate and x1 being the y-coordinate)
	int x1, y1;
	//number of generations to be calculated
	int N;
	//stores the number of times the target cell has been green
	int numberOfGreens;


public:
	GridController();
	~GridController();

	//get parameters inputed by the user
	void userInput();
	//initializes the grid with the values of initState
	void gridInit();
	//updates the grid N times to get it to the desired generation while storing how many times the target cell has been green
	void updateGrid();
	//get the number of times that the target cell has been green
	int getNumberOfGreens();
};
