        #include <stdio.h>
#include <stdlib.h>


struct mab {
    int offset;
    int size;
    int allocated;
    struct mab* next;
    struct mab* prev;
};
typedef struct mab Mab;
typedef Mab* MabPtr;

MabPtr memChk(MabPtr m, int size) {
    while (m != NULL) {
        if (!m->allocated && m->size >= size) {
            return m;
        }
        m = m->next;
    }
    return NULL;
}

MabPtr memAlloc(MabPtr m, int size) {
    MabPtr block = memChk(m, size);
    if (block != NULL) {
        if (block->size > size) {
      
            MabPtr freeBlock = (MabPtr)malloc(sizeof(Mab));
            freeBlock->offset = block->offset + size;
            freeBlock->size = block->size - size;
            freeBlock->allocated = 0;
            freeBlock->next = block->next;
            freeBlock->prev = block;
            
            block->size = size;
            block->allocated = 1;
            block->next = freeBlock;
        } else {
      
            block->allocated = 1;
        }
    }
    return block;
}


MabPtr memFree(MabPtr m) {
    if (m != NULL) {
        m->allocated = 0;
     
        if (m->next != NULL && !m->next->allocated) {
            m->size += m->next->size;
            m->next = m->next->next;
            if (m->next != NULL) {
                m->next->prev = m;
            }
        }
    }
    return m;
}


MabPtr memMerge(MabPtr m) {

    if (m != NULL && m->next != NULL && !m->allocated && !m->next->allocated) {
        m->size += m->next->size;
        m->next = m->next->next;
        if (m->next != NULL) {
            m->next->prev = m;
        }
    }
    return m;
}

MabPtr memSplit(MabPtr m, int size) {
    if (m != NULL && m->size > size) {
        MabPtr newBlock = (MabPtr)malloc(sizeof(Mab));
        newBlock->offset = m->offset + size;
        newBlock->size = m->size - size;
        newBlock->allocated = 0;
        newBlock->next = m->next;
        newBlock->prev = m;
        
        m->size = size;
        m->next = newBlock;
    }
    return m;
}

void printMemoryBlocks(MabPtr m) {
    while (m != NULL) {
        printf("Offset: %d, Size: %d, Allocated: %d\n", m->offset, m->size, m->allocated);
        m = m->next;
    }
}

int main() {
    MabPtr memory = (MabPtr)malloc(sizeof(Mab));
    memory->offset = 0;
    memory->size = 1024;
    memory->allocated = 0;
    memory->next = NULL;
    memory->prev = NULL;

    printf("Initial Memory Blocks:\n");
    printMemoryBlocks(memory);

    MabPtr allocatedBlock = memAlloc(memory, 128);
    if (allocatedBlock != NULL) {
        printf("\nAllocated Memory Block:\n");
        printMemoryBlocks(memory);
    } else {
        printf("\nAllocation failed: No suitable block found.\n");
    }

    memFree(allocatedBlock);
    printf("\nMemory Block After Free:\n");
    printMemoryBlocks(memory);

    memMerge(allocatedBlock);
    printf("\nMemory Block After Merge:\n");
    printMemoryBlocks(memory);

    MabPtr splitBlock = memSplit(memory, 64);
    printf("\nMemory Block After Split:\n");
    printMemoryBlocks(memory);

    free(memory);
    return 0;
}
