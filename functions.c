#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUSY '+'
#define FREE ' '
#define BUSYSIZE -1
#define FREESIZE 0


struct space {
    char  *memory;
    int *sizes;
    int len;
};

void copyString(char *sIn, char *sOut, int len) {
    int t = 0;
    while (t < len) {
        *(sOut + t) = *(sIn + t);
        t++;
    }
}

int stringLen(char *s) {
    int t = 0;
    while (*(s + t) != '\0') t++;
    return t;
}

void printMemory(struct space *mem) {
    int i = 0;
    while (i < mem->len) {
        printf("%c", *(mem->memory + i));
        i++;
    }
    printf("\n");
}

void printSizes(struct space *mem) {
    int i = 0;
    int c;
    while (i < mem->len) {
        int n = *(mem->sizes + i);
        int t = 10000;
        while (n > 9) {
            c = n / t;
            n = n - c * t;
            t = t / 10;
            if (c) {
                c = c % 10 + '0';
                printf("%c", c);
                i++;
            }
        }
        c = n % 10 + '0';
        printf("%c", c);
        i++;
    }
    printf("\n");
}

void initializeMemory(int len, struct space *mem) {
    mem->memory = (char *)malloc(len * sizeof(char));
    mem->sizes = (int *)malloc(len * sizeof(int));
    mem->len = len;

    char *mem_ptr = mem->memory;
    int *sizes_ptr = mem->sizes;

    while (len--) {
        *mem_ptr++ = FREE;
        *sizes_ptr++ = FREESIZE;
    }

    printMemory(mem);
    printSizes(mem);
}

void cleanMemory(struct space *mem) {
    char *mem_ptr = mem->memory;
    int *sizes_ptr = mem->sizes;
    int count = mem->len;

    while (count--) {
        *mem_ptr++ = FREE;
        *sizes_ptr++ = FREESIZE;
    }

    printMemory(mem);
    printSizes(mem);

    free(mem->memory);
    free(mem->sizes);
}

int stackAllocator(int nbytes, struct space *mem) {
    int allocIndex = 0;
    while (allocIndex < mem->len && mem->sizes[allocIndex] != FREESIZE) {
        allocIndex++;
    }

    if (allocIndex + nbytes > mem->len) {
        return mem->len; 
    }

    int *size_ptr = mem->sizes + allocIndex;
    char *mem_ptr = mem->memory + allocIndex;

    *size_ptr = nbytes;
    *mem_ptr = BUSY;

    for (int i = 1; i < nbytes; i++) {
        *(size_ptr + i) = BUSYSIZE;
        *(mem_ptr + i) = BUSY;
    }

    return allocIndex;
}

void deallocator(int p, struct space *mem) {
    if (p < 0 || p >= mem->len || mem->sizes[p] == FREESIZE) {
        return;
    }

    int nbytes = mem->sizes[p];
    int *size_ptr = mem->sizes + p;
    char *mem_ptr = mem->memory + p;

    *size_ptr = FREESIZE;
    *mem_ptr = FREE;

    for (int i = 1; i < nbytes; i++) {
        *(size_ptr + i) = FREESIZE;
        *(mem_ptr + i) = FREE;
    }
}

int spaceScanner(int nbytes, struct space *mem) {
    int *size_ptr = mem->sizes;

    for (int i = 0; i <= mem->len - nbytes; i++, size_ptr++) {
        if (*size_ptr == FREESIZE) {
            int j;
            for (j = 1; j < nbytes; j++) {
                if (*(size_ptr + j) != FREESIZE) break;
            }
            if (j == nbytes) return i;
        }
    }
    return mem->len;
}



void increaseMemory(int nbytes, struct space *mem) {
    int newLen = mem->len;
    while (newLen - mem->len < nbytes) {
        newLen = 2 * (newLen + 1);
    }

    char *oldMemory = mem->memory;
    int *oldSizes = mem->sizes;
    int oldLen = mem->len;

    mem->memory = (char *)malloc(newLen * sizeof(char));
    mem->sizes = (int *)malloc(newLen * sizeof(int));
    mem->len = newLen;

    for (int i = 0; i < newLen; i++) {
        mem->memory[i] = (i < oldLen) ? oldMemory[i] : FREE;
        mem->sizes[i] = (i < oldLen) ? oldSizes[i] : FREESIZE;
    }

    free(oldMemory);
    free(oldSizes);
}


int readString(char **s) {
    int len = 0;
    *s = (char *)malloc(1);
    char c;

    char buffer[1024]; 
    char *buff_ptr = buffer;

    while ((c = getchar()) != '\n' && c != EOF) {
        *buff_ptr++ = c;
        len++;
    }
    *buff_ptr = '\0'; 

    *s = (char *)malloc(len + 1);
    copyString(buffer, *s, len);

    return (c != EOF);
}


void copyArray(int *oldArray, int *newArray, int len) {
    for (int i = 0; i < len; i++) {
        newArray[i] = oldArray[i];
    }
}

int heapAllocator(int nbytes, struct space *mem) {
    int p = spaceScanner(nbytes, mem);
    while (p == mem->len) {
        increaseMemory(nbytes, mem);
        p = spaceScanner(nbytes, mem);
    }

    mem->sizes[p] = nbytes; 
    mem->memory[p] = BUSY;
    for (int i = 1; i < nbytes; i++) {
        mem->sizes[p + i] = BUSYSIZE;
        mem->memory[p + i] = BUSY;
    }

    return p;
}
