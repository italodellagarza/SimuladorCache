#include <iostream>
#include "Memory.h"
#include "MainMemory.h"
#include "Cache.h"


using namespace std;

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
	if ((address >= 0) and (address < (mem.ramsize + mem.vmsize))){
		retorno = 4;
	}else{
		retorno = -1;
	}
	//~ verifica se encontrou.
    if(retorno == 4){
        retorno = getCacheData(mem.cache, mem.memoria, address, value);
        return retorno;
    }
    return -1;
}

int Memory::getInstruction(Memory mem, int address, int * value){
    int retorno;
    //~ Se retornar 4 ,quer dizer que a busca nao encontrou
	//~ a informacao no L1, no L2 e no L3, assim, e preciso conferir na memoria,
	//~ dessa forma testa se esta pegando na memoria.
    if ((address >= 0) and (address < (mem.ramsize + mem.vmsize))){
		retorno = 4;
	}else{
		retorno = -1;
	}
    if(retorno == -1){
        return retorno;
    }
    int instrucion = getCacheInstruction(mem.cache, mem.memoria, address, value);
    return instruction;
}

int Memory::setData(Memory &mem, int address, int value){
    return setCacheData(mem.cache, mem.memoria, address, value); 
}

int Memory::setInstruction(Memory &mem, int address, int value){
    return setCacheInstruction(mem.cache, mem.memoria, address, value);
}

Memory Memory::duplicateMemory(Memory mem){
    Memory newHierarchy;
    newHierarchy.c = duplicateCache(mem.cache);
    newHierarchy.mMemory = mem.memoria;
    return mem;
}

