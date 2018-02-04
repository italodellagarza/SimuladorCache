#include "SACache.h"
#include <vector>

/**
 * Construtor padrão (private).
 */
SACache::SACache() {
    conjuntos = 0;
    capacity = 0;
    associativity = 0;
    bytesLine = 0;
}


SACache SACache::createSACache(int c, int a, int l){

    SACache novoSACache;
    TACache TAC;
    
    novoSACache.capacidade = c;
    novoSACache.associatividade = a;
    novoSACache.bytesLinha = l;
    novoSACache.conjuntos = c / (a * l);
    novoSACache.vetorTACache.resize(newSACache.conjuntos);
    
    TAC = createTACache((a*l), l);
    
    for(int i = 0; i < newSACache.conjuntos; ++i){
        newSACache.vetorTACache[i] = TAC; 
    }
    return novoSACache;
}


inline int SACache::getSACacheCapacity(SACache sac){//acessa dados privados
    return sac.capacity;
}

inline int SACache::getSACacheAssociatividade(SACache sac){//acessa dados privados
    return sac.associativity;
}

inline int SACache::getSACacheLineSize(SACache sac){//acessa dados privados
    return sac.bytesLine;
}

bool SACache::getSACacheData(SACache sac, int address, int * value){
    
    bool hit = false;
    //bool miss = true;
    for(unsigned int i = 0; i < sac.conjuntos and not(hit); i++){
        hit = getTACacheData(sac.vetorTACache[i], address, value);
    }
    return hit;//retorna se aconteceu hit ou nao
}

void SACache::setSACacheLine(SACache &sac, int address, int *line){
    int lookup = (address / sac.bytesLinha) & (sac.conjuntos - 1);//comparacao and bit a bit
    
    setTACacheLine(sac.vetorTACache[lookup], address, line);
}

bool SACache::setSACacheData(SACache &sac, int address, int value){
     int lookup = (address / sac.bytesLinha) & (sac.conjuntos - 1);//comparacao and bit a bit
     
     return setTACacheData(sac.vetorTACache[lookup], address, value);
}


SACache SACache::duplicateSACache(SACache sac){
    SACache novoSACache;
    
    novoSACache.capacity = sac.capacity;
    novoSACache.associativity = sac.associativity;
    novoSACache.bytesLine = sac.bytesLine;
    novoSACache.conjuntos = sac.conjuntos;
    novoSACache.vetorTACache.resize(sac.conjuntos);
    
    for(int i = 0; i < sac.conjuntos; i++){
        novoSACache.vetorTACache[i] = sac.vetorTACache[i];
    }
    
    return novoSACache;
}

