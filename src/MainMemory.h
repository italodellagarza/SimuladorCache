#ifndef MAINMEMORY_H
#define MAINMEMORY_H 1

/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *      Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Cabeçalho da classe MainMemory
 */

class MainMemory{
    friend class Memory;
private:
    MainMemory(int ramsize, int vmsize);
public:
    int ramsize;
    int vmsize;
    int* memory;
    MainMemory();
    static MainMemory createMainMemory(int ramsize, int vmsize);
    static int allocSegment(MainMemory mem, int id, int size);
    static int getMainMemoryData(MainMemory mem, int adress, int* value);
    static int setMainMemoryData(MainMemory &mem, int adress, int value);
};



#endif // MAINMEMORY_H
