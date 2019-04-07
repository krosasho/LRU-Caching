// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <string>
#include <iostream>
#include <fstream>
#include "LRUCache.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid command line parameters. Should be of form:";
		cout << "./<lru || arc> <c, the cache size in number of pages> <TraceName (excluding .lis extension)>" << endl;
		exit(1);
	}

	int cacheSize = atoi(argv[1]);
	string trace = argv[2];
	string traceName = trace + ".lis";

	ifstream myFile(traceName);

	if (myFile.good())
	{
		int startingBlock, numOfBlocks, ignore, ignore2;
		while (myFile >> startingBlock)
		{
			myFile >> numOfBlocks; myFile >> ignore; myFile >> ignore2;
			cout << startingBlock << " " << numOfBlocks << " " << ignore << " " << ignore2 << endl; // DEBUGGING
		}
	}
	else
	{
		cout << "Failed to open file " << traceName << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
