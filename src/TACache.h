/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Cabeçalho da classe TACache
 */

#ifndef TACACHE_H
#define TACACHE_H 1

#include <memory.h>

typedef char byte;

class TACache {
friend class SACache;
private:
    int* lineTaggs;
    int nLines; // A Associatividade é o número de linhas
    int linesOccupied;
    int offsetSize;
    int** matrixBytes;
    int tACacheCapacity;
    int tACacheLineSize;
    TACache();
public:
    static TACache createTACache(int c, int l);
    static int getTACacheCapacity(TACache tac);
    static int getTACacheLineSize(TACache tac);
    static bool getTACacheData(TACache tac, int address, int * value);
    static bool setTACacheData(TACache& tac, int address, int value);
    static void setTACacheLine(TACache& tac, int address, int *line);
};

#endif // TACACHE_H
