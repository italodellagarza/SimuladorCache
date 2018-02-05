#include <iostream>
#include <cstdlib>
#include "MainMemory.h"


/**
 * Métodos da classe MainMemory
 */
MainMemory::MainMemory(int ramsize, int vmsize) {
    this->ramsize = ramsize;
    this->vmsize = vmsize;
    this->memory = new int[vmsize + ramsize];
}

MainMemory MainMemory::createMainMemory(int ramsize, int vmsize) {
    return MainMemory(ramsize, vmsize);
}

int MainMemory::getMainMemoryData(MainMemory mem, int adress, int* value){
    if(((mem.ramsize + mem.vmsize) > adress) and (adress >= 0)){
        *value = mem.memory[adress >> 2];
        return 4;
    }
    return -1;
}

int MainMemory::setMainMemoryData(MainMemory &mem, int adress, int value){
    if(((mem.ramsize + mem.vmsize) > adress) and (adress >= 0)){
        mem.memory[adress >> 2] = value;
        return 4;
    }
    return -1;
}
