/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Cabeçalho da classe Processor
 */


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
    Memory* coreMemory;
    Processor();
    static Processor createProcessor(Memory mem, int ncores);

};


#endif // PROCESSOR_H
