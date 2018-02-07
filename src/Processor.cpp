/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *          Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Métodos para a classe Processor
 */

#include <iostream>
#include "Processor.h"


Processor::Processor() {
    ncores = 0;
}

/**
 * Método para criar um novo Processador, com
 * ncores núcleos e referenciando a memória mem 
 */
Processor Processor::createProcessor(Memory mem, int ncores) {
    Processor *p = new Processor();
    p->coreMemory = new Memory[ncores];
    p->coreMemory[0] = mem;
    for (int i = 1; i < ncores; ++i) {
        p->coreMemory[i] = Memory::duplicateMemory(mem);
    }
    p->ncores = ncores;
    return *p;
}
