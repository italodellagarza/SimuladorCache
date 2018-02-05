#include "TACache.h"
#include <cstdlib>
#include <iostream>

using namespace std;
TACache::TACache() {
    matrixBytes = NULL;
    nLines = 0;
    tagSize = 0;
    linesOccupied = 0;
    tagSize = 0;
    a = 1;
}

TACache::~TACache() {
    delete [] matrixBytes;
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
    	++tac->tagSize;
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
    int tag = (address & !offset) >> tac.tagSize;
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
    int tag = (address & !tag) >> tac.tagSize;
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
	int tag = (address & (tac.nLines -1)) >> tac.tagSize;
	for (int i = tac.linesOccupied; i > 0; --i) {
		tac.lineTaggs[i] = tac.lineTaggs[i-1];
		tac.matrixBytes[i] = tac.matrixBytes[i-1];
	}
	if(tac.linesOccupied < tac.nLines - 1)  {
		++tac.linesOccupied;
	}
	tac.lineTaggs[tac.linesOccupied] = tag;
	tac.matrixBytes[tac.linesOccupied] = line;
}

// char []  toString() {
// 	for (int i = 0; i < ; ++i) {
// 		// TODO
// 	}
// }