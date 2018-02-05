#include <iostream>
#include "Cache.h"
#include "SACache.h"

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
    int addressIl1 = address & (SACache::getSACacheLineSize(l1d));
    int addressIl2 = address & (SACache::getSACacheLineSize(l2));
    int addressIl3 = address & (SACache::getSACacheLineSize(l3));
    int* linel1 = &mmem.memory[addressIl1];
    int* linel2 = &mmem.memory[addressIl2];
    int* linel3 = &mmem.memory[addressIl3];
    setSACacheLine(c.l1d, address, linel1);
    setSACacheLine(c.l2, address, linel2);
    setSACacheLine(*c.l3, address, linel3);
}

void Cache::fetchCacheInstruction(Cache &c, MainMemory mmem, int address){
    int addressIl1 = address & (-c.l1i.bytesLine);
    int addressIl2 = address & (-c.l2.bytesLine);
    int addressIl3 = address & (-c.l2.bytesLine);
    int* linel1 = &mmem.memory[addressIl1];
    int* linel2 = &mmem.memory[addressIl2];
    int* linel3 = &mmem.memory[addressIl3];
    setSACacheLine(c.l1i, address, linel1);
    setSACacheLine(c.l2, address, linel2);
    setSACacheLine(*c.l3, address, linel3);
}

int Cache::getCacheData(Cache &c, MainMemory mmem, int address, int * value){
    int ret = 1;
    if(getSACacheData(c.l1d, adress, value)){
        return 1;
    }
    else if((getSACacheData(c.l2, address, value))){
        ret = 2;
    }
    else if(getSACacheData(*c.l3, address, value)){
        ret = 3;
    }
    else{
        ret = getMainMemoryData(mmen, adress, value);
    }

    if(ret > 0){ //for valid adress
        fetchCacheData(c, mmem, adress);
    }
    return ret;
}

int Cache::getCacheInstruction(Cache &c, MainMemory mmem, int address, int * value){
    int ret = 1;
    if(getSACacheData(c.l1i, address, value)){
        return 1;
    }
    else if(getSACacheData(c.l2, address, value)) {
        ret = 2;
    }
    else if(getSACacheData(*c.l3, address, value)) {
        ret = 3;
    }
    else{
        ret = getMainMemoryData(mmem, address, value);
    }
    
    if (ret > 0) { // for valid adress
        fetchCacheInstruction(c, mmem, address);
    }
    
    return ret;
}

int Cache::setCacheData(Cache &c, mainMemory &mmem, int address, int value){
    int ret = 0;
    if(getSACacheData(c.l1d, address, &value)){
        ret = 1;
    }
    else if(getSACacheData(c.l2, address, &value)){
        ret = 2;
    }
    else if(getSACacheData(*c.l3, address, &value)){
        ret = 3;
    }
    else{
        ret = getMainMemoryData(mmem, adress, &value);
    }
    if(ret > 0){
        fetchCacheData(c, mmem, adress);
    }

    setSACacheData(c.l1d, address, value);
    setSACacheData(c.l2, address, value);
    setSACacheData(*c.l3, address, value);
    setMainMemoryData(mmem, address, value);
    return ret;
}

int Cache::setCacheInstruction(Cache &c, MainMemory mmem, int address, int value){
    int ret = 1;
    if (getSACacheData(c.l1i, address, &value)){
        ret = 1;
    }
    else if(getSACacheData(c.l2, address, &value)){
        ret = 2;
    }
    else if(getSACacheData(*c.l3, address, &value)) {
        ret = 3;
    }
    else{
        ret = getMainMemoryData(mmem, address, &value);
    }
    
    if(ret > 0) { // for valid adress
        fetchCacheData(c, mmem, address);
    }
    setSACacheData(c.l1i, address, value);
    setSACacheData(c.l2, address, value);
    setSACacheData(*c.l3, address, value);
    setMainMemoryData(mmem, address, value);
    return ret;
}

Cache Cache::duplicateCache(Cache c) {
    Cache newCache;
    newCache.l1d = duplicateSACache(c.l1d);
    newCache.l1i = duplicateSACache(c.l1i);
    newCache.l2 = duplicateSACache(c.l2);
    newCache.l3 = c.l3;
    return newCache;
}
