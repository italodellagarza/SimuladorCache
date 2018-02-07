/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Métodos para a classe SACache
 */

#include "SACache.h"
#include <cstdlib>

SACache::SACache() {
    // FAZ NADA
}

SACache SACache::createSACache(int c, int a, int l){
    SACache* sac = new SACache();
    sac->nSets = c/(a*l);
    sac->sACacheCapacity = c;
    sac->sACacheLineSize = l;
    sac->a = a;
    sac->vetorTACache = new TACache[sac->nSets];
    for (int i = 0; i < sac->nSets; i++){
        sac->vetorTACache[i] = TACache::createTACache((a*l),l);
    }
    return *sac;
}


int SACache::getSACacheCapacity(SACache sac){//acessa dados privados
    return sac.sACacheCapacity;
}

int SACache::getSACacheLineSize(SACache sac){//acessa dados privados
    return sac.sACacheLineSize;
}

bool SACache::getSACacheData(SACache sac, int address, int * value){
    int position = (address/getSACacheLineSize(sac)) & (sac.nSets -1);
    return TACache::getTACacheData(sac.vetorTACache[position], address, value);
}

void SACache::setSACacheLine(SACache &sac, int address, int *line){
    int position = (address/getSACacheLineSize(sac)) & (sac.nSets -1);
    TACache::setTACacheLine(sac.vetorTACache[position], address, line);
}

bool SACache::setSACacheData(SACache &sac, int address, int value){
    int position = (address/getSACacheLineSize(sac)) & (sac.nSets -1);
    return TACache::setTACacheData(sac.vetorTACache[position], address, value);
}


SACache* SACache::duplicateSACache(SACache sac){
    SACache* newSac = new SACache();
    newSac->nSets = sac.nSets;
    newSac->sACacheCapacity = sac.sACacheCapacity;
    newSac->sACacheLineSize = sac.sACacheLineSize;
    newSac->a = sac.a;
    newSac->vetorTACache = new TACache[sac.nSets];
    for (int i = 0; i < sac.nSets; i++){
        newSac->vetorTACache[i] = TACache::createTACache((sac.a*sac.sACacheLineSize),sac.sACacheLineSize);
    }
    return newSac;
}

