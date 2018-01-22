#include "TACache.h"
#include <cstdlib>
#include <iostream>

using namespace std;
TACache::TACache() {
    matrixBytes = null;
}

TACache::~TACache() {
    delete [] matrixBytes;
}


TACache TACache::createTACache(int c, int l) {
    TACache tac = new TACache();
    tac->matrixBytes = new int*[c];
    
    if((c%4 != 0) or (l%4 != 0)) {
        cerr << "ERRO: c e l precisam ser multiplos de 4" << endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < c; ++i) {
        tac->matrixBytes[i] = new int[l];
        
        // Inicializa a matriz de bytes zerada.
        for(int j = 0; j < l; ++j) {
            tac->matrixBytes[i][j] = 0;
        }
    }
    tac->tACacheCapacity = c;
    tac->tACacheLineSize = l;
    
    return tac;
}
int TACache::getTACacheCapacity(TACache tac) {
    return tac->tACacheCapacity;
}
int TACache::getTACacheLineSize(TACache tac) {
    return tac->tACacheLineSize;
}

/**
 * Função que obtém um valor da cache tac em address e grava em value.
 * Retorna verdadeiro para HIT e false para MISS
 */
bool TACache::getTACacheData(TACache tac, int address, int * value) {
    // TODO verificar se é necessário percorrer a matriz inteira e
    // se o valor que adress referencia está no final da linha ou 
    // logo depois de address. 
    for (int i = 0; i < tac->tACacheCapacity; ++i) {
        for (int j = 0; j < tac->tACacheLineSize; ++j) {
            if(tac->matrixBytes[i][j] == adress) {
                value = tac->matrixBytes[i][j+1];
                return true;
            }
        }
    }
    return false;
    
}
void TACache::setTACacheData(TACache tac, int adress, int value) {
    
}
