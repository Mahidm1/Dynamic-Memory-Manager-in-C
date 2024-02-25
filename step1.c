#include "functions.c"



int main()
{

    struct space mem;
    int memSize = 50; 

 
    initializeMemory(memSize, &mem);
    printMemory(&mem);
    printSizes(&mem);

    free(mem.memory);
    free(mem.sizes);
    return 0;
}

