#include <stdio.h>
#include <stdlib.h>

// Static Memory Allocation
int globalVar = 10; // Static allocation outside of functions

void stackAllocationExample() {
    int stackVar = 20; // Stack allocation inside a function
    printf("Stack-Allocated Variable: %d\n", stackVar);
}

void heapAllocationExample() {
    int *heapVar = (int*)malloc(sizeof(int));
    if (heapVar == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    *heapVar = 30; // Heap allocation

    printf("Heap-Allocated Variable: %d\n", *heapVar);

    free(heapVar); // Release allocated memory
}

int main() {
    // Static Allocation
    printf("Static-Allocated Variable: %d\n", globalVar);

    // Stack Allocation
    stackAllocationExample();

    // Heap Allocation
    heapAllocationExample();

    return 0;
}

