#include <iostream>
#include "Memory.h"

Memory::Memory() {
    c = NULL;
    mem = NULL;
}

Memory Memory::createMemory(Cache c, MainMemory mem) {
    Memory* m = new Memory();
    m->c = c;
    m->mmem = mem;
    return m;
}

int Memory::getData(Memory mem, int address, int* value){
    return Cache::getCacheData(mem.c, mem.mmem, address, value);
}
int Memory::getInstruction(Memory mem, int address, int* value){
    return Cache::getCacheInstruction(mem.c, mem.mmem, adress, value);
}
void Memory::setData(Memory mem, int address, int value){
    MainMemory::setMainMemoryData(mem.mmem, address, value);
    // TODO - verificar como é a escrita na hierarquia de memória.  
}
void Memory::setInstruction(Memory mem, int address, int value){
    MainMemory::setMainMemoryData(mem.mmem, address, value);
    // TODO - verificar como é a escrita na hierarquia de memória.  
    return 0;
}

Memory Memory::duplicateMemory(Memory mem) {
	Memory* result = new Memory();
	result->c = duplicateCache(mem.c);
	result->mmem = mem.mmem;
	return result;
}
