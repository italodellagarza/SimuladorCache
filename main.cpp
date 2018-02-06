#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <memory.h>
//~ #include <vector>

using namespace std;
typedef char byte;

class TACache {
friend class SACache;
private:
	int* lineTaggs;
	int nLines; // A Associatividade é o número de linhas
//  int a;		// Associatividade a ser usada no SACache (em TACache é 1)
	int linesOccupied;
	int offsetSize;
    int** matrixBytes;
    int tACacheCapacity;
    int tACacheLineSize;
	TACache();
public:
	static TACache createTACache(int c, int l);
	static int getTACacheCapacity(TACache tac);
	static int getTACacheLineSize(TACache tac);
	static bool getTACacheData(TACache tac, int address, int * value);
	static bool setTACacheData(TACache& tac, int address, int value);
	static void setTACacheLine(TACache& tac, int address, int *line);
	//char []  toString();
	
};


class SACache {
friend class TACache;	
private:
// Implementação antiga*
    int nSets;
    int a; // associatividade
    int sACacheCapacity;
    int sACacheLineSize;
public:
	TACache* vetorTACache;
	SACache();
	static SACache createSACache(int c, int a, int l);
	static int getSACacheCapacity(SACache sac);
	static int getSACacheLineSize(SACache sac);
	static bool getSACacheData(SACache sac, int address, int * value);
	static bool setSACacheData(SACache &sac, int address, int value);
	static void setSACacheLine(SACache &sac, int address, int *line);
	static SACache* duplicateSACache(SACache sac);
};

class MainMemory{
	friend class Memory;
private:
	int ramsize;
	int vmsize;
	MainMemory(int ramsize, int vmsize);
public:
	int* memory;
	MainMemory();
	static MainMemory createMainMemory(int ramsize, int vmsize);
	static int allocSegment(MainMemory mem, int id, int size);
	static int getMainMemoryData(MainMemory mem, int adress, int* value);
	static int setMainMemoryData(MainMemory &mem, int adress, int value);
};


class Cache { 
	friend class Memory;
private:
	SACache l1d;
	SACache l1i;
	SACache l2;
	SACache* l3;
	Cache(SACache l1d, SACache l1i, SACache l2, SACache* l3);
public:
	Cache();
	static Cache createCache(SACache l1d, SACache l1i, SACache l2, SACache* l3);
	static int getCacheData(Cache &c, MainMemory mmem, int address, int * value);
	static int getCacheInstruction(Cache &c, MainMemory mmem, int address, int * value);
	static void setCacheData(Cache &c, MainMemory &mmem, int address, int value);
	static void setCacheInstruction(Cache &c, MainMemory mmem, int address, int value);
	static void fetchCacheData(Cache &c, MainMemory mmem, int adress);
	static void fetchCacheInstruction(Cache &c, MainMemory mmem, int adress);
	static Cache duplicateCache(Cache c);
	
};



class Memory{
    private:
        Cache c;
        MainMemory mMemory;
    public:
        Memory();
        static Memory createMemory(Cache c, MainMemory mem);
        static int getData(Memory mem, int address, int * value);
        static int getInstruction(Memory mem, int address, int * value);
        static void setData(Memory &mem, int address, int value);
        static void setInstruction(Memory &mem, int address, int value);
        static Memory duplicateMemory(Memory mem);
};

class Processor{
private:
	int ncores;
public:
	Memory* coreMemory;
	Processor();
	static Processor createProcessor(Memory mem, int ncores);

};





//

TACache::TACache() {
    matrixBytes = NULL;
    nLines = 1;
    offsetSize = 0;
    linesOccupied = 0;
}




TACache TACache::createTACache(int c, int l) {
    TACache* tac = new TACache();
    tac->nLines = c/l;
    tac->matrixBytes = new int*[tac->nLines];
    tac->lineTaggs = new int[tac->nLines];
    for(int i = 0; i < tac->nLines; ++i) {
        // Divide a linha em um vetor de inteiros.
        tac->matrixBytes[i] = (int*)malloc(l);
    }
    tac->tACacheCapacity = c;
    tac->tACacheLineSize = l;
    int w = tac->nLines;
    while(w xor 1) {
    	w  = w >> 1;
    	++tac->offsetSize;
    }
    return *tac;
}
int TACache::getTACacheCapacity(TACache tac) {
    return tac.tACacheCapacity;
}
int TACache::getTACacheLineSize(TACache tac) {
    return tac.tACacheLineSize;
}

/**
 * Função que obtém um valor da cache tac em address e grava em value.
 * Retorna verdadeiro para HIT e false para MISS
 */
