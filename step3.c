#include "functions.c"


int main() {
    struct space mem;
    int memSize = 50; 

    initializeMemory(memSize, &mem); 

    int bkIndex = heapAllocator(stringLen("Brian Kernighan") + 2, &mem);
    copyString("Brian Kernighan", mem.memory + bkIndex, stringLen("Brian Kernighan"));

    int csIndex = heapAllocator(stringLen("CS2850") + 2, &mem);
    copyString("CS2850", mem.memory + csIndex, stringLen("CS2850"));
    
    deallocator(csIndex, &mem);

    int drIndex = heapAllocator(stringLen("Dennis Ritchie") + 2, &mem);
    copyString("Dennis Ritchie", mem.memory + drIndex, stringLen("Dennis Ritchie"));

    printMemory(&mem);
    printSizes(&mem);

    cleanMemory(&mem);

    return 0;
}

