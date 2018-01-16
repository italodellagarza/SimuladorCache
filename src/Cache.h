#ifndef CACHE_H
#define CACHE_H 1

#include "SACache.h"

class Cache {
private:
	Cache();
public:
	static Cache createCache(SACache lld, SACache lli, SACache l2, SACache l3);
	static int getCacheData(Cache c, int address, int * value);
	static int getCacheInstruction(Cache c, int address, int * value);
	static void setCacheData(Cache sac, int address, int value);
	static void setCacheInstruction(Cache sac, int address, int value);
	static Cache duplicateCache(Cache c);
	~Cache();
	
};

#endif // CACHE_H