bool TACache::getTACacheData(TACache tac, int address, int * value) {
    // Verificando os bits de label
    int offset = (tac.nLines - 1) & address;
    int tag = address  >> tac.offsetSize;
    //cout << "label = " << label << endl;
    for (int i = 0; i < tac.linesOccupied; ++i) {
        if(!(tac.lineTaggs[i] xor tag)){
        	*value = tac.matrixBytes[i][offset];
            return true;
        }
    }
    //cout << "Cache MISS" << endl;
    return false;
    
}
bool TACache::setTACacheData(TACache& tac, int address, int value) {
    // Verificando os bits de label
    int offset = (tac.nLines - 1) & address;
    int tag = (address & offset) >> tac.offsetSize;
    //cout << "label = " << label << endl;
    for (int i = 0; i < tac.linesOccupied; ++i) {
        if(!(tac.lineTaggs[i] xor tag)){
        	tac.matrixBytes[i][offset] = value;
            return true;
        }
    }
    //cout << "Cache MISS" << endl;
    return false;
}

void TACache::setTACacheLine(TACache& tac, int address, int *line) {
	// Verifica primeiro se já tem
	bool naoTem = true;
	int tag = (address & (tac.nLines -1)) >> tac.offsetSize;
	for (int i = 0; naoTem && i < tac.linesOccupied; ++i) {
        if(!(tac.lineTaggs[i] xor tag)){
            naoTem = false;
        }
    }
    // se não tem.
    if(naoTem) {
		for (int i = tac.linesOccupied; i > 0; --i) {
			tac.lineTaggs[i] = tac.lineTaggs[i-1];
			tac.matrixBytes[i] = tac.matrixBytes[i-1];
		}
		if(tac.linesOccupied < tac.nLines - 1)  {
			++tac.linesOccupied;
		}
		tac.lineTaggs[0] = tag;
		memcpy(tac.matrixBytes[tac.linesOccupied], line, tac.tACacheLineSize); // VERIFICAR
	}
}

SACache::SACache() {
	// FAZ NADA
}


SACache SACache::createSACache(int c, int a, int l){
	SACache* sac = new SACache();
	sac->nSets = c/(a*l);
	sac->sACacheCapacity = c;
	sac->sACacheLineSize = l;
	sac->a = a;
	sac->vetorTACache = new TACache[sac->nSets];
	for (int i = 0; i < sac->nSets; i++){
		sac->vetorTACache[i] = TACache::createTACache((a*l),l);
	}
	return *sac;
}


inline int SACache::getSACacheCapacity(SACache sac){//acessa dados privados
    return TACache::getTACacheCapacity(*sac.vetorTACache);
}

inline int SACache::getSACacheLineSize(SACache sac){//acessa dados privados
    return TACache::getTACacheLineSize(*sac.vetorTACache);
}

bool SACache::getSACacheData(SACache sac, int address, int * value){
	int position = (address/getSACacheLineSize(sac)) & (sac.nSets -1);
	return TACache::getTACacheData(sac.vetorTACache[position], address, value);
}

void SACache::setSACacheLine(SACache &sac, int address, int *line){
	int position = (address/getSACacheLineSize(sac)) & (sac.nSets -1);
    TACache::setTACacheLine(sac.vetorTACache[position], address, line);
}

bool SACache::setSACacheData(SACache &sac, int address, int value){
    int position = (address/getSACacheLineSize(sac)) & (sac.nSets -1);
	return TACache::setTACacheData(sac.vetorTACache[position], address, value);
}


SACache* SACache::duplicateSACache(SACache sac){
    SACache* newSac = new SACache();
	newSac->nSets = sac.nSets;
	newSac->sACacheCapacity = sac.sACacheCapacity;
	newSac->sACacheLineSize = sac.sACacheLineSize;
	newSac->a = sac.a;
	newSac->vetorTACache = new TACache[sac.nSets];
	for (int i = 0; i < sac.nSets; i++){
		newSac->vetorTACache[i] = TACache::createTACache((sac.a*sac.sACacheLineSize),sac.sACacheLineSize);
	}
	return newSac;
}

Processor::Processor() {
	ncores = 0;
}

/**
 * Destrutor.
 */



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

Memory::Memory(){
}

	//~ Guarda os atributos da cache e da memoria pincipal.
Memory Memory::createMemory(Cache c, MainMemory mem){
    Memory createdMemory;
    createdMemory.c = c;
    createdMemory.mMemory = mem;
    return createdMemory;
}

	//~ O if verifica o retorno, se ele for igual a 4, entao o endereco e valido.
	//~ o retorno (-1) significa que nao foi encontrado.
