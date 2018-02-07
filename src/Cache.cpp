/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Métodos para a classe Cache
 */
 
#include <iostream>
#include "Cache.h"

Cache::Cache(){
}

Cache::Cache(SACache l1d, SACache l1i, SACache l2, SACache* l3) {
    this->l1d = l1d;
    this->l1i = l1i;
    this->l2 = l2;
    this->l3 = l3;
}



Cache Cache::createCache(SACache l1d, SACache l1i, SACache l2, SACache* l3) {
    return Cache(l1d, l1i, l2, l3);
}

void Cache::fetchCacheData(Cache &c, MainMemory mmem, int address){
    // Aqui se encontra o complemento de dois do tamanho da linha de cada cache,
    // faz-se um and bit a bit com address para encontrar o endereço em
    // em cada cache.
    int addressIl1 = address & (SACache::getSACacheLineSize(c.l1d) - 1);
    int addressIl2 = address & (SACache::getSACacheLineSize(c.l2) - 1);
    int addressIl3 = address & (SACache::getSACacheLineSize(*c.l3) - 1);
    int* linel1 = &mmem.memory[addressIl1];
    int* linel2 = &mmem.memory[addressIl2];
    int* linel3 = &mmem.memory[addressIl3];
    SACache::setSACacheLine(c.l1d, address, linel1);
    SACache::setSACacheLine(c.l2, address, linel2);
    SACache::setSACacheLine(*c.l3, address, linel3);
}

void Cache::fetchCacheInstruction(Cache &c, MainMemory mmem, int address){
    // Aqui se encontra o complemento de dois do tamanho da linha de cada cache,
    // faz-se um and bit a bit com address para encontrar o endereço em
    // em cada cache.
    int addressIl1 = address & (SACache::getSACacheLineSize(c.l1d) -1);
    int addressIl2 = address & (SACache::getSACacheLineSize(c.l2) -1);
    int addressIl3 = address & (SACache::getSACacheLineSize(*c.l3) -1);
    int* linel1 = &mmem.memory[addressIl1];
    int* linel2 = &mmem.memory[addressIl2];
    int* linel3 = &mmem.memory[addressIl3];
    SACache::setSACacheLine(c.l1i, address, linel1);
    SACache::setSACacheLine(c.l2, address, linel2);
    SACache::setSACacheLine(*c.l3, address, linel3);
}

int Cache::getCacheData(Cache &c, MainMemory mmem, int address, int * value){
    int ret = 1;
    if(SACache::getSACacheData(c.l1d, address, value)){
        return 1;
    }
    else if((SACache::getSACacheData(c.l2, address, value))){
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, value)){
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, value);
    }

    if(ret > 0){ //for valid adress
        fetchCacheData(c, mmem, address);
    }
    return ret;
}

int Cache::getCacheInstruction(Cache &c, MainMemory mmem, int address, int * value){
    int ret = 1;
    if(SACache::getSACacheData(c.l1i, address, value)){
        return 1;
    }
    else if(SACache::getSACacheData(c.l2, address, value)) {
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, value)) {
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, value);
    }
    
    if (ret > 0) { // for valid adress
        fetchCacheInstruction(c, mmem, address);
    }
    
    return ret;
}

void Cache::setCacheData(Cache &c, MainMemory &mmem, int address, int value){
    int ret = 0;
    if(SACache::getSACacheData(c.l1d, address, &value)){
        ret = 1;
    }
    else if(SACache::getSACacheData(c.l2, address, &value)){
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, &value)){
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, &value);
    }
    if(ret > 0){
        fetchCacheData(c, mmem, address);
    }

    SACache::setSACacheData(c.l1d, address, value);
    SACache::setSACacheData(c.l2, address, value);
    SACache::setSACacheData(*c.l3, address, value);
    MainMemory::setMainMemoryData(mmem, address, value);
}

void Cache::setCacheInstruction(Cache &c, MainMemory mmem, int address, int value){
    int ret = 1;
    if (SACache::getSACacheData(c.l1i, address, &value)){
        ret = 1;
    }
    else if(SACache::getSACacheData(c.l2, address, &value)){
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, &value)) {
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, &value);
    }
    
    if(ret > 0) { // for valid adress
        fetchCacheData(c, mmem, address);
    }
    SACache::setSACacheData(c.l1i, address, value);
    SACache::setSACacheData(c.l2, address, value);
    SACache::setSACacheData(*c.l3, address, value);
    MainMemory::setMainMemoryData(mmem, address, value);
}

Cache Cache::duplicateCache(Cache c) {
    SACache* l1d = SACache::duplicateSACache(c.l1d);
    SACache* l1i = SACache::duplicateSACache(c.l1i);
    SACache* l2 = SACache::duplicateSACache(c.l2);
    SACache* l3 = c.l3;
    return Cache::createCache(*l1d,*l1i,*l2,l3);
}
