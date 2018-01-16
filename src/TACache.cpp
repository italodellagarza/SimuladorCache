#include "TACache.h"

class TACache {
private:
	TACache();
public:
	static TACache createTACache(int c, int l);
	static int getTACacheCapacity(TACache tac);
	static int getTACacheLineSize(TACache tac);
	static bool getTACacheData(TACache tac, int adress, int * value);
	static void setTACacheData(TACache tac, int adress, int value);
	~TACache();
	
};