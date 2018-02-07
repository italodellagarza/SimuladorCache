#include <iostream>
#include "Memory.h"

/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *      Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Métodos para a classe Memory
 */



Memory::Memory(){
}

    //~ Guarda os atributos da cache e da memoria pincipal.
Memory Memory::createMemory(Cache c, MainMemory mem){
    Memory createdMemory;
    createdMemory.c = c;
    createdMemory.mMemory = mem;
    return createdMemory;
}

    //~ O if verifica o retorno, se ele for igual a 4, entao o endereco e valido.
    //~ o retorno (-1) significa que nao foi encontrado.
int Memory::getData(Memory mem, int address, int * value){
    int retorno;
    //~ Se retornar 4 ,quer dizer que a busca nao encontrou
    //~ a informacao no L1, no L2 e no L3, assim, e preciso conferir na memoria,
    //~ dessa forma testa se esta pegando na memoria.
    if ((address >= 0) and (address < (mem.mMemory.ramsize + mem.mMemory.vmsize))){
        retorno = 4;
    }else{
        retorno = -1;
    }
    //~ verifica se encontrou.
    if(retorno == 4){
        retorno = Cache::getCacheData(mem.c, mem.mMemory, address, value);
        return retorno;
    }
    return -1;
}

int Memory::getInstruction(Memory mem, int address, int * value){
    int retorno;
    //~ Se retornar 4 ,quer dizer que a busca nao encontrou
    //~ a informacao no L1, no L2 e no L3, assim, e preciso conferir na memoria,
    //~ dessa forma testa se esta pegando na memoria.
    if ((address >= 0) and (address < (mem.mMemory.ramsize + mem.mMemory.vmsize))){
        retorno = 4;
    }else{
        retorno = -1;
    }
    if(retorno == -1){
        return retorno;
    }
    int instruction = Cache::getCacheInstruction(mem.c, mem.mMemory, address, value);
    return instruction;
}

void Memory::setData(Memory &mem, int address, int value){
    Cache::setCacheData(mem.c, mem.mMemory, address, value); 
}

void Memory::setInstruction(Memory &mem, int address, int value){
    Cache::setCacheInstruction(mem.c, mem.mMemory, address, value);
}

Memory Memory::duplicateMemory(Memory mem){
    Memory newHierarchy;
    newHierarchy.c = Cache::duplicateCache(mem.c);
    newHierarchy.mMemory = mem.mMemory;
    return mem;
}
