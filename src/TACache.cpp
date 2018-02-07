/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Métodos para a classe TACache
 */

#include "TACache.h"
#include <cstdlib>
#include <iostream>

using namespace std;

TACache::TACache() {
    matrixBytes = NULL;
    nLines = 1;
    offsetSize = 0;
    linesOccupied = 0;
}

TACache TACache::createTACache(int c, int l) {
    TACache* tac = new TACache();
    tac->nLines = c/l;
    tac->matrixBytes = new int*[tac->nLines];
    tac->lineTaggs = new int[tac->nLines];
    for(int i = 0; i < tac->nLines; ++i) {
        // Divide a linha em um vetor de inteiros.
        tac->matrixBytes[i] = (int*)malloc(l);
    }
    tac->tACacheCapacity = c;
    tac->tACacheLineSize = l;
    int w = tac->nLines;
    while(w xor 1) {
        w  = w >> 1;
        ++tac->offsetSize;
    }
    return *tac;
}
int TACache::getTACacheCapacity(TACache tac) {
    return tac.tACacheCapacity;
}
int TACache::getTACacheLineSize(TACache tac) {
    return tac.tACacheLineSize;
}

/**
 * Função que obtém um valor da cache tac em address e grava em value.
 * Retorna verdadeiro para HIT e false para MISS
 */
bool TACache::getTACacheData(TACache tac, int address, int * value) {
    // Verificando os bits de label
    int offset = (tac.nLines - 1) & address;
    int tag = address  >> tac.offsetSize;
    //cout << "label = " << label << endl;
    for (int i = 0; i < tac.linesOccupied; ++i) {
        if(!(tac.lineTaggs[i] xor tag)){
            *value = tac.matrixBytes[i][offset];
            return true;
        }
    }
    //cout << "Cache MISS" << endl;
    return false;
    
}
bool TACache::setTACacheData(TACache& tac, int address, int value) {
    // Verificando os bits de label
    int offset = (tac.nLines - 1) & address;
    int tag = (address & offset) >> tac.offsetSize;
    //cout << "label = " << label << endl;
    for (int i = 0; i < tac.linesOccupied; ++i) {
        if(!(tac.lineTaggs[i] xor tag)){
            tac.matrixBytes[i][offset] = value;
            return true;
        }
    }
    //cout << "Cache MISS" << endl;
    return false;
}

void TACache::setTACacheLine(TACache& tac, int address, int *line) {
    // Verifica primeiro se já tem
    bool naoTem = true;
    int tag = (address & (tac.nLines -1)) >> tac.offsetSize;
    for (int i = 0; naoTem && i < tac.linesOccupied; ++i) {
        if(!(tac.lineTaggs[i] xor tag)){
            naoTem = false;
        }
    }
    // se não tem.
    if(naoTem) {
        for (int i = tac.linesOccupied; i > 0; --i) {
            tac.lineTaggs[i] = tac.lineTaggs[i-1];
            tac.matrixBytes[i] = tac.matrixBytes[i-1];
        }
        if(tac.linesOccupied < tac.nLines - 1)  {
            ++tac.linesOccupied;
        }
        tac.lineTaggs[0] = tag;
        memcpy(tac.matrixBytes[0], line, tac.tACacheLineSize); // VERIFICAR
    }
}
