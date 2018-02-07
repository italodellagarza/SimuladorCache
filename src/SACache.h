/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Cabeçalho da classe SACache
 */

#include "TACache.h"

#ifndef SACACHE_H
#define SACACHE_H 1


class SACache {
friend class TACache;    
private:
    int nSets;
    int sACacheCapacity;
    int sACacheLineSize;
public:
    int a; // associatividade
    TACache* vetorTACache;
    SACache();
    static SACache createSACache(int c, int a, int l);
    static int getSACacheCapacity(SACache sac);
    static int getSACacheLineSize(SACache sac);
    static bool getSACacheData(SACache sac, int address, int * value);
    static bool setSACacheData(SACache &sac, int address, int value);
    static void setSACacheLine(SACache &sac, int address, int *line);
    static SACache* duplicateSACache(SACache sac);
};
#endif // SACACHE_H
