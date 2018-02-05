#ifndef MAINMEMORY_H
#define MAINMEMORY_H 1


/**
 * Classe para representar a memória.
 */
class MainMemory{
private:
	int ramsize;
	int vmsize;
	MainMemory(int ramsize, int vmsize);
	int* memory;
public:
	static MainMemory createMainMemory(int ramsize, int vmsize);
	static int allocSegment(MainMemory mem, int id, int size);
	static int getMainMemoryData(MainMemory mem, int adress, int* value);
	static int setMainMemoryData(MainMemory &mem, int adress, int value);
	~MainMemory();
};



#endif // MAINMEMORY_H
