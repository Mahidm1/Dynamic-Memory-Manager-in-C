#include "functions.c" 
#include <string.h>

int main() {
    struct space mem;
    int memSize = 50;
    initializeMemory(memSize, &mem);

    char *inputString;
    int allocIndex, deallocIndex = -1;
    int sentenceCount = 0;

    while (1) {
        printf("Enter a sentence (or type 'exit' to quit): ");
        if (!readString(&inputString)) {
            break; 
        }

        if (strcmp(inputString, "exit") == 0) {
            free(inputString);
            break; 
        }

        allocIndex = heapAllocator(stringLen(inputString) + 1, &mem);
        copyString(inputString, mem.memory + allocIndex, stringLen(inputString));
        free(inputString);

        sentenceCount++;
        if (sentenceCount % 3 == 0 && deallocIndex != -1) {
            deallocator(deallocIndex, &mem);
        }
        deallocIndex = allocIndex; 

        printMemory(&mem);
        printSizes(&mem);
    }

    cleanMemory(&mem); 
    return 0;
}
