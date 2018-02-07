/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Métodos para a classe MainMemory
 */

#include <iostream>
#include <cstdlib>
#include "MainMemory.h"


/**
 * Métodos da classe MainMemory
 */
MainMemory::MainMemory(int ramsize, int vmsize) {
    this->ramsize = ramsize;
    this->vmsize = vmsize;
    this->memory = new int[(vmsize + ramsize)>>2];
}

MainMemory MainMemory::createMainMemory(int ramsize, int vmsize) {
    return MainMemory(ramsize, vmsize);
}

int MainMemory::getMainMemoryData(MainMemory mem, int address, int* value){
    if(((mem.ramsize + mem.vmsize) > address) and (address >= 0)){
        *value = mem.memory[address >> 2];
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

MainMemory::MainMemory(){
}
