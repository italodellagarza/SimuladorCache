/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Cabeçalho da classe Cache
 */

#ifndef CACHE_H
#define CACHE_H 1

#include "SACache.h"
#include "MainMemory.h"

class Cache { 
    friend class Memory;
private:
    SACache l1d;
    SACache l1i;
    SACache l2;
    SACache* l3;
    Cache(SACache l1d, SACache l1i, SACache l2, SACache* l3);
public:
    Cache();
    static Cache createCache(SACache l1d, SACache l1i, SACache l2, SACache* l3);
    static int getCacheData(Cache &c, MainMemory mmem, int address, int * value);
    static int getCacheInstruction(Cache &c, MainMemory mmem, int address, int * value);
    static void setCacheData(Cache &c, MainMemory &mmem, int address, int value);
    static void setCacheInstruction(Cache &c, MainMemory mmem, int address, int value);
    static void fetchCacheData(Cache &c, MainMemory mmem, int adress);
    static void fetchCacheInstruction(Cache &c, MainMemory mmem, int adress);
    static Cache duplicateCache(Cache c);
    
};

#endif // CACHE_H
