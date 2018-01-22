#ifndef TACACHE_H
#define TACACHE_H 1


class TACache {
private:
    int** matrixBytes;
    int tACacheCapacity;
    int tACacheLineSize;
	TACache();
public:
	static TACache createTACache(int c, int l);
	static int getTACacheCapacity(TACache tac);
	static int getTACacheLineSize(TACache tac);
	static bool getTACacheData(TACache tac, int address, int * value);
	static void setTACacheData(TACache tac, int address, int value);
	~TACache();
	
};

#endif // TACACHE_H
