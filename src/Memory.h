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
    public:
        Memory();
        static Memory createMemory(Cache c, MainMemory mem);
        static int getData(Memory mem, int address, int * value);
        static int getInstruction(Memory mem, int address, int * value);
        static void setData(Memory &mem, int address, int value);
        static void setInstruction(Memory &mem, int address, int value);
        static Memory duplicateMemory(Memory mem);
};

#endif
