#include <iostream>
#include "Processor.h"


/**
 * Métodos da classe Processor
 */

/**
 * Construtor padrão (privado).
 */
Processor::Processor() {
	ncores = 0;
}

/**
 * Destrutor.
 */
Processor::~Processor() {
	delete [] coreMemory;
}


/**
 * Método para criar um novo Processador, com
 * ncores núcleos e referenciando a memória mem 
 */
Processor Processor::createProcessor(Memory mem, int ncores) {
	Processor *p = new Processor();
	p->coreMemory[0] = mem;
	for (int i = 1; i < ncores; ++i) {
		p->coreMemory[i] = Memory::duplicateMemory(mem);
	}
	p->ncores = ncores;
	return *p;
}
