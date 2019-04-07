#include "LRUCache.h"

LRUCache::LRUCache(int size)
{
	cacheSize = size;
}

void LRUCache::reference(int newEntry)
{
	cacheRequest++;
	if (cacheMap.find(newEntry) == cacheMap.end()) // If true, new entry is not in cache
	{
		if (cacheQueue.size() == cacheSize) // If true, our cache is full, and space must be made for new entry.
		{
			int leastRecentlyUsed = cacheQueue.back();
			cacheQueue.pop_back();
			cacheMap.erase(leastRecentlyUsed);
		}
	}
	else // Else, new entry is already in cache somewhere
	{
		cacheHit++;
		cacheQueue.erase(cacheMap[newEntry]);
	}

	// Update cache and queue accordingly with this new entry
	cacheQueue.push_front(newEntry);
	cacheMap[newEntry] = cacheQueue.begin();
}