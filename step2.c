#include "functions.c"



int main() {
    struct space mem;
    int memSize = 50; 
    initializeMemory(memSize, &mem); 

    printf("%s\n", mem.memory); 

    char *names[] = {"Brian Kernighan", "CS2850", "Dennis Ritchie"};
    for (int i = 0; i < 3; i++) {
        int requiredSize = stringLen(names[i]) + 5; 
        int index = stackAllocator(requiredSize, &mem);
        if (index < mem.len) {
            copyString(names[i], mem.memory + index, stringLen(names[i]));
        }
        printMemory(&mem);
        printSizes(&mem);
    }
    
    int index = stackAllocator(stringLen(names[2]) + 7, &mem);
    if (index < mem.len) {
        copyString(names[2], mem.memory + index, stringLen(names[2]));
    } else {
        printf("Not enough space to allocate '%s'\n", names[2]);
    }

    printMemory(&mem);
    printSizes(&mem);

    cleanMemory(&mem); 
    return 0;
}

