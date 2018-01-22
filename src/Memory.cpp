#include <iostream>
#include "Memory.h"

Memory::Memory() {
    c = NULL;
    mem = NULL;
}

Memory Memory::createMemory(Cache c, MainMemory mem) {
	Memory m = new Memory();
	m->c = c;
    m->mem = mem;
}

int Memory::getData(Memory mem){
	// TODO
	return 0;
}
int Memory::getInstruction(Memory mem, int address, int* value){
	// TODO
	return 0;
}
int Memory::setData(Memory mem, int address, int value){
	// TODO
	return 0;	
}
int Memory::setInstruction(Memory mem, int address, int value){
	// TODO
	return 0;
}
