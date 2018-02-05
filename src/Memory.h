#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include "MainMemory.h"
#include "Cache.h"

using namespace std;

class Memory{
    private:
        Cache c;
        MainMemory mMemory;
    private:
        Memory createMemory(Cache c, MainMemory mem);
        int getData(Memory mem, int address, int * value);
        int getInstruction(Memory mem, int address, int * value);
        int setData(Memory &mem, int address, int value);
        int setInstruction(Memory &mem, int address, int value);
        Memory duplicateMemory(Memory mem);
};

#endif
