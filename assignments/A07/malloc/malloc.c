#include "malloc.h"

#include <stdio.h>
#include <assert.h>

typedef struct _Block {
    /*
     * Pointer to the header of the next free block.
     * Only valid if this block is also free.
     * This is null for the last Block of the free list.
     */
    struct _Block *next;

    /*
     * Our header should always have a size of 16 Bytes.
     * This is just for 32 bit systems.
     */
    uint8_t padding[8 - sizeof(void*)];

    /*
     * The size of this block, including the header
     * Always a multiple of 16 bytes.
     */
    uint64_t size;

    /*
     * The data area of this block.
     */
    uint8_t data[];
} Block;

#define HEADER_SIZE sizeof(Block)
#define INV_HEADER_SIZE_MASK ~((uint64_t)HEADER_SIZE - 1)

/*
 * This is the heap you should use.
 * 16 MiB heap space per default. The heap does not grow.
 */
#define HEAP_SIZE (HEADER_SIZE * 1024 * 1024)
uint8_t __attribute__ ((aligned(HEADER_SIZE))) _heapData[HEAP_SIZE];

/*
 * This should point to the first free block in memory.
 */
Block *_firstFreeBlock;

/*
 * Initializes the memory block. You don't need to change this.
 */
void initAllocator()
{
    _firstFreeBlock = (Block*)&_heapData[0];
    _firstFreeBlock->next = NULL;
    _firstFreeBlock->size = HEAP_SIZE;
}

/*
 * Gets the next block that should start after the current one.
 */
static Block *_getNextBlockBySize(const Block *current)
{
    static const Block *end = (Block*)&_heapData[HEAP_SIZE];
    Block *next = (Block*)&current->data[current->size - HEADER_SIZE];

    assert(next <= end);
    return (next == end) ? NULL : next;
}

/*
 * Dumps the allocator. You should not need to modify this.
 */
void dumpAllocator()
{
    Block *current;

    printf("All blocks:\n");
    current = (Block*)&_heapData[0];
    while (current) {
        assert((current->size & INV_HEADER_SIZE_MASK) == current->size);
        assert(current->size > 0);

        printf("  Block starting at %" PRIuPTR ", size %" PRIu64 "\n",
            ((uintptr_t)(void*)current - (uintptr_t)(void*)&_heapData[0]),
            current->size);

        current = _getNextBlockBySize(current);
    }

    printf("Current free block list:\n");
    current = _firstFreeBlock;
    while (current) {
        printf("  Free block starting at %" PRIuPTR ", size %" PRIu64 "\n",
            ((uintptr_t)(void*)current - (uintptr_t)(void*)&_heapData[0]),
            current->size);

        current = current->next;
    }
}

/*
 * Round the integer up to the block header size (16 Bytes).
 */
uint64_t roundUp(uint64_t n)
{
    return (uint64_t)((n + 15) / 16) * 16;
}

void *my_malloc(uint64_t size)
{
    uint64_t neededSize = roundUp(size) + HEADER_SIZE;

    Block *currentBlock = _firstFreeBlock;
    Block *prev = NULL; 

    while (currentBlock != NULL) {
        
        if (currentBlock->size >= neededSize) {
            
        
            if (currentBlock->size >= neededSize + HEADER_SIZE) {
                
                // === SPLIT LOGIK ===
                
                // A. Adresse des neuen freien Blocks berechnen
                // WICHTIG: Cast auf (uint8_t*), damit wir Byte-weise addieren!
                Block *newFreeBlock = (Block*)((uint8_t*)currentBlock + neededSize);
                
                // B. Den neuen Block initialisieren
                newFreeBlock->size = currentBlock->size - neededSize; // Restgröße
                newFreeBlock->next = currentBlock->next;              // Kette weiterführen
                
                // C. Den aktuellen Block auf die angeforderte Größe schrumpfen
                currentBlock->size = neededSize;
                


                if (prev == NULL) {
                    _firstFreeBlock = newFreeBlock;
                } else {
                    prev->next = newFreeBlock;
                }

            } else {
                if (prev == NULL) {
                    _firstFreeBlock = currentBlock->next;
                } else {
                    prev->next = currentBlock->next;
                }
            }

            return (void*)currentBlock->data;
        }

        prev = currentBlock;
        currentBlock = currentBlock->next;
    }

    return NULL;
}

void my_free(void *address)
{
    Block toFree = *(Block*)((uint8_t*)address - HEADER_SIZE);
    Block *currentBlock = _firstFreeBlock;
    Block *prev = NULL;
}


