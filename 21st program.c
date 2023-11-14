#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000

// Node structure representing a free memory block
struct FreeBlock {
    int start;
    int size;
    struct FreeBlock* next;
};

// Function to initialize a free memory block
struct FreeBlock* initializeBlock(int start, int size) {
    struct FreeBlock* block = (struct FreeBlock*)malloc(sizeof(struct FreeBlock));
    block->start = start;
    block->size = size;
    block->next = NULL;
    return block;
}

// Function to display the free memory blocks
void displayFreeBlocks(struct FreeBlock* freeList) {
    printf("Free Memory Blocks:\n");
    while (freeList != NULL) {
        printf("Start: %d, Size: %d\n", freeList->start, freeList->size);
        freeList = freeList->next;
    }
    printf("\n");
}

// Function to allocate memory using worst fit algorithm
void allocateMemory(struct FreeBlock** freeList, int processSize) {
    struct FreeBlock *prev = NULL, *curr = *freeList, *worstFitPrev = NULL, *worstFit = NULL;

    // Find the largest free block
    while (curr != NULL) {
        if (curr->size >= processSize && (worstFit == NULL || curr->size > worstFit->size)) {
            worstFit = curr;
            worstFitPrev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    // Allocate memory if a suitable block is found
    if (worstFit != NULL) {
        int remainingSize = worstFit->size - processSize;

        // Update the free list if there is remaining space
        if (remainingSize > 0) {
            struct FreeBlock* newFreeBlock = initializeBlock(worstFit->start + processSize, remainingSize);
            newFreeBlock->next = worstFit->next;

            if (worstFitPrev == NULL) {
                *freeList = newFreeBlock;
            } else {
                worstFitPrev->next = newFreeBlock;
            }
        } else {
            // Remove the entire block if no remaining space
            if (worstFitPrev == NULL) {
                *freeList = worstFit->next;
            } else {
                worstFitPrev->next = worstFit->next;
            }
        }

        // Display allocation information
        printf("Allocated memory: Start = %d, Size = %d\n", worstFit->start, processSize);
        free(worstFit);
    } else {
        printf("Memory allocation failed. Not enough space.\n");
    }
}

// Function to deallocate memory
void deallocateMemory(struct FreeBlock** freeList, int start, int size) {
    struct FreeBlock* newFreeBlock = initializeBlock(start, size);
    newFreeBlock->next = *freeList;
    *freeList = newFreeBlock;

    printf("Deallocated memory: Start = %d, Size = %d\n", start, size);
}

int main() {
    struct FreeBlock* freeList = initializeBlock(0, MEMORY_SIZE);

    // Display initial free memory blocks
    displayFreeBlocks(freeList);

    // Allocate memory for processes
    allocateMemory(&freeList, 200);
    allocateMemory(&freeList, 300);
    allocateMemory(&freeList, 150);

    // Display free memory blocks after allocations
    displayFreeBlocks(freeList);

    // Deallocate memory
    deallocateMemory(&freeList, 200, 200);
    deallocateMemory(&freeList, 600, 150);

    // Display free memory blocks after deallocations
    displayFreeBlocks(freeList);

    return 0;
}

