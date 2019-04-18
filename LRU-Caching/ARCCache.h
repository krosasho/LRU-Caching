#pragma once
#include <list>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

class ARCCache
{
public:
	ARCCache(int size);
	void ARCreference(int newEntry);
	void getHitRatio();
	void REPLACE(int newEntry);

private:
	int p = 0;

	unordered_map<int, list<int>::iterator> B1map;
	list<int> B1queue;

	unordered_map<int, list<int>::iterator> B2map;
	list<int> B2queue;

	unordered_map<int, list<int>::iterator> T1map;
	list<int> T1queue;

	unordered_map<int, list<int>::iterator> T2map;
	list<int> T2queue;

	int currentSize = 0; // |T1| + |T2|. Manually updated whenever something is added to cache. Ensure it does not exceed maxSize.
	int maxSize; // This is the first command line parameter
	double cacheHit; // This will be incremented whenever we reference something that is available in cache
	double cacheRequest; // This will be incremented whenever anything is referenced
};

