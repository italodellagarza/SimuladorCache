#include "TACache.h"
#include <cstdlib>
#include <iostream>

using namespace std;
TACache::TACache() {
    matrixBytes = NULL;
}

TACache::~TACache() {
    delete [] matrixBytes;
    nLines = 0;
    indexSize = 0;
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
        // Inicializa a matriz de bytes zerada.
    }
    tac->tACacheCapacity = c;
    tac->tACacheLineSize = l;
    tac->indexSize = tac->nLines%l;
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
    int label = address;
    cout << "label = " << label << endl;
    for (int i = 0; i < tac.linesOccupied; ++i) {
        cout << *tac.matrixBytes[i] << endl;
        if (tac.lineTaggs[i] == address) {
            value = tac.matrixBytes[i];
            cout << "CACHE HIT" << endl;
            return true;
        }
    }
    cout << "Cache MISS" << endl;
    return false;
    
}
void TACache::setTACacheData(TACache& tac, int address, int value) {
    for (int i = tac.linesOccupied; i > 0; ++i){
        tac.matrixBytes[i] = tac.matrixBytes[i-1];
        tac.lineTaggs[i] = tac.lineTaggs[i-1];
    }
    tac.lineTaggs[tac.linesOccupied] = address;
    tac.matrixBytes[tac.linesOccupied] = &value;

    if (tac.linesOccupied != tac.nLines -1){
        ++tac.linesOccupied;
    }
}
