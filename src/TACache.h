#ifndef TACACHE_H
#define TACACHE_H 1
//#include "SACache.h"
typedef char byte;

class TACache {
friend class SACache;
private:
	int* lineTaggs;
	int nLines;
	int a;		// Associatividade a ser usada no SACache (em TACache é 1)
	int linesOccupied;
	int tagSize;
    int** matrixBytes;
    int tACacheCapacity;
    int tACacheLineSize;
	TACache();
public:
	static TACache createTACache(int c, int l);
	static int getTACacheCapacity(TACache tac);
	static int getTACacheLineSize(TACache tac);
	static bool getTACacheData(TACache tac, int address, int * value);
	static bool setTACacheData(TACache& tac, int address, int value);
	static void setTACacheLine(TACache& tac, int address, int *line);
	//char []  toString();
	~TACache();
	
};

#endif // TACACHE_H
