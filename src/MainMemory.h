#ifndef MAINMEMORY_H
#define MAINMEMORY_H 1


/**
 * Classe para representar a memória.
 */
class MainMemory{
private:
	MainMemory();
public:
	static MainMemory createMainMemory(int ramsize, int vmsize);
	static int allocSegment(MainMemory mem, int id, int size);
	~MainMemory();
};



#endif // MAINMEMORY_H