#include <iostream>
#include "Processor.h"


/**
 * Métodos da classe Processor
 */

/**
 * Construtor padrão (privado).
 */
Processor::Processor() {
	memoryHierarchy = NULL;
	ncores = 0;
}

/**
 * Destrutor.
 */
Processor::~Processor() {
	delete [] memoryHierarchy;
}


/**
 * Método para criar um novo Processador, com
 * ncores núcleos e referenciando a memória mem 
 */
Processor Processor::createProcessor(Memory mem, int ncores) {
	Processor p = new Processor();
	p->memoryHierarchy[0] = mem;
	for (int i = 0; i < ncores; ++i) {
		p->memoryHierarchy[i] = Memory.duplicateMemory(mem);
	}
	p->ncores = ncores;
	return p;
}
