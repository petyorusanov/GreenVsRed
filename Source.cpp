#include<iostream>
#include "GridController.h"
using namespace std;



int main()
{
	GridController active;
	active.userInput();
	active.gridInit();
	active.updateGrid();
	cout << active.getNumberOfGreens() << endl;

	system("pause");
	return 0;
}