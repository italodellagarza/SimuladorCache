/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Cabeçalho da classe Memory
 */
 
#ifndef MEMORY_H
#define MEMORY_H 1

#include "MainMemory.h"
#include "Cache.h"

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

#endif //MEMORY_H
