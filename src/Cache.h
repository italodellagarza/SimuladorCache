#ifndef CACHE_H
#define CACHE_H 1

#include "SACache.h"

class Cache {
private:
	SACache l1d;
	SACache l1i;
	SACache l2;
	SACache* l3;
	Cache(SaCache l1d, SACache l1i, SACache l2, SACache* l3);
public:
	static Cache createCache(SACache l1d, SACache l1i, SACache l2, SACache l3);
	static int getCacheData(Cache &c, MainMemory mmem, int address, int * value);
	static int getCacheInstruction(Cache &c, MainMemory mmem, int address, int * value);
	static int setCacheData(Cache &c, mainMemory &mmem, int address, int value);
	static void setCacheInstruction(Cache &c, MainMemory mmem, int address, int value);
	static void fetchCacheData(Cache &c, MainMemory mmem, int adress);
	static void fetchCacheInstruction(Cache &c, MainMemory mmem, int adress);
	static Cache duplicateCache(Cache c);
	~Cache();
	
};

#endif // CACHE_H