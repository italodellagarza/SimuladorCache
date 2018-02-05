#ifndef PROCESSOR_H
#define PROCESSOR_H 1

#include "Memory.h"

/*
 * Classe para representar o processador
 */
class Processor{
private:
	int ncores;
public:
	Memory coreMemory[];
	Processor();
	static Processor createProcessor(Memory mem, int ncores);
	~Processor();

};


#endif // PROCESSOR_H
