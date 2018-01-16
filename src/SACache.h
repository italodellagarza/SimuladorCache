#ifndef SACACHE_H
#define SACACHE_H 1

class SACache {
private:
	SACache();
public:
	static SACache createSACache(int c, int a, int l);
	static int getSACacheCapacity(SACache sac);
	static int getSACacheLineSize(SACache sac);
	static bool getSACacheData(SACache sac, int address, int * value);
	static void setSACacheData(SACache sac, int address, int value);
	static SACache duplicateSACache(SACache sac);
	~SACache();
	
};

#endif // SACACHE_H