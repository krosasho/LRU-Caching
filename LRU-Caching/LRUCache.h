#pragma once
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
public:
	LRUCache(int size); // Parameterized constructor
	void printCache();
	void reference(int newEntry);

private:
	unordered_map<int, list<int>::iterator> cacheMap; // This is to be able to quickly keep track of what is and is not in our cache
	list<int> cacheQueue; // This will maintain the order of elements in our cache
	int cacheSize; // This is the first command line parameter
};