#ifndef MEMORY_H
#define MEMORY_H 1

#include "MainMemory.h"
#include "Cache.h"

class Memory {
private:
	Memory();
    MainMemory mmem;
    Cache c;
public:
	static Memory createMemory(Cache c, MainMemory mem);
	static int getData(Memory mem);
	static int getInstruction(Memory mem, int address, int* value);
	static void setData(Memory mem, int address, int value);
	static void setInstruction(Memory mem, int address, int value);
	static Memory duplicateMemory(Memory mem);
	~Memory();
	
};

#endif //MEMORY_H
