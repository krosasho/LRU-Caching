// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <string>
#include <fstream>
#include "LRUCache.h"
#include "ARCCache.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid command line parameters. Should be of form:";
		cout << "./<lru || arc> <c, the cache size in number of pages> <TraceName (excluding .lis extension)>" << endl;
		exit(1);
	}
	string fileName = argv[0];
	int cacheSize = atoi(argv[1]);
	string trace = argv[2];
	string traceName = trace + ".lis";

	ifstream myFile(traceName);

	if (fileName == "lru")
	{
		LRUCache myCache(cacheSize);

		if (myFile.good())
		{
			int startingBlock, numOfBlocks, ignore, ignore2;
			while (myFile >> startingBlock)
			{
				myFile >> numOfBlocks; myFile >> ignore; myFile >> ignore2;
				//cout << startingBlock << " " << numOfBlocks << " " << ignore << " " << ignore2 << endl; // DEBUGGING
				for (int i = 0; i < numOfBlocks; i++)
				{
					myCache.reference(startingBlock + i);
				}
			}

			myCache.getHitRatio();
		}
		else
		{
			cout << "Failed to open file " << traceName << endl;
		}
	}
	else if (fileName == "arc")
	{
		ARCCache myCache(cacheSize);

		if (myFile.good())
		{
			int startingBlock, numOfBlocks, ignore, ignore2;
			while (myFile >> startingBlock)
			{
				myFile >> numOfBlocks; myFile >> ignore; myFile >> ignore2;
				for (int i = 0; i < numOfBlocks; i++)
				{
					myCache.ARCreference(startingBlock + i);
				}
			}
			myCache.getHitRatio();
		}
		else
		{
			cout << "Failed to open file " << traceName << endl;
		}
	}
	else
	{
		cout << "Error: Program must be named 'lru' or 'arc'." << endl;
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
