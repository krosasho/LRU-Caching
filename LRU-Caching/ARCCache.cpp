#include "ARCCache.h"



ARCCache::ARCCache(int size) 
{
	maxSize = size;
}

void ARCCache::getHitRatio()
{
	if (cacheRequest != 0)
	{
		double hitRatio = cacheHit / cacheRequest * 100;
		cout << hitRatio << endl;
	}
	else
	{
		cout << "Cache is empty" << endl;
	}

}

void ARCCache::ARCreference(int newEntry)
{
	cacheRequest++;
	/* Case 1: x_t is in T1 or T2. A cache hit has occured: */
	if (T1map.find(newEntry) != T1map.end() || T2map.find(newEntry) != T1map.end())
	{
		// DEBUGGING
		cout << "Cache hit on " << newEntry << endl;
		// END DEBUGGING
		cacheHit++;
		if (T1map.find(newEntry) != T1map.end()) // x_t is in T1
		{
			T1queue.erase(T1map[newEntry]); // Erase x_t from T1
			T1map.erase(newEntry);
		}
		else // x_t is in T2
		{
			T2queue.erase(T2map[newEntry]); // Erase x_t from its current position in T2
			T2map.erase(newEntry);
		}
		T2queue.push_front(newEntry); // Add x_t to MRU position in T2
		T2map[newEntry] = T2queue.begin();
		currentSize++;
	}
	/* Case 2: x_t is in B1. A cache miss has occured */
	else if (B1map.find(newEntry) != B1map.end())
	{
		// ADAPTATION
		int delta;
		if (B1queue.size() >= B2queue.size())
		{
			delta = 1;
		}
		else
		{
			delta = B2queue.size() / B1queue.size();
		}
		p = min((p + delta), maxSize);
		REPLACE(newEntry);

		// Move xt from B1 to the MRU position in T2 (also fetch xt to the cache)
		B1queue.erase(B2map[newEntry]);
		B1map.erase(newEntry);
		T2queue.push_front(newEntry);
		T2map[newEntry] = T2queue.begin();
		currentSize++;
	}
	/* Case 3: x_t is in B2. A cache miss has occurred. */
	else if (B2map.find(newEntry) != B2map.end())
	{
		// ADAPTATION
		int delta;
		if (B2queue.size() >= B1queue.size())
		{
			delta = 1;
		}
		else
		{
			delta = B1queue.size() / B2queue.size();
		}
		p = max(p - delta, 0);
		REPLACE(newEntry);

		// Move x_t from B2 to the MRU position in T2
		B2queue.erase(B2map[newEntry]);
		B2map.erase(newEntry);
		T2queue.push_front(newEntry);
		T2map[newEntry] = T2queue.begin();
		currentSize++;
	}
	/* Case 4: x_t is not in T1, B2, T2, or B2. A Cache miss has occurred */
	else
	{
		/* Case A: L1 = T1 <Union> B1 has exactly c pages */
		if ((T1queue.size() + B1queue.size()) == maxSize)
		{
			if (T1queue.size() < maxSize)
			{
				// Delete LRU page in B1
				int b1LRU = B1queue.back();
				B1queue.pop_back();
				B1map.erase(b1LRU);
				REPLACE(newEntry);
			}
			else
			{
				/* Here, B1 is empty. Delete LRU page in T1 (also remove it from the cache) */
				int t1LRU = T1queue.back();
				T1queue.pop_back();
				T1map.erase(t1LRU);
				currentSize--;
			}


		}
		/* Case B: L1 = T1 <Union> B1 has less than c pages */
		else if ((T1queue.size() + B1queue.size()) < maxSize)
		{
			if ((T1queue.size() + T2queue.size() + B1queue.size() + B2queue.size()) >= maxSize)
			{
				// Delete LRU page in B2, if (T1 + T2 + B1 + B2 = 2c)
				if ((T1queue.size() + T2queue.size() + B1queue.size() + B2queue.size()) == maxSize)
				{
					int b2LRU = B2queue.back();
					B2queue.pop_back();
					B2map.erase(b2LRU);
				}
				REPLACE(newEntry);
			}
		}
		// Finally, fetch x_t to the cache and move it to MRU position in T1
		T1queue.push_front(newEntry);
		T1map[newEntry] = T1queue.begin();
		currentSize++;
	}
}

void ARCCache::REPLACE(int newEntry)
{
	if ((T1queue.size() != 0) && ((T1queue.size() > p) || (B2map.find(newEntry) != B2map.end() && T1queue.size() == p)))
	{
		int t1LRU = T1queue.back();

		// Delete the LRU page in T1 (also remove it from the cache)
		T1queue.pop_back();
		T1map.erase(t1LRU);
		currentSize--;

		// and move it to the MRU position in B1.
		B1queue.push_front(t1LRU);
		B1map[t1LRU] = B1queue.begin();
	}
	else
	{
		int t2LRU = T2queue.back();

		// Delete the LRU page in T2 (also remove it from the cache)
		T2queue.pop_back();
		T1map.erase(t2LRU);
		currentSize--;

		// Move it to the MRU position in B2
		B2queue.push_front(t2LRU);
		B2map[t2LRU] = B2queue.begin();
	}
}