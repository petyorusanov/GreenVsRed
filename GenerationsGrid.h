#pragma once
#include<string>
#include<vector>
#include<queue>
using namespace std;

class GenerationsGrid
{
private:
	int** mainGrid;
	int rows;
	int columns;

	//a queue of integers to store which cells' value 
	//has to be changed in the current generation
	//after the change the queue is empty
	queue<int> cellsToBeUpdated;

	//auxiliary function for the destructor
	void clear();

	//auxiliary function for nextGeneration() 
	//counts surrounding greens of a cell
	int countSurroundingGreens(int, int);

	//auxiliary function for nextGeneration() 
	//update the look of the grid(getting to next generation) 
	//happens at once using the cellsToBeUpdated queue
	void changeValues();
public:
	GenerationsGrid();
	~GenerationsGrid();
	//builds the grid
	void buildGrid(int, int);
	//initializes the grid with the user's initial state input
	void init(vector<string>);

	//get the value of a cell
	int getValueOf(int, int);

	//main function of the class
	//go from one generation to the next
	void nextGeneration();
};
