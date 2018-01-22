#ifndef PROCESSOR_H
#define PROCESSOR_H 1

#include "Memory.h"

/*
 * Classe para representar o processador
 */
class Processor{
private:
	Processor();
	Memory memoryHierarchy[];
	int ncores;
public:
	static Processor createProcessor(Memory mem, int ncores);

};


#endif // PROCESSOR_H
