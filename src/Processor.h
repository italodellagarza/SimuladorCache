#ifndef PROCESSOR_H
#define PROCESSOR_H 1

/*
 * Classe para representar o processador
 */
class Processor{
private:
	Processor();
public:
	static Processor createProcessor(Memory mem, int ncores);

};


#endif // PROCESSOR_H