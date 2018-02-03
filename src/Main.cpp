/**
 * Trabalho de Arquitetura de Computadores I - Simulador de cache de Memória
 * Alunos:  Ítalo Della Garza Silva
 *          Giovani Rezende 
 *          Rodrigo
 *          Lucas Fiorini Braga
 *	    Isadora Moreira Rodrigues
 * Universidade Federal de Lavras - 2018
 * Função principal do programa
 */

#include <iostream>
#include <string>
#include "Cache.h"
#include "TACache.h"
#include "SACache.h"
#include "MainMemory.h"
#include "Processor.h"

using namespace std;


int main(int argc, const char * argv[])
{
 //DECLARAR VARIÁVEIS... l1i, l1d, cl2, entre outras
	
    ifstream file(argv[1]);
    string command;
    file >> command;

    while(command != "")
    {
		cout << "Comando sendo executado:" << command << endl;
		
		if (command == "cl1d"){
			int c, a, l;
			file >> c  >>  a >> l;
			//inicializar l1d como struct ou objeto, dependendo de como foi escolhido
			// l1d = __________(c,a,l);
			// tratar erros
		}
		
		if (command == "cl1di"){
			int c, a, l;
			file >> c  >>  a >> l;
			//inicializar l1i como struct ou objeto, dependendo de como foi escolhido
			// l1i = __________(c,a,l);
			// tratar erros
		}
		
		if (command == "cl2"){
			int c, a, l;
			file >> c  >>  a >> l;
			//inicializar l2 como struct ou objeto, dependendo de como foi escolhido
			// l2 = __________(c,a,l);
			// tratar erros
		}
		
		if (command == "cl3"){
			int c, a, l;
			file >> c  >>  a >> l;
			//inicializar l3 como struct ou objeto, dependendo de como foi escolhido
			//l3 = __________(c,a,l);
			// tratar erros
		}
		
		if (command == "cmp"){
			int ramsize, vmsize;
			file >> ramsize  >>  vmsize;
			inicializar mp como struct ou objeto, dependendo de como foi escolhido
			//mp = __________(c,a,l);
			// tratar erros
		}
		
		if (command == "cmem"){
			int ramsize, vmsize;
			file >> ramsize  >>  vmsize;
			//inicializar mp como struct ou objeto, dependendo de como foi escolhido
			//mem = __________(l1d, l1i, l2, l3, mp);
			// tratar erros
		}
		
		if (command == "cp"){
			int ramsize, vmsize;
			file >> ramsize  >>  vmsize;
			//inicializar mp como struct ou objeto, dependendo de como foi escolhido
			//p = __________(n, mem);
			// tratar erros
		}
		
		if (command == "ri"){
			int n, addr;
			file >> n  >>  addr;
			//__________(n, addr);
			// tratar erros
		}
		
		if (command == "wi"){
			int n, addr, value;
			file >> n  >>  addr >> value;
			//__________(n, addr, value);
			// tratar erros
		}
		
		if (command == "rd"){
			int n, addr;
			file >> n  >>  addr;
			//__________(n, addr);
			// tratar erros
		}
		
		if (command == "wd"){
			int n, addr, value;
			file >> n  >>  addr >> value;
			//__________(n, addr, value);
			// tratar erros
		}
		
		if (command == "asserti"){
			int n, addr, value, level;
			file >> n  >>  addr >> level >> value;
			//__________(n, addr, level, value);
			// tratar erros
		}
		if (command == "assertd"){
			int n, addr, value, level;
			file >> n  >>  addr >> level >> value;
			//__________(n, addr, level, value);
			// tratar erros
		}
        file >> command;
    }

}
