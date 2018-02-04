/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *      Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Função principal do programa
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Cache.h"
#include "TACache.h"
#include "SACache.h"
#include "MainMemory.h"
#include "Processor.h"

using namespace std;

bool isPot2(int num) {
    while (num xor 1) {
        if(num%2 != 0)  return false;
        num = num >> 1;
    }
    return true;
}


int main(int argc, const char * argv[]) {
    SACache l1d, l1i, l2, l3;
    MainMemory mp;
    Memory mem;
    Processor p;
    ifstream file(argv[1]);
    string command;

    while(file >> command) {
        cout << "Comando sendo executado:" << command << endl;
        
        if (command == "cl1d"){
            int c, a, l;
            file >> c  >>  a >> l;

            if(isPot2(a) && isPot2(c) && isPot2(l) && (c%(a*l) == 0)) {
                l1d = SACache::createSACache(c,a,l);
                // cout << "criei l1d com tamanho de linha " << l << ", associatividade " << a
                //      << " e capacidade " << c << endl; 
            } else {
                cerr << "Erro: l1d precisa ter c, a e l multiplos de 2 e c multiplo de a*l" << endl;
                exit(EXIT_FAILURE);

            }
        }
        
        else if (command == "cl1i"){
            int c, a, l;
            file >> c  >>  a >> l;
            if(isPot2(a) && isPot2(c) && isPot2(l) && (c%(a*l) == 0)) {
                l1i = SACache::createSACache(c,a,l);
                // cout << "criei l1i com tamanho de linha " << l << ", associatividade " << a
                //      << " e capacidade " << c << endl; 
            } else {
                cerr << "Erro: l1i precisa ter c, a e l multiplos de 2 e c multiplo de a*l" << endl;
                exit(EXIT_FAILURE);
            }
        }
        
        else if (command == "cl2"){
            int c, a, l;
            file >> c  >>  a >> l;
            if(isPot2(a) && isPot2(c) && isPot2(l) && (c%(a*l) == 0)) {
                l2 = SACache::createSACache(c,a,l);
                // cout << "criei l2 com tamanho de linha " << l << ", associatividade " << a
                //      << " e capacidade " << c << endl; 
            } else {
                cerr << "Erro: l2 precisa ter c, a e l multiplos de 2 e c multiplo de a*l" << endl;
                exit(EXIT_FAILURE);
            }
        }
        
        else if (command == "cl3"){
            int c, a, l;
            file >> c  >>  a >> l;
            if(isPot2(a) && isPot2(c) && isPot2(l) && (c%(a*l) == 0)) {
                l3 = SACache::createSACache(c,a,l);
                cout << "criei l3 com tamanho de linha " << l << ", associatividade " << a
                     << " e capacidade " << c << endl; 
            } else {
                // cerr << "Erro: l3 precisa ter c, a e l multiplos de 2 e c multiplo de a*l" << endl;
                exit(EXIT_FAILURE);
            }
        }
        
        else if (command == "cmp"){
            int ramsize, vmsize;
            file >> ramsize  >>  vmsize;
            mp = MainMemory::createMainMemory(ramsize,vmsize);
            // cout << "Criei memoria principal com RAM =" << ramsize << " e virtual = " << vmsize << endl;
        }
        
        else if (command == "cmem"){
            mem = Memory::createMemory(l1d, l1i, l2, l3, mp);
            // cout << "criei hierarquia de memoria" << endl;
        }
        
        else if (command == "cp"){
            int n;
            file >> n;
            p = new Processor(mem, n);
            // cout << "criei um processador com " << n << " nucleos" << endl;
        }
        
        else if (command == "ri"){
            int n, addr, value;
            file >> n  >>  addr;
            Memory::getInstruction(p.mem[n], addr, value);
            // cout << "li a instrucao de endereco " << addr << " no nucleo " << n << endl; 
        }
        
        else if (command == "wi"){
            int n, addr, value;
            file >> n  >>  addr;
            Memory::setInstruction(p.mem[n], addr, value);
            // cout << "escrevi a instrucao de endereco " << addr << " no nucleo " << n << endl;
        }
        
        else if (command == "rd"){
            int n, addr, value;
            file >> n  >>  addr;
            Memory::getData(p.mem[n], addr, value);
            // cout << "li o dado de endereco " << addr << " no nucleo " << n << endl;
        // }
        
        else if (command == "wd"){
            int n, addr, value;
            file >> n  >>  addr >> value;
            Memory::setData(p.mem[n], addr, value);
            // cout << "escrevi o dado " << value <<" de endereco " << addr << " no nucleo " << n << endl;
        }
        
        else if (command == "asserti"){
            int n, addr, value, level, vCompare;
            file >> n  >>  addr >> level >> value;
            if(level == Memory::getData(p.mem[n], addr, vCompare) {
                if(vCompare == value) {
                    // CONFIRMA.
                }
                else {
                    // ERRO NO VALOR.
                }
            } 
            else {
                // NAO FOI LIDO NO LEVEL.
            }
            // cout << "li a instrucao de endereco " << addr << " no nucleo " << n 
            //      << "e comparei com level " << level << " e com value " << value << endl;
        }
        else if (command == "assertd"){
            int n, addr, value, level, vCompare;
            file >> n  >>  addr >> level >> value;
            if(level == Memory::getData(p.mem[n], addr, vCompare) {
                if(vCompare == value) {
                    // CONFIRMA.
                }
                else {
                    // ERRO NO VALOR.
                }
            } else {
                // NAO FOI LIDO NO LEVEL.
            }
            // cout << "li o dado de endereco " << addr << " no nucleo " << n
            //   << "e comparei com level " << level << " e com value " << value << endl;
        }

        else {
            cerr << "Comando \"" << command << "\" nao foi reconhecido. abortando execucao!" << endl; 
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