int Memory::getData(Memory mem, int address, int * value){
	int retorno;
	//~ Se retornar 4 ,quer dizer que a busca nao encontrou
	//~ a informacao no L1, no L2 e no L3, assim, e preciso conferir na memoria,
	//~ dessa forma testa se esta pegando na memoria.
	if ((address >= 0) and (address < (mem.mMemory.ramsize + mem.mMemory.vmsize))){
		retorno = 4;
	}else{
		retorno = -1;
	}
	//~ verifica se encontrou.
    if(retorno == 4){
        retorno = Cache::getCacheData(mem.c, mem.mMemory, address, value);
        return retorno;
    }
    return -1;
}

int Memory::getInstruction(Memory mem, int address, int * value){
    int retorno;
    //~ Se retornar 4 ,quer dizer que a busca nao encontrou
	//~ a informacao no L1, no L2 e no L3, assim, e preciso conferir na memoria,
	//~ dessa forma testa se esta pegando na memoria.
    if ((address >= 0) and (address < (mem.mMemory.ramsize + mem.mMemory.vmsize))){
		retorno = 4;
	}else{
		retorno = -1;
	}
    if(retorno == -1){
        return retorno;
    }
    int instruction = Cache::getCacheInstruction(mem.c, mem.mMemory, address, value);
    return instruction;
}

void Memory::setData(Memory &mem, int address, int value){
    Cache::setCacheData(mem.c, mem.mMemory, address, value); 
}

void Memory::setInstruction(Memory &mem, int address, int value){
    Cache::setCacheInstruction(mem.c, mem.mMemory, address, value);
}

Memory Memory::duplicateMemory(Memory mem){
    Memory newHierarchy;
    newHierarchy.c = Cache::duplicateCache(mem.c);
    newHierarchy.mMemory = mem.mMemory;
    return mem;
}


/**
 * Métodos da classe MainMemory
 */
MainMemory::MainMemory(int ramsize, int vmsize) {
    this->ramsize = ramsize;
    this->vmsize = vmsize;
    this->memory = new int[(vmsize + ramsize)>>2];
}

MainMemory MainMemory::createMainMemory(int ramsize, int vmsize) {
    return MainMemory(ramsize, vmsize);
}

int MainMemory::getMainMemoryData(MainMemory mem, int address, int* value){
    if(((mem.ramsize + mem.vmsize) > address) and (address >= 0)){
        *value = mem.memory[address >> 2];
        return 4;
    }
    return -1;
}

int MainMemory::setMainMemoryData(MainMemory &mem, int adress, int value){
    if(((mem.ramsize + mem.vmsize) > adress) and (adress >= 0)){
        mem.memory[adress >> 2] = value;
        return 4;
    }
    return -1;
}

MainMemory::MainMemory(){
}

bool isPot2(int num) {
    while (num xor 1) {
        if(num%2 != 0)  return false;
        num = num >> 1;
    }
    return true;
}

Cache::Cache(){
}

Cache::Cache(SACache l1d, SACache l1i, SACache l2, SACache* l3) {
    this->l1d = l1d;
    this->l1i = l1i;
    this->l2 = l2;
    this->l3 = l3;
}



Cache Cache::createCache(SACache l1d, SACache l1i, SACache l2, SACache* l3) {
    return Cache(l1d, l1i, l2, l3);
}

void Cache::fetchCacheData(Cache &c, MainMemory mmem, int address){
	// Aqui se encontra o complemento de dois do tamanho da linha de cada cache,
	// faz-se um and bit a bit com address para encontrar o endereço em
	// em cada cache.
    int addressIl1 = address & (-SACache::getSACacheLineSize(c.l1d));
    int addressIl2 = address & (-SACache::getSACacheLineSize(c.l2));
    int addressIl3 = address & (-SACache::getSACacheLineSize(*c.l3));
    int* linel1 = &mmem.memory[addressIl1];
    int* linel2 = &mmem.memory[addressIl2];
    int* linel3 = &mmem.memory[addressIl3];
    SACache::setSACacheLine(c.l1d, address, linel1);
    SACache::setSACacheLine(c.l2, address, linel2);
    SACache::setSACacheLine(*c.l3, address, linel3);
}

void Cache::fetchCacheInstruction(Cache &c, MainMemory mmem, int address){
	// Aqui se encontra o complemento de dois do tamanho da linha de cada cache,
	// faz-se um and bit a bit com address para encontrar o endereço em
	// em cada cache.
    int addressIl1 = address & (-SACache::getSACacheLineSize(c.l1d));
    int addressIl2 = address & (-SACache::getSACacheLineSize(c.l2));
    int addressIl3 = address & (-SACache::getSACacheLineSize(*c.l3));
    int* linel1 = &mmem.memory[addressIl1];
    int* linel2 = &mmem.memory[addressIl2];
    int* linel3 = &mmem.memory[addressIl3];
    SACache::setSACacheLine(c.l1i, address, linel1);
    SACache::setSACacheLine(c.l2, address, linel2);
    SACache::setSACacheLine(*c.l3, address, linel3);
}

