#include "TACache.h"

#ifndef SACACHE_H
#define SACACHE_H 1

using namespace std;

class SACache {
friend class TACache;
private:
    SACache();
    TACache tac;
public:
	static SACache createSACache(int c, int a, int l);
	static int getSACacheCapacity(SACache sac);
	static int getSACacheLineSize(SACache sac);
	static bool getSACacheData(SACache sac, int address, int * value);
	static void setSACacheData(SACache &sac, int address, int value);
	static void setSACacheLine(SACache &sac, int address, int *line);
	static SACache duplicateSACache(SACache sac);
};

#endif // SACACHE_H
