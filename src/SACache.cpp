#include "SACache.h"
#include <cstdlib>
#include "TACache.h"


/**
 * Construtor padrão (private).
 */
SACache::SACache() {
	// FAZ NADA
}


SACache SACache::createSACache(int c, int a, int l){
	SACache* sac = new SACache();
	sac->tac = TACache::createTACache(c,l);
	sac->tac.a = a;
	return *sac;
}


inline int SACache::getSACacheCapacity(SACache sac){//acessa dados privados
    return sac.tac.getTACacheCapacity();
}

inline int SACache::getSACacheAssociatividade(SACache sac){//acessa dados privados
    return sac.tac.a;
}

inline int SACache::getSACacheLineSize(SACache sac){//acessa dados privados
    return sac.tac.getTACacheLineSize();
}

bool SACache::getSACacheData(SACache sac, int address, int * value){
    
    return sac.tac.getTACacheData(sac.tac, address, value);
}

void SACache::setSACacheLine(SACache &sac, int address, int *line){
    setTACacheLine(sac.tac, address, line);
}

bool SACache::setSACacheData(SACache &sac, int address, int value){t
     
     return setTACacheData(sac.tac, address, value);
}


SACache SACache::duplicateSACache(SACache sac){
    SACache* novo = new SACache();
	novo->tac = TACache::createTACache(sac.tac.getSACacheCapacity,sac.tac.getTACacheLineSize);
	novo->tac->a = sac.tac.a;    
    return *novoSACache;
}