int Cache::getCacheData(Cache &c, MainMemory mmem, int address, int * value){
    int ret = 1;
    if(SACache::getSACacheData(c.l1d, address, value)){
        return 1;
    }
    else if((SACache::getSACacheData(c.l2, address, value))){
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, value)){
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, value);
    }

    if(ret > 0){ //for valid adress
        fetchCacheData(c, mmem, address);
    }
    return ret;
}

int Cache::getCacheInstruction(Cache &c, MainMemory mmem, int address, int * value){
    int ret = 1;
    if(SACache::getSACacheData(c.l1i, address, value)){
        return 1;
    }
    else if(SACache::getSACacheData(c.l2, address, value)) {
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, value)) {
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, value);
    }
    
    if (ret > 0) { // for valid adress
        fetchCacheInstruction(c, mmem, address);
    }
    
    return ret;
}

void Cache::setCacheData(Cache &c, MainMemory &mmem, int address, int value){
    int ret = 0;
    if(SACache::getSACacheData(c.l1d, address, &value)){
        ret = 1;
    }
    else if(SACache::getSACacheData(c.l2, address, &value)){
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, &value)){
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, &value);
    }
    if(ret > 0){
        fetchCacheData(c, mmem, address);
    }

    SACache::setSACacheData(c.l1d, address, value);
    SACache::setSACacheData(c.l2, address, value);
    SACache::setSACacheData(*c.l3, address, value);
    MainMemory::setMainMemoryData(mmem, address, value);
}

void Cache::setCacheInstruction(Cache &c, MainMemory mmem, int address, int value){
    int ret = 1;
    if (SACache::getSACacheData(c.l1i, address, &value)){
        ret = 1;
    }
    else if(SACache::getSACacheData(c.l2, address, &value)){
        ret = 2;
    }
    else if(SACache::getSACacheData(*c.l3, address, &value)) {
        ret = 3;
    }
    else{
        ret = MainMemory::getMainMemoryData(mmem, address, &value);
    }
    
    if(ret > 0) { // for valid adress
        fetchCacheData(c, mmem, address);
    }
    SACache::setSACacheData(c.l1i, address, value);
    SACache::setSACacheData(c.l2, address, value);
    SACache::setSACacheData(*c.l3, address, value);
    MainMemory::setMainMemoryData(mmem, address, value);
}

Cache Cache::duplicateCache(Cache c) {
    SACache* l1d = SACache::duplicateSACache(c.l1d);
    SACache* l1i = SACache::duplicateSACache(c.l1i);
    SACache* l2 = SACache::duplicateSACache(c.l2);
    SACache* l3 = c.l3;
    return Cache::createCache(*l1d,*l1i,*l2,l3);
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
			Cache c = Cache::createCache(l1d, l1i, l2, &l3);
            mem = Memory::createMemory(c, mp);
            // cout << "criei hierarquia de memoria" << endl;
        }
        
        else if (command == "cp"){
            int n;
            file >> n;
            p = Processor::createProcessor(mem, n);
            // cout << "criei um processador com " << n << " nucleos" << endl;
        }
        
        else if (command == "ri"){
            int n, addr;
            int value;
            file >> n  >>  addr;
            Memory::getInstruction(p.coreMemory[n], addr, &value);
            // cout << "li a instrucao de endereco " << addr << " no nucleo " << n << endl; 
        }
        
        else if (command == "wi"){
            int n, addr, value;
            file >> n  >>  addr >> value;
            Memory::setInstruction(p.coreMemory[n], addr, value);
            // cout << "escrevi a instrucao de endereco " << addr << " no nucleo " << n << endl;
        }
        
        else if (command == "rd"){
            int n, addr;
            int value;
            file >> n  >>  addr;
            Memory::getData(p.coreMemory[n], addr, &value);
            // cout << "li o dado de endereco " << addr << " no nucleo " << n << endl;
        }
        
        else if (command == "wd"){
            int n, addr, value;
            file >> n  >>  addr >> value;
            Memory::setData(p.coreMemory[n], addr, value);
            // cout << "escrevi o dado " << value <<" de endereco " << addr << " no nucleo " << n << endl;
        }
        
        else if (command == "asserti"){
            int n, addr, level;
            int vCompare, value;
            file >> n  >>  addr >> level >> value;
            if(level == Memory::getInstruction(p.coreMemory[n], addr, &vCompare)) {
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
            int n, addr, level;
            int vCompare, value;
            file >> n  >>  addr >> level >> value;
            if(level == Memory::getData(p.coreMemory[n], addr, &vCompare)) {
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

