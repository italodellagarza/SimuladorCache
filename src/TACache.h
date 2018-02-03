#ifndef TACACHE_H
#define TACACHE_H 1

typedef char byte;

class TACache {
private:
	int* lineTaggs;
	int nLines;
	int linesOccupied;
	int indexSize;
    int** matrixBytes;
    int tACacheCapacity;
    int tACacheLineSize;
	TACache();
public:
	static TACache createTACache(int c, int l);
	static int getTACacheCapacity(TACache tac);
	static int getTACacheLineSize(TACache tac);
	static bool getTACacheData(TACache tac, int address, int * value);
	static void setTACacheData(TACache& tac, int address, int value);
	~TACache();
	
};

#endif // TACACHE_H
