#include <iostream>
#include "Hungarian.h"


int main(void)
{
    // please use "-std=c++11" for this initialization of vector.
	vector< vector<double> > costMatrix(5, vector<double>(5, 0));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			costMatrix[i][j] = i + j;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin>>costMatrix[i][j];
		}
	}
	HungarianAlgorithm HungAlgo;
	vector<int> assignment;

	double cost = HungAlgo.Solve(costMatrix, assignment);

	for (unsigned int x = 0; x < costMatrix.size(); x++)
		std::cout << x << "," << assignment[x] << "\t";

	std::cout << "\ncost: " << cost << std::endl;

	return 0;
}
