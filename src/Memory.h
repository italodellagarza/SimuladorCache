#ifndef MEMORY_H
#define MEMORY_H 1

#include "MainMemory.h"
#include "Cache.h"

class Memory {
private:
	Memory();
public:
	static Memory createMemory(Cache c, MainMemory mem);
	static int getData(Memory mem);
	static int getInstruction(Memory mem, int address, int* value);
	static int setData(Memory mem, int address, int value);
	static int setInstruction(Memory mem, int address, int value);
	~Memory();
	
};

#endif //MEMORY_H