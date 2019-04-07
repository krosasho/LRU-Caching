#pragma once
#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

class LRUCache
{
public:
	LRUCache(int size); // Parameterized constructor
	void printCache();
	void reference(int newEntry);
	void getHitRatio();

private:
	unordered_map<int, list<int>::iterator> cacheMap; // This is to be able to quickly keep track of what is and is not in our cache
	list<int> cacheQueue; // This will maintain the order of elements in our cache
	int cacheSize; // This is the first command line parameter
	double cacheHit; // This will be incremented whenever we reference something that is available in cache
	double cacheRequest; // This will be incremented whenever anything is referenced
};